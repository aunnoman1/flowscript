#include <stdio.h>
#include "flowscript.tab.h" // For yyparse, ast_root
#include "ast.h"          // For ASTNode, ast_print, ast_free
#include "codegen.h"      // For codegen_generate

extern FILE *yyin;
extern ASTNode *ast_root; // Defined in flowscript.y or flowscript.tab.c
extern int yylineno;      // For error reporting, provided by lexer

// yyerror is defined in flowscript.y

int main(int argc, char **argv) {
    yyin = stdin; // Default to stdin
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }
    yylineno = 1; // Initialize line number

    fprintf(stderr, "Starting main execution. Initiating parse...\n");
    fflush(stderr);

    int parse_result = yyparse(); // Call the Bison parser

    if (parse_result == 0) {
        // The success message is now printed from within the program rule in flowscript.y
        // fprintf(stderr, "Parse successful (yyparse returned 0)!\n"); 
        if (ast_root) {
            fprintf(stderr, "AST generated. Printing AST...\n");
            fflush(stderr);
            ast_print(ast_root, 0);
            
            fprintf(stderr, "--- AST PRINT COMPLETE. Attempting Codegen ---\n");
            fflush(stderr);
            codegen_generate(ast_root, "output.ll");
            
            fprintf(stderr, "--- CODEGEN COMPLETE. Attempting AST Free ---\n");
            fflush(stderr);
            ast_free(ast_root);
            fprintf(stderr, "--- AST FREE COMPLETE ---\n");
            fflush(stderr);
        } else {
            fprintf(stderr, "Parse resulted in NULL AST root (e.g. empty input processed by specific rule).\n");
            fflush(stderr);
        }
    } else {
        fprintf(stderr, "Parse failed: yyparse returned %d.\n", parse_result);
        // yyerror in flowscript.y should have printed specifics.
        fflush(stderr);
    }

    if (yyin != stdin && yyin != NULL) { // Ensure yyin is not NULL before closing
        fclose(yyin);
    }
    // Return 0 if parse_result was 0 (success), otherwise return an error code (e.g., 1 or parse_result)
    return (parse_result == 0) ? 0 : 1; 
} 