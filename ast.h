#ifndef AST_H
#define AST_H

#include <stdlib.h> // For malloc, free
#include <string.h> // For strdup

// Forward declaration for ASTNode pointer in other structs
struct ASTNode;

// Node Types Enum
typedef enum NodeType {
    NODE_NUMBER,
    NODE_IDENTIFIER, // Can also be represented directly as char* in some contexts
    NODE_BINARY_OP,
    NODE_ASSIGNMENT,
    NODE_PIPELINE,
    NODE_FUNCTION_CALL,
    NODE_IF,
    NODE_FOR,
    NODE_RANGE,
    NODE_PRINT,
    NODE_STATEMENTS, // Represents a list of statements
    NODE_ARG_LIST_ITEM, // Represents an item in a function call argument list
    NODE_EXPRESSION_STATEMENT // Wrapper for an expression used as a statement
} NodeType;

// For Binary Operations - using token values like PLUS, MINUS, etc.
// For Function Calls - distinguish built-ins
typedef enum BuiltinFunctionID {
    BUILTIN_ID_DOUBLE,
    BUILTIN_ID_ADD,
    BUILTIN_ID_PRINT // Print can also be a keyword/construct
} BuiltinFunctionID;


// Generic AST Node Structure
typedef struct ASTNode {
    NodeType type;
    union {
        // Basic Values / Literals
        struct { int value; } number;
        struct { char *name; } identifier; // Often managed directly by yylval.sval then copied

        // Operations & Expressions
        struct { int op; struct ASTNode *left; struct ASTNode *right; } binary_op;
        struct { struct ASTNode *input; struct ASTNode *transform; } pipeline; // transform is often a function call

        // Function Calls
        struct {
            char *func_name; // For user-defined functions
            BuiltinFunctionID builtin_id; // For built-ins
            int is_builtin; // Flag: 0 for user-defined, 1 for built-in
            struct ASTNode *arg_list_head; // Linked list of argument expressions
        } function_call;

        // Statements
        struct { struct ASTNode *var_node; struct ASTNode *expr_node; } assignment; // var_node should be an IDENTIFIER node

        struct { // For IF and PIPED-IF
            struct ASTNode *condition_expr;     // For standard IF: (condition_expr) { ... }
                                            // For piped-IF: value |> IF (comparison_op condition_expr) { ... }
                                            // Here condition_expr would be the right side of comparison
            struct ASTNode *piped_value_expr;   // For piped-IF: the value on LHS of |>
            int comparison_op_token;        // For piped-IF: GT, LT, EQ, NEQ token value. 0 if not piped-if.
            struct ASTNode *then_block;     // StatementsNode
            struct ASTNode *else_block;     // StatementsNode (can be NULL)
        } if_stmt;

        struct { struct ASTNode *range_node; struct ASTNode *body_block; } for_stmt; // body_block is a StatementsNode
        struct { struct ASTNode *start_expr; struct ASTNode *end_expr; } range_expr;
        struct { struct ASTNode *expr_to_print; int is_implicit_pipe; } print_stmt; // is_implicit_pipe if print() takes from |>

        // For lists of things
        struct { struct ASTNode *current_statement; struct ASTNode *next_statements; } statements; // Linked list for blocks
        struct { struct ASTNode *current_arg; struct ASTNode *next_arg; } arg_list_item; // Linked list for function args
        
        // Wrapper for expressions used as standalone statements (e.g. a pipeline)
        struct { struct ASTNode* expression; } expression_statement;

    } data;
} ASTNode;


// AST Node Constructor Functions (declarations)
ASTNode* ast_new_node(NodeType type); // Generic helper, might not be used directly often

ASTNode* ast_new_number(int value);
ASTNode* ast_new_identifier(char* name); // Note: name should be duplicated if coming from yytext
ASTNode* ast_new_binary_op(int op_token, ASTNode* left, ASTNode* right);
ASTNode* ast_new_assignment(ASTNode* var_node, ASTNode* expr_node);
ASTNode* ast_new_pipeline(ASTNode* input_expr, ASTNode* transform_expr);

ASTNode* ast_new_function_call_user(char* func_name, ASTNode* arg_list_head);
ASTNode* ast_new_function_call_builtin(BuiltinFunctionID builtin_id, ASTNode* arg_list_head);

ASTNode* ast_new_if_statement(ASTNode* condition_expr, ASTNode* then_block, ASTNode* else_block);
ASTNode* ast_new_piped_if_statement(ASTNode* piped_value_expr, int comparison_op, ASTNode* comparison_val_expr, ASTNode* then_block, ASTNode* else_block);

ASTNode* ast_new_for_statement(ASTNode* range_node, ASTNode* body_block);
ASTNode* ast_new_range_expression(ASTNode* start_expr, ASTNode* end_expr);
ASTNode* ast_new_print_statement(ASTNode* expr_to_print, int is_implicit);

ASTNode* ast_new_statements_list(ASTNode* statement, ASTNode* next_statements); // Prepends or appends
ASTNode* ast_new_arg_list_item(ASTNode* arg_expr, ASTNode* next_arg); // For function arguments

ASTNode* ast_new_expression_statement(ASTNode* expression);


// Function to print the AST (declaration)
void ast_print(ASTNode *node, int indent);

// Function to free the AST (declaration)
void ast_free(ASTNode *node);

#endif // AST_H 