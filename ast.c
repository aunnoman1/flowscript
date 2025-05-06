#include "ast.h"
#include <stdio.h> // For printf in case of errors, or for debugging

// Generic AST Node Constructor helper
ASTNode* ast_new_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for ASTNode\n");
        exit(EXIT_FAILURE); // Or handle error more gracefully
    }
    node->type = type;
    // Initialize all union parts to 0/NULL to be safe, though specific constructors will set them.
    // For pointers, this means NULL. For structs, their members are zeroed.
    // memset(&node->data, 0, sizeof(node->data)); // Alternative to individual initialization
    return node;
}

// --- Literal/Basic Value Node Constructors ---
ASTNode* ast_new_number(int value) {
    ASTNode* node = ast_new_node(NODE_NUMBER);
    node->data.number.value = value;
    return node;
}

ASTNode* ast_new_identifier(char* name) {
    ASTNode* node = ast_new_node(NODE_IDENTIFIER);
    node->data.identifier.name = strdup(name); // Must be freed later
    if (!node->data.identifier.name) {
        fprintf(stderr, "Memory allocation failed for identifier name string\n");
        ast_free(node); // Free the node itself
        exit(EXIT_FAILURE);
    }
    return node;
}

// --- Expression Node Constructors ---
ASTNode* ast_new_binary_op(int op_token, ASTNode* left, ASTNode* right) {
    ASTNode* node = ast_new_node(NODE_BINARY_OP);
    node->data.binary_op.op = op_token;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

ASTNode* ast_new_pipeline(ASTNode* input_expr, ASTNode* transform_expr) {
    ASTNode* node = ast_new_node(NODE_PIPELINE);
    node->data.pipeline.input = input_expr;
    node->data.pipeline.transform = transform_expr;
    return node;
}

// --- Function Call Node Constructors ---
ASTNode* ast_new_function_call_user(char* func_name, ASTNode* arg_list_head) {
    ASTNode* node = ast_new_node(NODE_FUNCTION_CALL);
    node->data.function_call.is_builtin = 0;
    node->data.function_call.func_name = strdup(func_name); // Must be freed
    if (!node->data.function_call.func_name) {
        fprintf(stderr, "Memory allocation failed for function name string\n");
        ast_free(node);
        exit(EXIT_FAILURE);
    }
    node->data.function_call.arg_list_head = arg_list_head;
    return node;
}

ASTNode* ast_new_function_call_builtin(BuiltinFunctionID builtin_id, ASTNode* arg_list_head) {
    ASTNode* node = ast_new_node(NODE_FUNCTION_CALL);
    node->data.function_call.is_builtin = 1;
    node->data.function_call.builtin_id = builtin_id;
    node->data.function_call.func_name = NULL; // Not used for builtins
    node->data.function_call.arg_list_head = arg_list_head;
    return node;
}

// --- Statement Node Constructors ---
ASTNode* ast_new_assignment(ASTNode* var_node, ASTNode* expr_node) {
    ASTNode* node = ast_new_node(NODE_ASSIGNMENT);
    // var_node should ideally be of type NODE_IDENTIFIER
    node->data.assignment.var_node = var_node; 
    node->data.assignment.expr_node = expr_node;
    return node;
}

ASTNode* ast_new_if_statement(ASTNode* condition_expr, ASTNode* then_block, ASTNode* else_block) {
    ASTNode* node = ast_new_node(NODE_IF);
    node->data.if_stmt.condition_expr = condition_expr;
    node->data.if_stmt.then_block = then_block;
    node->data.if_stmt.else_block = else_block;
    node->data.if_stmt.piped_value_expr = NULL; // Not a piped-if
    node->data.if_stmt.comparison_op_token = 0; // Not a piped-if
    return node;
}

ASTNode* ast_new_piped_if_statement(ASTNode* piped_value_expr, int comparison_op, ASTNode* comparison_val_expr, ASTNode* then_block, ASTNode* else_block) {
    ASTNode* node = ast_new_node(NODE_IF);
    node->data.if_stmt.piped_value_expr = piped_value_expr;
    node->data.if_stmt.comparison_op_token = comparison_op;
    node->data.if_stmt.condition_expr = comparison_val_expr; // The RHS of the comparison
    node->data.if_stmt.then_block = then_block;
    node->data.if_stmt.else_block = else_block;
    return node;
}

ASTNode* ast_new_for_statement(ASTNode* range_node, ASTNode* body_block) {
    ASTNode* node = ast_new_node(NODE_FOR);
    node->data.for_stmt.range_node = range_node;
    node->data.for_stmt.body_block = body_block;
    return node;
}

ASTNode* ast_new_range_expression(ASTNode* start_expr, ASTNode* end_expr) {
    ASTNode* node = ast_new_node(NODE_RANGE);
    node->data.range_expr.start_expr = start_expr;
    node->data.range_expr.end_expr = end_expr;
    return node;
}

ASTNode* ast_new_print_statement(ASTNode* expr_to_print, int is_implicit) {
    ASTNode* node = ast_new_node(NODE_PRINT);
    node->data.print_stmt.expr_to_print = expr_to_print; // Can be NULL if is_implicit
    node->data.print_stmt.is_implicit_pipe = is_implicit;
    return node;
}

// --- List Node Constructors ---
ASTNode* ast_new_statements_list(ASTNode* statement, ASTNode* next_statements) {
    ASTNode* node = ast_new_node(NODE_STATEMENTS);
    node->data.statements.current_statement = statement;
    node->data.statements.next_statements = next_statements;
    return node;
}

ASTNode* ast_new_arg_list_item(ASTNode* arg_expr, ASTNode* next_arg) {
    ASTNode* node = ast_new_node(NODE_ARG_LIST_ITEM); // Use the correct type
    node->data.arg_list_item.current_arg = arg_expr;
    node->data.arg_list_item.next_arg = next_arg;
    return node;
}

ASTNode* ast_new_expression_statement(ASTNode* expression) {
    ASTNode* node = ast_new_node(NODE_EXPRESSION_STATEMENT);
    node->data.expression_statement.expression = expression;
    return node;
}

// --- AST Freeing Function ---
void ast_free(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_NUMBER:
            // No dynamic parts in number.data itself
            break;
        case NODE_IDENTIFIER:
            free(node->data.identifier.name); // Free the duplicated string
            break;
        case NODE_BINARY_OP:
            ast_free(node->data.binary_op.left);
            ast_free(node->data.binary_op.right);
            break;
        case NODE_ASSIGNMENT:
            ast_free(node->data.assignment.var_node); // This is an identifier node, its name will be freed
            ast_free(node->data.assignment.expr_node);
            break;
        case NODE_PIPELINE:
            ast_free(node->data.pipeline.input);
            ast_free(node->data.pipeline.transform);
            break;
        case NODE_FUNCTION_CALL:{
            if (!node->data.function_call.is_builtin) {
                free(node->data.function_call.func_name); // Free user-defined function name
            }
            // Free argument list (linked list of expression nodes or arg_list_item nodes)
            ASTNode *current_arg = node->data.function_call.arg_list_head;
            ASTNode *next_arg;
            while (current_arg) {
                // If it's a list of NODE_ARG_LIST_ITEM:
                if(current_arg->type == NODE_ARG_LIST_ITEM && current_arg->data.arg_list_item.current_arg) { // Check for NODE_ARG_LIST_ITEM
                     next_arg = current_arg->data.arg_list_item.next_arg;
                     ast_free(current_arg->data.arg_list_item.current_arg); // Free the expression node
                     free(current_arg); // Free the list item node itself
                     current_arg = next_arg;
                } else {
                    // Fallback: if it's just a single expression or an unhandled list structure
                    ast_free(current_arg);
                    break; 
                }
            }
            break;
        }
        case NODE_IF:{
            ast_free(node->data.if_stmt.condition_expr);
            if (node->data.if_stmt.piped_value_expr) {
                ast_free(node->data.if_stmt.piped_value_expr);
            }
            ast_free(node->data.if_stmt.then_block);
            if (node->data.if_stmt.else_block) {
                ast_free(node->data.if_stmt.else_block);
            }
            break;
        }
        case NODE_FOR:{
            ast_free(node->data.for_stmt.range_node);
            ast_free(node->data.for_stmt.body_block);
            break;
        }
        case NODE_RANGE:{
            ast_free(node->data.range_expr.start_expr);
            ast_free(node->data.range_expr.end_expr);
            break;
        }
        case NODE_PRINT:{
            if (node->data.print_stmt.expr_to_print) {
                ast_free(node->data.print_stmt.expr_to_print);
            }
            break;
        }
        case NODE_STATEMENTS:{
            // This also covers how arg_list_item is currently structured if using NODE_STATEMENTS type
            if(node->data.statements.current_statement) ast_free(node->data.statements.current_statement);
            if(node->data.statements.next_statements) ast_free(node->data.statements.next_statements);
            break;
        }
        case NODE_ARG_LIST_ITEM: { // New case for freeing argument list items
            ast_free(node->data.arg_list_item.current_arg);
            ast_free(node->data.arg_list_item.next_arg);
            break;
        }
        case NODE_EXPRESSION_STATEMENT:{
            ast_free(node->data.expression_statement.expression);
            break;
        }
        default:
            fprintf(stderr, "Warning: ast_free called on unknown node type %d\n", node->type);
            break;
    }
    free(node); // Finally, free the node itself
}

// --- AST Printing Function ---

// Helper to print indentation
static void print_indent(int indent) {
    for (int i = 0; i < indent; ++i) {
        printf("  "); // Two spaces per indent level
    }
}

// Helper to get string for operator tokens (simplified)
// In a real compiler, you might use the yytname array if available and configured,
// or a more robust mapping.
const char* op_to_string(int op_token) {
    // This requires knowing the token values generated by Bison.
    // These would typically be in flowscript.tab.h
    // For now, a placeholder or direct check against common ones.
    // This is highly dependent on the actual token values from flowscript.tab.h
    // We'll approximate for now. It's better to include flowscript.tab.h if possible,
    // or define these symbolic constants in ast.h/ast.c as well (less ideal).
    // Let's assume we will add a way to map token values from flowscript.tab.h later.
    // For now, just printing the int value or a simple switch if we had the defines.
    // We can't include flowscript.tab.h directly in ast.c without potential circular dependencies
    // or build system complexities. Let's just print token numbers for now.
    static char buf[16];
    sprintf(buf, "op_val:%d", op_token);
    // Example of what it COULD be if defines were available here:
    /* switch(op_token) {
        case PLUS: return "+"; // Assuming PLUS is a define from flowscript.tab.h
        case MINUS: return "-";
        // ... etc. ...
        default: return "op?";
    }*/
    return buf;
}

void ast_print(ASTNode *node, int indent) {
    if (!node) {
        // print_indent(indent); // Optional: print indent even for NULL if desired
        // printf("(NULL)\n");
        return;
    }

    print_indent(indent);

    switch (node->type) {
        case NODE_NUMBER:
            printf("NUMBER: %d\n", node->data.number.value);
            break;
        case NODE_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->data.identifier.name);
            break;
        case NODE_BINARY_OP:
            printf("BINARY_OP: %s\n", op_to_string(node->data.binary_op.op));
            ast_print(node->data.binary_op.left, indent + 1);
            if (node->data.binary_op.right) { // Right can be NULL for unary ops like NOT
                ast_print(node->data.binary_op.right, indent + 1);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGNMENT:\n");
            print_indent(indent + 1); printf("VAR:\n");
            ast_print(node->data.assignment.var_node, indent + 2); // Should be an IDENTIFIER node
            print_indent(indent + 1); printf("EXPR:\n");
            ast_print(node->data.assignment.expr_node, indent + 2);
            break;
        case NODE_PIPELINE:
            printf("PIPELINE:\n");
            print_indent(indent + 1); printf("INPUT:\n");
            ast_print(node->data.pipeline.input, indent + 2);
            print_indent(indent + 1); printf("TRANSFORM:\n");
            ast_print(node->data.pipeline.transform, indent + 2);
            break;
        case NODE_FUNCTION_CALL: {
            if (node->data.function_call.is_builtin) {
                printf("BUILTIN_CALL: ID %d\n", node->data.function_call.builtin_id);
            } else {
                printf("USER_CALL: %s\n", node->data.function_call.func_name);
            }
            if (node->data.function_call.arg_list_head) {
                print_indent(indent + 1); printf("ARGS:\n");
                ASTNode* current_arg_item = node->data.function_call.arg_list_head;
                while(current_arg_item) {
                    if (current_arg_item->type == NODE_ARG_LIST_ITEM) {
                        ast_print(current_arg_item->data.arg_list_item.current_arg, indent + 2);
                        current_arg_item = current_arg_item->data.arg_list_item.next_arg;
                    } else {
                         print_indent(indent + 2); printf("Error: Expected NODE_ARG_LIST_ITEM in function call args\n");
                         break;
                    }
                }
            } else {
                print_indent(indent + 1); printf("(No Args)\n");
            }
            break;
        }
        case NODE_IF: {
            printf("IF_STMT:\n");
            if (node->data.if_stmt.piped_value_expr) {
                print_indent(indent + 1); printf("PIPED_INPUT:\n");
                ast_print(node->data.if_stmt.piped_value_expr, indent + 2);
                print_indent(indent + 1); printf("COMPARISON_OP: %s\n", op_to_string(node->data.if_stmt.comparison_op_token));
                print_indent(indent + 1); printf("COMPARE_VALUE:\n");
                ast_print(node->data.if_stmt.condition_expr, indent + 2);
            } else {
                print_indent(indent + 1); printf("CONDITION:\n");
                ast_print(node->data.if_stmt.condition_expr, indent + 2);
            }
            print_indent(indent + 1); printf("THEN_BLOCK:\n");
            ast_print(node->data.if_stmt.then_block, indent + 2);
            if (node->data.if_stmt.else_block) {
                print_indent(indent + 1); printf("ELSE_BLOCK:\n");
                ast_print(node->data.if_stmt.else_block, indent + 2);
            }
            break;
        }
        case NODE_FOR: {
            printf("FOR_STMT:\n");
            print_indent(indent + 1); printf("RANGE:\n");
            ast_print(node->data.for_stmt.range_node, indent + 2);
            print_indent(indent + 1); printf("BODY:\n");
            ast_print(node->data.for_stmt.body_block, indent + 2);
            break;
        }
        case NODE_RANGE:
            printf("RANGE_EXPR:\n");
            print_indent(indent + 1); printf("START:\n");
            ast_print(node->data.range_expr.start_expr, indent + 2);
            print_indent(indent + 1); printf("END:\n");
            ast_print(node->data.range_expr.end_expr, indent + 2);
            break;
        case NODE_PRINT:
            printf("PRINT_STMT: %s\n", node->data.print_stmt.is_implicit_pipe ? "(Implicit from pipe)" : "(Explicit arg)");
            if (node->data.print_stmt.expr_to_print) {
                ast_print(node->data.print_stmt.expr_to_print, indent + 1);
            }
            break;
        case NODE_STATEMENTS: {
            printf("STATEMENTS_LIST:\n");
            ASTNode* current_stmt = node; // Start with the current node
            int stmt_count = 0;
            while(current_stmt && current_stmt->type == NODE_STATEMENTS) {
                stmt_count++;
                // print_indent(indent + 1); printf("Statement %d:\n", stmt_count);
                ast_print(current_stmt->data.statements.current_statement, indent + 1); // Print current actual statement
                current_stmt = current_stmt->data.statements.next_statements;
            }
            if(current_stmt) { // Should be NULL if list was properly terminated
                 print_indent(indent+1); printf("Unexpected node in statements list tail.\n");
                 ast_print(current_stmt, indent+1);
            }
            break;
        }
        case NODE_ARG_LIST_ITEM: // This node type is primarily for structure, its content is printed by NODE_FUNCTION_CALL
            printf("ARG_LIST_ITEM:\n");
            ast_print(node->data.arg_list_item.current_arg, indent + 1);
            if (node->data.arg_list_item.next_arg) {
                // This recursive call will print the next ARG_LIST_ITEM fully
                ast_print(node->data.arg_list_item.next_arg, indent); // Same indent for next item in list
            }
            break;
        case NODE_EXPRESSION_STATEMENT:
            printf("EXPRESSION_STATEMENT:\n");
            ast_print(node->data.expression_statement.expression, indent + 1);
            break;
        default:
            printf("UNKNOWN_NODE_TYPE: %d\n", node->type);
            break;
    }
} 