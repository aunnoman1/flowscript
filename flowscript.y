%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h" // Add ast.h here for ast_root definition
#include "codegen.h" // Include codegen header

int yylex(void);
void yyerror(const char *s);

ASTNode *ast_root = NULL; // Global pointer to the root of the AST
%}

%code requires {
    #include "ast.h" // Ensure ASTNode is defined before YYSTYPE for flowscript.tab.h
}

%union {
    int ival;
    char *sval;
    ASTNode *node; // For AST nodes
}

// Tokens from Lexer
%token <ival> NUMBER
%token <sval> IDENTIFIER // IDENTIFIER token carries char*

%token IF ELSE FOR EACH RANGE PRINT
%token AND OR NOT
%token BUILTIN_DOUBLE BUILTIN_ADD

%token PIPE
%token ASSIGN
%token PLUS MINUS MULTIPLY DIVIDE
%token EQ NEQ LT GT
// Future: LTE, GTE

%token LPAREN RPAREN LBRACE RBRACE COMMA

// Types for non-terminals that will have values (now ASTNode pointers)
%type <node> program statements statement
%type <node> assignment_statement pipeline_statement
%type <node> expression term factor
%type <node> function_call_like opt_arg_list arg_list
%type <node> if_statement opt_else_clause
%type <node> for_statement range_expression
// Removed: piped_if_condition, its logic will be in if_statement rule

// Operator Precedence and Associativity (remains the same)
%right NOT
%left OR
%left AND
%nonassoc EQ NEQ LT GT
%left PLUS MINUS
%left MULTIPLY DIVIDE
%left PIPE
%right ASSIGN

%start program

%%

program:
    statements                { ast_root = $1; }
    | /* empty */             { ast_root = NULL; }
    ;

statements:
    statement                 { $$ = ast_new_statements_list($1, NULL); }
    | statement statements    { $$ = ast_new_statements_list($1, $2); } // Builds list: stmt1 -> stmt2 -> ...
    ;

statement:
    assignment_statement      { $$ = $1; }
    | pipeline_statement      { $$ = $1; } // This is an expression used as a statement
    | if_statement            { $$ = $1; }
    | for_statement           { $$ = $1; }
    // | function_definition // To be added later
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression {
        ASTNode* var_node = ast_new_identifier($1);
        $$ = ast_new_assignment(var_node, $3);
        free($1); // Free the sval from IDENTIFIER token
    }
    ;

pipeline_statement: // An expression used as a statement
    expression                { $$ = ast_new_expression_statement($1); }
    ;

expression:
    term                      { $$ = $1; }
    | expression PLUS term     { $$ = ast_new_binary_op(PLUS, $1, $3); }
    | expression MINUS term    { $$ = ast_new_binary_op(MINUS, $1, $3); }
    | expression MULTIPLY term { $$ = ast_new_binary_op(MULTIPLY, $1, $3); }
    | expression DIVIDE term   { $$ = ast_new_binary_op(DIVIDE, $1, $3); }
    | expression EQ term       { $$ = ast_new_binary_op(EQ, $1, $3); }
    | expression NEQ term      { $$ = ast_new_binary_op(NEQ, $1, $3); }
    | expression LT term       { $$ = ast_new_binary_op(LT, $1, $3); }
    | expression GT term       { $$ = ast_new_binary_op(GT, $1, $3); }
    | expression AND term      { $$ = ast_new_binary_op(AND, $1, $3); }
    | expression OR term       { $$ = ast_new_binary_op(OR, $1, $3); }
    | NOT expression           { $$ = ast_new_binary_op(NOT, $2, NULL); /* Using binary_op for unary, right child is NULL */ }
    | expression PIPE function_call_like { $$ = ast_new_pipeline($1, $3); }
    ;

term:
    factor                    { $$ = $1; }
    ;

factor:
    NUMBER                    { $$ = ast_new_number($1); }
    | IDENTIFIER                { $$ = ast_new_identifier($1); free($1); /* IDENTIFIER used as a value */ }
    | function_call_like      { $$ = $1; }
    | LPAREN expression RPAREN  { $$ = $2; /* Pass through the inner expression node */ }
    ;

function_call_like: // Can be part of a pipeline or standalone factor
    IDENTIFIER LPAREN opt_arg_list RPAREN {
        // $1 is sval (char*) from IDENTIFIER token
        $$ = ast_new_function_call_user($1, $3);
        free($1); // Free the sval
    }
    | BUILTIN_DOUBLE LPAREN RPAREN {
        $$ = ast_new_function_call_builtin(BUILTIN_ID_DOUBLE, NULL);
    }
    | BUILTIN_ADD LPAREN expression RPAREN {
        ASTNode* arg_list = ast_new_arg_list_item($3, NULL); // Single argument
        $$ = ast_new_function_call_builtin(BUILTIN_ID_ADD, arg_list);
    }
    | PRINT LPAREN expression RPAREN { // Explicit print(expr)
        $$ = ast_new_print_statement($3, 0 /* not implicit */);
    }
    | PRINT LPAREN RPAREN { // Implicit print() from pipe
        $$ = ast_new_print_statement(NULL, 1 /* implicit */);
    }
    ;

opt_arg_list:
    /* empty */               { $$ = NULL; }
    | arg_list                { $$ = $1; }
    ;

arg_list:
    expression                { $$ = ast_new_arg_list_item($1, NULL); }
    // For func(a, b, c), builds: arg(a) -> arg(b) -> arg(c) -> NULL
    | expression COMMA arg_list { $$ = ast_new_arg_list_item($1, $3); }
    ;

if_statement:
    IF expression LBRACE statements RBRACE opt_else_clause {
        $$ = ast_new_if_statement($2, $4, $6);
    }
    // Piped IF forms:
    | expression PIPE IF GT expression LBRACE statements RBRACE opt_else_clause {
        $$ = ast_new_piped_if_statement($1, GT, $5, $7, $9);
    }
    | expression PIPE IF LT expression LBRACE statements RBRACE opt_else_clause {
        $$ = ast_new_piped_if_statement($1, LT, $5, $7, $9);
    }
    | expression PIPE IF EQ expression LBRACE statements RBRACE opt_else_clause {
        $$ = ast_new_piped_if_statement($1, EQ, $5, $7, $9);
    }
    | expression PIPE IF NEQ expression LBRACE statements RBRACE opt_else_clause {
        $$ = ast_new_piped_if_statement($1, NEQ, $5, $7, $9);
    }
    ;

// Removed piped_if_condition non-terminal

opt_else_clause:
    /* empty */                   { $$ = NULL; }
    | ELSE LBRACE statements RBRACE { $$ = $3; }
    ;

for_statement:
    range_expression PIPE FOR EACH LBRACE pipeline_statement RBRACE {
        // $6 is pipeline_statement which is an expression_statement node
        // The body_block for ast_new_for_statement should be a statements_list node
        // For now, let's assume the body_block in ast_new_for_statement can take a single statement node.
        // If ast_new_for_statement expects a NODE_STATEMENTS for body_block,
        // then we should wrap $6: ast_new_statements_list($6, NULL)
        // Assuming ast.h for_stmt.body_block can be a single statement node for now or a list.
        // Let's check ast.h: for_stmt { ASTNode *range_node; ASTNode *body_block; }
        // body_block should be a NODE_STATEMENTS. Our pipeline_statement is NODE_EXPRESSION_STATEMENT.
        // So, we should wrap it.
        ASTNode* body_as_statement_list = ast_new_statements_list($6, NULL);
        $$ = ast_new_for_statement($1, body_as_statement_list);
    }
    ;

range_expression:
    RANGE LPAREN expression COMMA expression RPAREN {
        $$ = ast_new_range_expression($3, $5);
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    // Consider adding yylloc information if available for better error reporting
}

// Main function updated to use AST
int parser_main_old(void) {
    printf("Starting parse...\n");
    if (yyparse() == 0) {
        printf("Parse successful!\n");
        if (ast_root) {
            printf("AST generated. Printing AST...\n");
            ast_print(ast_root, 0); // Print the AST
            
            printf("Generating LLVM IR...\n");
            codegen_generate(ast_root, "output.ll"); // Generate LLVM IR

            printf("Freeing AST...\n");
            ast_free(ast_root);
        } else {
            printf("AST is NULL (empty input).\n");
        }
    } else {
        printf("Parse failed.\n");
    }
    return 0;
}

// To compile and run (example, add ast.c):
// bison -d flowscript.y  -> flowscript.tab.c, flowscript.tab.h
// flex flowscript.l      -> lex.yy.c
// gcc flowscript.tab.c lex.yy.c ast.c -o flowscript_parser -lfl
// ./flowscript_parser < your_script.fs
