#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h> // For writing bitcode to file, or use Core.h for textual IR dump

// Potentially other headers like Target.h, ExecutionEngine.h if needed later

/**
 * @brief Generates LLVM IR from the AST and writes it to a file.
 *
 * @param ast_root The root of the Abstract Syntax Tree.
 * @param output_filename The name of the file to write the LLVM IR to (e.g., "output.ll").
 */
void codegen_generate(ASTNode *ast_root, const char* output_filename);

#endif // CODEGEN_H 