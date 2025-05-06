#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strcmp, strdup in symbol table
#include "flowscript.tab.h" // For token definitions like GT, PLUS etc.

// Global LLVM variables (or pass them around in a struct)
static LLVMContextRef llvm_context;
static LLVMModuleRef llvm_module;
static LLVMBuilderRef llvm_builder;

// Global reference to the printf function
static LLVMValueRef printf_func;
// Global reference to the printf format string for integers
static LLVMValueRef int_format_str;
// Store printf function type globally as well
static LLVMTypeRef stored_printf_func_type;

// --- Symbol Table for Variables ---
typedef struct SymbolTableEntry {
    char* name;
    LLVMValueRef alloca_inst; 
    struct SymbolTableEntry* next;
} SymbolTableEntry;

static SymbolTableEntry* symbol_table_head = NULL;

static LLVMValueRef find_variable_alloca(const char* name) {
    SymbolTableEntry* current = symbol_table_head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current->alloca_inst;
        }
        current = current->next;
    }
    return NULL;
}

static LLVMValueRef add_variable_alloca(const char* name, LLVMTypeRef type) {
    LLVMValueRef existing_alloca = find_variable_alloca(name);
    if (existing_alloca) {
        // This simplistic model reuses existing alloca. Type changes are not handled.
        // A real compiler might error on re-declaration or handle scopes.
        // Also, the alloca should ideally be in the entry block.
        // For now, if found, just return it, assuming type matches or first one wins.
        // If LLVMTypeOf(LLVMGetAllocatedType(existing_alloca)) != type, it's an issue.
        // fprintf(stderr, "Warning: Variable '%s' re-declaration/type change not fully handled.\n", name);
        return existing_alloca;
    }

    // Create alloca at current builder position. For locals, ideally in function entry block.
    LLVMValueRef alloca_inst = LLVMBuildAlloca(llvm_builder, type, name);

    SymbolTableEntry* new_entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    if (!new_entry) { /* handle malloc failure */ exit(EXIT_FAILURE); }
    new_entry->name = strdup(name);
    if (!new_entry->name) { /* handle strdup failure */ free(new_entry); exit(EXIT_FAILURE); }
    new_entry->alloca_inst = alloca_inst;
    new_entry->next = symbol_table_head;
    symbol_table_head = new_entry;

    fprintf(stderr, "[DEBUG] Allocated variable '%s' (alloca: %p)\n", name, (void*)alloca_inst);
    return alloca_inst;
}

static void clear_symbol_table() {
    SymbolTableEntry* current = symbol_table_head;
    SymbolTableEntry* next;
    while (current) {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    symbol_table_head = NULL;
    fprintf(stderr, "[DEBUG] Symbol table cleared.\n");
}
// --- End Symbol Table ---

// Helper to map comparison operator tokens to LLVMIntPredicate
static LLVMIntPredicate map_token_to_llvm_predicate(int token) {
    switch (token) {
        case EQ:  return LLVMIntEQ;
        case NEQ: return LLVMIntNE;
        case LT:  return LLVMIntSLT; // Assuming signed comparisons for now
        case GT:  return LLVMIntSGT; // Assuming signed comparisons for now
        // Add LTE, GTE if they are added as tokens later
        // case LTE: return LLVMIntSLE;
        // case GTE: return LLVMIntSGE;
        default:
            fprintf(stderr, "Warning: Unknown comparison token %d for LLVMIntPredicate mapping. Defaulting to EQ.\n", token);
            return LLVMIntEQ; // Should not happen if parser only allows valid ops
    }
}

// Forward declarations for recursive codegen functions
static LLVMValueRef codegen_expression(ASTNode* expr_node, LLVMValueRef piped_value_arg);
static void codegen_statement(ASTNode* stmt_node);

// --- Codegen for Expressions (Recursive) ---
static LLVMValueRef codegen_expression(ASTNode* expr_node, LLVMValueRef piped_value_arg) {
    if (!expr_node) return NULL;

    switch (expr_node->type) {
        case NODE_NUMBER:
            // All numbers in FlowScript are integers for now (i32)
            return LLVMConstInt(LLVMInt32TypeInContext(llvm_context), expr_node->data.number.value, 0 /* sign extend? no */);
        
        case NODE_IDENTIFIER: {
            const char* var_name = expr_node->data.identifier.name;
            LLVMValueRef alloca_inst = find_variable_alloca(var_name);
            if (!alloca_inst) {
                fprintf(stderr, "Codegen Error: Undefined variable '%s' used in expression.\n", var_name);
                return NULL; 
            }
            LLVMTypeRef var_type = LLVMGetAllocatedType(alloca_inst);
            fprintf(stderr, "[DEBUG] Loading variable '%s' (alloca: %p, type: %p)\n", 
                    var_name, (void*)alloca_inst, (void*)var_type);
            return LLVMBuildLoad2(llvm_builder, var_type, alloca_inst, var_name);
        }
        
        case NODE_BINARY_OP: {
            fprintf(stderr, "[DEBUG] Codegen_Expr: NODE_BINARY_OP. Left type: %d, Right type: %d\n", 
                    expr_node->data.binary_op.left ? expr_node->data.binary_op.left->type : -1, 
                    expr_node->data.binary_op.right ? expr_node->data.binary_op.right->type : -1);
            LLVMValueRef lhs = codegen_expression(expr_node->data.binary_op.left, NULL);
            LLVMValueRef rhs = NULL;
            // For unary operators like NOT, rhs might be NULL in our AST if we model it that way
            if (expr_node->data.binary_op.right) { 
                rhs = codegen_expression(expr_node->data.binary_op.right, NULL);
            }

            if (!lhs || (expr_node->data.binary_op.right && !rhs)) { // If right exists, rhs must be valid
                fprintf(stderr, "Codegen Error: Operand(s) for binary op yielded NULL.\n");
                return NULL;
            }

            int op = expr_node->data.binary_op.op;

            switch (op) {
                // Arithmetic (assuming i32 for now)
                case PLUS:  return LLVMBuildAdd(llvm_builder, lhs, rhs, "addtmp");
                case MINUS: return LLVMBuildSub(llvm_builder, lhs, rhs, "subtmp");
                case MULTIPLY: return LLVMBuildMul(llvm_builder, lhs, rhs, "multmp");
                case DIVIDE: return LLVMBuildSDiv(llvm_builder, lhs, rhs, "divtmp"); // Signed division

                // Comparisons (return i1)
                case GT: return LLVMBuildICmp(llvm_builder, LLVMIntSGT, lhs, rhs, "gttmp");
                case LT: return LLVMBuildICmp(llvm_builder, LLVMIntSLT, lhs, rhs, "lttmp");
                case EQ: return LLVMBuildICmp(llvm_builder, LLVMIntEQ, lhs, rhs, "eqtmp");
                case NEQ: return LLVMBuildICmp(llvm_builder, LLVMIntNE, lhs, rhs, "neqtmp");
                
                // Logical (assuming i1 operands from comparisons or other logical ops)
                case AND: return LLVMBuildAnd(llvm_builder, lhs, rhs, "andtmp");
                case OR:  return LLVMBuildOr(llvm_builder, lhs, rhs, "ortmp");
                case NOT: // Unary, rhs should be NULL
                    if (!rhs) { 
                        // For i1, NOT x is equivalent to x XOR true, or x == false
                        LLVMValueRef const_false = LLVMConstInt(LLVMInt1TypeInContext(llvm_context), 0, 0);
                        return LLVMBuildICmp(llvm_builder, LLVMIntEQ, lhs, const_false, "nottmp");
                        // Or: return LLVMBuildXor(llvm_builder, lhs, LLVMConstInt(LLVMInt1TypeInContext(llvm_context), 1, 0), "nottmp");
                    } else {
                        fprintf(stderr, "Codegen Error: NOT operator expects one operand.\n");
                        return NULL;
                    }
                
                default:
                    fprintf(stderr, "Codegen: Unimplemented or unknown BINARY_OP operator token: %d\n", op);
                    return NULL;
            }
            break;
        }

        case NODE_FUNCTION_CALL: {
            if (expr_node->data.function_call.is_builtin) {
                BuiltinFunctionID builtin_id = expr_node->data.function_call.builtin_id;
                ASTNode* arg_list_head = expr_node->data.function_call.arg_list_head;
                LLVMValueRef explicit_arg_val = NULL;

                if (arg_list_head && arg_list_head->type == NODE_ARG_LIST_ITEM && 
                    arg_list_head->data.arg_list_item.current_arg) {
                    explicit_arg_val = codegen_expression(arg_list_head->data.arg_list_item.current_arg, NULL);
                    if (!explicit_arg_val) {
                        fprintf(stderr, "Codegen Error: Explicit argument for builtin function yielded NULL.\n");
                        return NULL;
                    }
                }

                switch (builtin_id) {
                    case BUILTIN_ID_DOUBLE:
                        if (piped_value_arg) {
                            LLVMValueRef const_two = LLVMConstInt(LLVMTypeOf(piped_value_arg), 2, 0);
                            return LLVMBuildMul(llvm_builder, piped_value_arg, const_two, "doubletmp_pipe");
                        } else if (explicit_arg_val) {
                            LLVMValueRef const_two = LLVMConstInt(LLVMTypeOf(explicit_arg_val), 2, 0);
                            return LLVMBuildMul(llvm_builder, explicit_arg_val, const_two, "doubletmp_arg");
                        } else {
                             fprintf(stderr, "Codegen Error: BUILTIN_ID_DOUBLE expects a piped value or an explicit argument (latter not current syntax).\n");
                             return NULL;
                        }
                    case BUILTIN_ID_ADD:
                        if (piped_value_arg && explicit_arg_val) {
                            return LLVMBuildAdd(llvm_builder, piped_value_arg, explicit_arg_val, "addtmp_pipe_arg");
                        } else if (explicit_arg_val) {
                            LLVMValueRef const_zero = LLVMConstInt(LLVMTypeOf(explicit_arg_val), 0, 0);
                            fprintf(stderr, "[DEBUG] Codegen: BUILTIN_ID_ADD called as expression with explicit arg %p. Using 0 + arg.\n", (void*)explicit_arg_val);
                            return LLVMBuildAdd(llvm_builder, const_zero, explicit_arg_val, "addtmp_arg_only");
                        } else {
                            fprintf(stderr, "Codegen Error: BUILTIN_ID_ADD requires an explicit argument, and optionally a piped value.\n");
                            return NULL;
                        }
                    case BUILTIN_ID_PRINT: 
                        fprintf(stderr, "Codegen Error: BUILTIN_ID_PRINT (NODE_FUNCTION_CALL) encountered directly as expression. This should be handled by pipeline or expression statement.\n");
                        return NULL;
                    default:
                        fprintf(stderr, "Codegen Error: Unknown builtin_id in function call expression.\n");
                        return NULL;
                }
            } else {
                // User-defined functions (future)
                fprintf(stderr, "Codegen: User-defined FUNCTION_CALL (as expression) not yet implemented.\n");
                return NULL;
            }
        }

        case NODE_PIPELINE: {
            fprintf(stderr, "[DEBUG] Codegen_Expr: NODE_PIPELINE. Left type: %d, Right type: %d\n",
                expr_node->data.pipeline.input ? expr_node->data.pipeline.input->type : -1,
                expr_node->data.pipeline.transform ? expr_node->data.pipeline.transform->type : -1);

            if (!expr_node->data.pipeline.input || !expr_node->data.pipeline.transform) {
                fprintf(stderr, "Codegen Error: Malformed NODE_PIPELINE (missing left or right side).\n");
                return NULL;
            }

            LLVMValueRef lhs_val = codegen_expression(expr_node->data.pipeline.input, piped_value_arg);
            if (!lhs_val) {
                fprintf(stderr, "Codegen Error: LHS of pipeline yielded NULL.\n");
                return NULL;
            }
            
            ASTNode* right_transform_node = expr_node->data.pipeline.transform;

            if (right_transform_node->type == NODE_PRINT) {
                if (right_transform_node->data.print_stmt.is_implicit_pipe) {
                     LLVMValueRef args[] = { int_format_str, lhs_val };
                     LLVMBuildCall2(llvm_builder, stored_printf_func_type, printf_func, args, 2, "printfcall_pipe");
                     fprintf(stderr, "[DEBUG] Codegen: Pipeline to implicit print() generated call with value %p.\n", (void*)lhs_val);
                     return lhs_val;
                } else {
                    fprintf(stderr, "Codegen Error: NODE_PRINT on RHS of pipeline was not marked as implicit_pipe. This is unexpected.\n");
                    return NULL;
                }
            } else if (right_transform_node->type == NODE_FUNCTION_CALL || 
                       right_transform_node->type == NODE_IF ||
                       right_transform_node->type == NODE_PIPELINE) {
                return codegen_expression(right_transform_node, lhs_val);
            } else {
                 fprintf(stderr, "Codegen Error: Invalid node type %d on RHS of pipeline.\n", right_transform_node->type);
                 return NULL;
            }
        }
        
        case NODE_PRINT:
            fprintf(stderr, "Codegen Error: Direct codegen_expression call for NODE_PRINT. This node should be part of ExpressionStatement or Pipeline.\n");
            return NULL;

        default:
            fprintf(stderr, "Codegen Error: Unknown expression node type: %d (raw value)\n", expr_node->type);
            // Try to print more context if it's a print node unexpectedly
            if (expr_node->type == NODE_PRINT) {
                 fprintf(stderr, "    (This unexpected node was NODE_PRINT)\n");
            }
            return NULL;
    }
    return NULL; // Should not be reached for valid expressions that are implemented
}

// --- Codegen for Statements (Recursive) ---
static void codegen_statement(ASTNode* stmt_node) {
    if (!stmt_node) return;

    switch (stmt_node->type) {
        case NODE_ASSIGNMENT: {
            ASTNode* var_ast_node = stmt_node->data.assignment.var_node;
            if (!var_ast_node || var_ast_node->type != NODE_IDENTIFIER) {
                fprintf(stderr, "Codegen Error: LHS of assignment is not a valid identifier.\n");
                return; 
            }
            const char* var_name = var_ast_node->data.identifier.name;
            LLVMValueRef value_to_store = codegen_expression(stmt_node->data.assignment.expr_node, NULL);

            if (!value_to_store) {
                fprintf(stderr, "Codegen Error: RHS expression of assignment to '%s' yielded NULL.\n", var_name);
                return; 
            }

            LLVMValueRef alloca_inst = find_variable_alloca(var_name);
            if (!alloca_inst) {
                alloca_inst = add_variable_alloca(var_name, LLVMTypeOf(value_to_store));
            } else {
                 // Check if type matches? For now, assume it does or re-alloc if different (more complex)
                 LLVMTypeRef alloca_data_type = LLVMGetAllocatedType(alloca_inst);
                 LLVMTypeRef value_type = LLVMTypeOf(value_to_store);
                 if (alloca_data_type != value_type) {
                     fprintf(stderr, "Warning: Type mismatch on re-assignment to variable '%s'. Previous type: %p, New type: %p. Attempting to store anyway.\n", 
                             var_name, (void*)alloca_data_type, (void*)value_type);
                 }
            }
            fprintf(stderr, "[DEBUG] Storing to variable '%s' (alloca: %p, value: %p)\n", 
                    var_name, (void*)alloca_inst, (void*)value_to_store);
            LLVMBuildStore(llvm_builder, value_to_store, alloca_inst);
            break;
        }
        
        case NODE_EXPRESSION_STATEMENT: // e.g. a function call or pipeline used as a statement
            ASTNode* inner_expr = stmt_node->data.expression_statement.expression;
            if (inner_expr) {
                fprintf(stderr, "[DEBUG] Codegen_Stmt: NODE_EXPRESSION_STATEMENT, inner type %d\n", inner_expr->type);
                if (inner_expr->type == NODE_PRINT) {
                    fprintf(stderr, "[DEBUG] Codegen_Stmt: Inner type is NODE_PRINT (explicit call).\n");
                    if (inner_expr->data.print_stmt.is_implicit_pipe) {
                        fprintf(stderr, "Codegen Warning: NODE_PRINT within EXPRESSION_STATEMENT marked as implicit_pipe. This is unusual.\n");
                    } else if (inner_expr->data.print_stmt.expr_to_print) {
                        fprintf(stderr, "[DEBUG] Codegen_Stmt: NODE_PRINT has explicit arg. Calling codegen_expression.\n");
                        LLVMValueRef value_to_print = codegen_expression(inner_expr->data.print_stmt.expr_to_print, NULL);
                        fprintf(stderr, "[DEBUG] Codegen_Stmt: value_to_print is %p\n", (void*)value_to_print);
                        if (value_to_print) {
                            LLVMValueRef args[] = { int_format_str, value_to_print };
                            LLVMBuildCall2(llvm_builder, stored_printf_func_type, printf_func, args, 2, "printfcall_explicit");
                        } else {
                            fprintf(stderr, "Codegen Error: Expression for explicit print statement yielded NULL.\n");
                        }
                    } else {
                        fprintf(stderr, "Codegen Warning: Explicit PRINT_STMT with no argument and not part of pipeline. Behavior undefined.\n");
                    }
                } else {
                    codegen_expression(inner_expr, NULL);
                }
            }
            break;

        case NODE_IF: {
            fprintf(stderr, "[DEBUG] Codegen_Stmt: Processing IF_STMT.\n");
            LLVMValueRef condition_val;
            ASTNode* then_statements = stmt_node->data.if_stmt.then_block;
            ASTNode* else_statements = stmt_node->data.if_stmt.else_block;

            LLVMValueRef current_function = LLVMGetBasicBlockParent(LLVMGetInsertBlock(llvm_builder));

            if (stmt_node->data.if_stmt.piped_value_expr) {
                // Piped if: value |> if OP compare_expr { ... }
                fprintf(stderr, "[DEBUG] Codegen_Stmt: Processing Piped IF_STMT.\n");
                ASTNode* piped_expr_node = stmt_node->data.if_stmt.piped_value_expr;
                ASTNode* compare_to_expr_node = stmt_node->data.if_stmt.condition_expr; // RHS of comparison
                int op_token = stmt_node->data.if_stmt.comparison_op_token;

                LLVMValueRef piped_val = codegen_expression(piped_expr_node, NULL);
                LLVMValueRef compare_val = codegen_expression(compare_to_expr_node, NULL);
                fprintf(stderr, "[DEBUG] Piped IF: piped_val=%p, compare_val=%p for op_token %d\n", (void*)piped_val, (void*)compare_val, op_token);

                if (!piped_val || !compare_val) {
                    fprintf(stderr, "Codegen Warning: Operand(s) for Piped IF_STMT condition yielded NULL. Defaulting to false.\n");
                    condition_val = LLVMConstInt(LLVMInt1TypeInContext(llvm_context), 0, 0); // Default to false
                } else {
                    // Assuming types are compatible (e.g. both i32) for comparison for now.
                    // Proper type checking would be needed here.
                    LLVMIntPredicate predicate = map_token_to_llvm_predicate(op_token);
                    condition_val = LLVMBuildICmp(llvm_builder, predicate, piped_val, compare_val, "pipeif_cond");
                }
            } else {
                // Standard if: if condition_expr { ... }
                condition_val = codegen_expression(stmt_node->data.if_stmt.condition_expr, NULL);
                if (!condition_val) {
                    fprintf(stderr, "Codegen Warning: Condition for IF_STMT yielded NULL. Defaulting to false.\n");
                    condition_val = LLVMConstInt(LLVMInt1TypeInContext(llvm_context), 0, 0); // Default to false
                }
            }
            
            // Ensure condition_val is of i1 type for branching
            // This is a simplification; proper type checking/conversion is needed.
            // If codegen_expression for comparisons doesn't return i1, this will be an issue.
            // For now, if it's not i1, we might have problems or need to cast/compare.
            // Let's assume for now a comparison like X > Y would yield an i1.
            // If condition_val comes from a number (e.g. if 1 {...}), we need to compare it to 0.
            if (LLVMTypeOf(condition_val) != LLVMInt1TypeInContext(llvm_context)) {
                 fprintf(stderr, "[DEBUG] IF condition is not i1, comparing to 0.\n");
                 condition_val = LLVMBuildICmp(llvm_builder, LLVMIntNE, condition_val, 
                                               LLVMConstNull(LLVMTypeOf(condition_val)), "tobool");
            }

            LLVMBasicBlockRef then_block_bb = LLVMAppendBasicBlockInContext(llvm_context, current_function, "then");
            LLVMBasicBlockRef else_block_bb = else_statements ? LLVMAppendBasicBlockInContext(llvm_context, current_function, "else") : NULL;
            LLVMBasicBlockRef merge_block_bb = LLVMAppendBasicBlockInContext(llvm_context, current_function, "ifcont");

            if (else_statements) {
                LLVMBuildCondBr(llvm_builder, condition_val, then_block_bb, else_block_bb);
            } else {
                LLVMBuildCondBr(llvm_builder, condition_val, then_block_bb, merge_block_bb); // No else, directly to merge
            }

            // Codegen for THEN block
            LLVMPositionBuilderAtEnd(llvm_builder, then_block_bb);
            // TEST: Try adding a simple instruction here before recursive calls (REMOVED)
            // LLVMValueRef test_const_then = LLVMConstInt(LLVMInt32TypeInContext(llvm_context), 77, 0);
            // LLVMBuildAdd(llvm_builder, test_const_then, test_const_then, "testadd_then"); // Unused result
            // fprintf(stderr, "[DEBUG] Added testadd_then to then_block_bb %p\n", (void*)then_block_bb);

            if (then_statements && then_statements->type == NODE_STATEMENTS) {
                ASTNode* current_stmt_node = then_statements;
                while(current_stmt_node != NULL && current_stmt_node->type == NODE_STATEMENTS) {
                    codegen_statement(current_stmt_node->data.statements.current_statement);
                    current_stmt_node = current_stmt_node->data.statements.next_statements;
                }
            } // else if then_statements is a single statement? AST structure should ensure it's a list.
            LLVMBuildBr(llvm_builder, merge_block_bb); 

            // Codegen for ELSE block
            if (else_statements) {
                LLVMPositionBuilderAtEnd(llvm_builder, else_block_bb);
                // TEST: Try adding a simple instruction here before recursive calls (REMOVED)
                // LLVMValueRef test_const_else = LLVMConstInt(LLVMInt32TypeInContext(llvm_context), 88, 0);
                // LLVMBuildAdd(llvm_builder, test_const_else, test_const_else, "testadd_else"); // Unused result
                // fprintf(stderr, "[DEBUG] Added testadd_else to else_block_bb %p\n", (void*)else_block_bb);

                if (else_statements->type == NODE_STATEMENTS) {
                    ASTNode* current_stmt_node = else_statements;
                    while(current_stmt_node != NULL && current_stmt_node->type == NODE_STATEMENTS) {
                        codegen_statement(current_stmt_node->data.statements.current_statement);
                        current_stmt_node = current_stmt_node->data.statements.next_statements;
                    }
                }
                LLVMBuildBr(llvm_builder, merge_block_bb); 
            }

            // Position builder at the merge block for subsequent instructions
            LLVMPositionBuilderAtEnd(llvm_builder, merge_block_bb);
            break;
        }

        case NODE_FOR: {
            fprintf(stderr, "[DEBUG] Codegen_Stmt: Processing FOR_STMT.\n");
            ASTNode* range_node = stmt_node->data.for_stmt.range_node;
            ASTNode* body_statements_list = stmt_node->data.for_stmt.body_block;

            if (!range_node || range_node->type != NODE_RANGE) {
                fprintf(stderr, "Codegen Error: Invalid range node in FOR_STMT.\n");
                return;
            }
            if (!body_statements_list || body_statements_list->type != NODE_STATEMENTS) {
                fprintf(stderr, "Codegen Error: Invalid body block in FOR_STMT (must be statements list).\n");
                return;
            }

            LLVMValueRef current_function = LLVMGetBasicBlockParent(LLVMGetInsertBlock(llvm_builder));

            LLVMBasicBlockRef preheader_bb = LLVMAppendBasicBlockInContext(llvm_context, current_function, "loop_preheader");
            LLVMBasicBlockRef cond_check_bb = LLVMAppendBasicBlockInContext(llvm_context, current_function, "loop_cond_check");
            LLVMBasicBlockRef loop_body_bb = LLVMAppendBasicBlockInContext(llvm_context, current_function, "loop_body");
            LLVMBasicBlockRef increment_bb = LLVMAppendBasicBlockInContext(llvm_context, current_function, "loop_increment");
            LLVMBasicBlockRef loop_exit_bb = LLVMAppendBasicBlockInContext(llvm_context, current_function, "loop_exit");

            // Branch from current block to preheader
            LLVMBuildBr(llvm_builder, preheader_bb);

            // --- Preheader Block --- (variable init, end_val eval)
            LLVMPositionBuilderAtEnd(llvm_builder, preheader_bb);
            LLVMValueRef start_val = codegen_expression(range_node->data.range_expr.start_expr, NULL);
            LLVMValueRef end_val = codegen_expression(range_node->data.range_expr.end_expr, NULL);
            if (!start_val || !end_val) {
                fprintf(stderr, "Codegen Error: Failed to evaluate start/end expression for range in FOR_STMT.\n");
                // How to handle this error gracefully? Maybe jump to loop_exit or emit error constant?
                // For now, let's make a best effort to jump to exit. Might leave preheader unterminated.
                LLVMBuildBr(llvm_builder, loop_exit_bb); // Attempt to recover by skipping loop
                LLVMPositionBuilderAtEnd(llvm_builder, loop_exit_bb);
                return; 
            }
            // Assuming range variable and values are i32 for now
            LLVMValueRef loop_var_alloca = LLVMBuildAlloca(llvm_builder, LLVMInt32TypeInContext(llvm_context), "loop_var");
            LLVMBuildStore(llvm_builder, start_val, loop_var_alloca);
            LLVMBuildBr(llvm_builder, cond_check_bb);

            // --- Condition Check Block ---
            LLVMPositionBuilderAtEnd(llvm_builder, cond_check_bb);
            LLVMValueRef current_loop_val = LLVMBuildLoad2(llvm_builder, LLVMInt32TypeInContext(llvm_context), loop_var_alloca, "current_loop_val");
            LLVMValueRef loop_condition = LLVMBuildICmp(llvm_builder, LLVMIntSLT, current_loop_val, end_val, "loop_cond"); // loop_var < end_val
            LLVMBuildCondBr(llvm_builder, loop_condition, loop_body_bb, loop_exit_bb);

            // --- Loop Body Block ---
            LLVMPositionBuilderAtEnd(llvm_builder, loop_body_bb);
            LLVMValueRef current_loop_val_for_body = LLVMBuildLoad2(llvm_builder, LLVMInt32TypeInContext(llvm_context), loop_var_alloca, "loop_val_for_body");
            
            ASTNode* current_stmt_list_item = body_statements_list;
            while (current_stmt_list_item != NULL && current_stmt_list_item->type == NODE_STATEMENTS) {
                ASTNode* actual_stmt_in_body = current_stmt_list_item->data.statements.current_statement;
                if (actual_stmt_in_body) {
                    if (actual_stmt_in_body->type == NODE_EXPRESSION_STATEMENT) {
                        ASTNode* inner_expr_for_loop_body = actual_stmt_in_body->data.expression_statement.expression;
                        if (inner_expr_for_loop_body && // Check if inner_expr_for_loop_body is not NULL
                            inner_expr_for_loop_body->type == NODE_PRINT && 
                            !inner_expr_for_loop_body->data.print_stmt.is_implicit_pipe &&
                            inner_expr_for_loop_body->data.print_stmt.expr_to_print) {
                            
                            fprintf(stderr, "[DEBUG] FOR_STMT Body: Handling explicit print(ARG) statement.\n");
                            LLVMValueRef val_to_print = codegen_expression(inner_expr_for_loop_body->data.print_stmt.expr_to_print, NULL);
                            if (val_to_print) {
                                LLVMValueRef args[] = { int_format_str, val_to_print };
                                LLVMBuildCall2(llvm_builder, stored_printf_func_type, printf_func, args, 2, "printfcall_loop_explicit");
                            } else {
                                fprintf(stderr, "Codegen Error: Expression for explicit print in loop yielded NULL.\n");
                            }
                        } else if (inner_expr_for_loop_body) { // Check if inner_expr_for_loop_body is not NULL before accessing its type
                            fprintf(stderr, "[DEBUG] FOR_STMT Body: Codegen Expression_Statement (type %d) with piped loop_val %p\n", inner_expr_for_loop_body->type, (void*)current_loop_val_for_body);
                            codegen_expression(inner_expr_for_loop_body, current_loop_val_for_body);
                        } else {
                             fprintf(stderr, "[DEBUG] FOR_STMT Body: Encountered NULL inner expression in Expression_Statement.\n");
                        }
                    } else {
                        // For other types of statements, they don't automatically get the loop variable piped.
                        fprintf(stderr, "[DEBUG] FOR_STMT Body: Codegen non-Expression_Statement (type %d)\n", actual_stmt_in_body->type);
                        codegen_statement(actual_stmt_in_body);
                    }
                }
                current_stmt_list_item = current_stmt_list_item->data.statements.next_statements;
            }
            LLVMBuildBr(llvm_builder, increment_bb);

            // --- Increment Block ---
            LLVMPositionBuilderAtEnd(llvm_builder, increment_bb);
            LLVMValueRef val_before_increment = LLVMBuildLoad2(llvm_builder, LLVMInt32TypeInContext(llvm_context), loop_var_alloca, "val_before_inc");
            LLVMValueRef const_one = LLVMConstInt(LLVMInt32TypeInContext(llvm_context), 1, 0);
            LLVMValueRef incremented_val = LLVMBuildAdd(llvm_builder, val_before_increment, const_one, "loop_var_inc");
            LLVMBuildStore(llvm_builder, incremented_val, loop_var_alloca);
            LLVMBuildBr(llvm_builder, cond_check_bb);

            // --- Loop Exit Block --- (Builder is positioned here for subsequent statements)
            LLVMPositionBuilderAtEnd(llvm_builder, loop_exit_bb);
            break;
        }

        // case NODE_PRINT: // This should be handled by NODE_EXPRESSION_STATEMENT wrapping a NODE_PRINT
        //     fprintf(stderr, "Codegen: Direct NODE_PRINT statement encountered (should be rare).\n");
        //     // ... (old logic for direct print, now effectively removed or merged into EXPRESSION_STATEMENT) ...
        //     break;
        
        // NODE_STATEMENTS is handled by the loop in codegen_generate

        default:
            fprintf(stderr, "Codegen Error: Unknown statement node type: %d\n", stmt_node->type);
            break;
    }
}

// --- Main Codegen Function ---
void codegen_generate(ASTNode *ast_root, const char* output_filename) {
    // Initialize LLVM components
    llvm_context = LLVMContextCreate();
    llvm_module = LLVMModuleCreateWithNameInContext("flowscript_module", llvm_context);
    llvm_builder = LLVMCreateBuilderInContext(llvm_context);

    // Declare printf function: int printf(char*, ...)
    LLVMTypeRef printf_arg_types[] = { LLVMPointerType(LLVMInt8TypeInContext(llvm_context), 0) };
    // LLVMTypeRef printf_func_type = LLVMFunctionType(LLVMInt32TypeInContext(llvm_context), printf_arg_types, 1, 1 /* is vararg */);
    // printf_func = LLVMAddFunction(llvm_module, "printf", printf_func_type);
    stored_printf_func_type = LLVMFunctionType(LLVMInt32TypeInContext(llvm_context), printf_arg_types, 1, 1 /* is vararg */);
    printf_func = LLVMAddFunction(llvm_module, "printf", stored_printf_func_type);

    // Create main function: int main()
    LLVMTypeRef main_func_type = LLVMFunctionType(LLVMInt32TypeInContext(llvm_context), NULL, 0, 0);
    LLVMValueRef main_func = LLVMAddFunction(llvm_module, "main", main_func_type);
    LLVMSetLinkage(main_func, LLVMExternalLinkage); 

    // Create entry basic block for main
    LLVMBasicBlockRef entry_block = LLVMAppendBasicBlockInContext(llvm_context, main_func, "entry");
    LLVMPositionBuilderAtEnd(llvm_builder, entry_block);

    // Create global format string for printf: "%d\n" AFTER builder is positioned
    int_format_str = LLVMBuildGlobalStringPtr(llvm_builder, "%d\n", ".fmt_int_global");

    // --- Traverse AST and generate code for statements ---
    ASTNode* current_statements_node = ast_root;
    while (current_statements_node != NULL && current_statements_node->type == NODE_STATEMENTS) {
        codegen_statement(current_statements_node->data.statements.current_statement);
        current_statements_node = current_statements_node->data.statements.next_statements;
    }
    if (current_statements_node != NULL) { 
        fprintf(stderr, "Warning: AST root or statements list was not properly formed for codegen.\n");
    }

    // Add a return 0; at the end of main
    LLVMBuildRet(llvm_builder, LLVMConstInt(LLVMInt32TypeInContext(llvm_context), 0, 0)); // Original return

    // Verify the module for errors
    char *error = NULL;
    if (LLVMVerifyModule(llvm_module, LLVMReturnStatusAction, &error) != 0) {
        fprintf(stderr, "LLVM module verification failed: %s\n", error);
        LLVMDisposeMessage(error); // Important to free the error message
    } else {
        printf("LLVM module verified successfully.\n");
        // Print the LLVM IR to the specified file
        if (LLVMPrintModuleToFile(llvm_module, output_filename, &error) != 0) {
            fprintf(stderr, "Error printing module to file: %s\n", error);
            LLVMDisposeMessage(error);
        } else {
            printf("LLVM IR written to %s\n", output_filename);
        }
    }

    // Dispose of LLVM components
    LLVMDisposeBuilder(llvm_builder);
    LLVMDisposeModule(llvm_module);
    LLVMContextDispose(llvm_context); 
    // NOTE: LLVMValues (like results from codegen_expression) are owned by their module/context or are constants,
    // and generally don't need explicit freeing unless created with specific APIs that say so.
    clear_symbol_table(); // Clear our simple symbol table
} 