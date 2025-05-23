# Compiler and tools
CC = gcc
FLEX = flex
BISON = bison
LLVM_CONFIG ?= llvm-config # Allows overriding, e.g., LLVM_CONFIG=/usr/bin/llvm-config-15 make

# Target executable name
TARGET = flowscript_compiler

# Source files
# Manually listed C source files
C_FILES = ast.c codegen.c flowscript_compiler.c
# Generated C source files (names are conventional)
GEN_C_FILES = lex.yy.c flowscript.tab.c

# Object files: derived from C_FILES and GEN_C_FILES
OBJECTS = $(C_FILES:.c=.o) $(GEN_C_FILES:.c=.o)

# Compiler and Linker Flags
# CPPFLAGS for preprocessor flags (e.g., -I for includes, -D for defines)
# CFLAGS for C compiler specific flags (e.g., -g for debug, -Wall for warnings)
# LDFLAGS for linker specific flags (e.g., -L for library search paths)
# LDLIBS for libraries to link (e.g., -lm, -lfl, -lLLVM...)

CPPFLAGS = -I. # Include current directory for flowscript.tab.h, ast.h etc.
CFLAGS = -g -Wall
LDFLAGS =
LDLIBS =

# LLVM Configuration - get flags from llvm-config
# Errors from shell commands will be printed by make
LLVM_CFLAGS_OUT = $(shell $(LLVM_CONFIG) --cflags)
LLVM_LDFLAGS_OUT = $(shell $(LLVM_CONFIG) --ldflags)
LLVM_LIBS_OUT = $(shell $(LLVM_CONFIG) --libs core analysis bitwriter support) # Add other components if needed

CPPFLAGS += $(LLVM_CFLAGS_OUT)
LDFLAGS += $(LLVM_LDFLAGS_OUT)
LDLIBS += $(LLVM_LIBS_OUT)

# Flex and Bison flags
FLEX_FLAGS =
BISON_FLAGS = -d # Crucial for generating flowscript.tab.h

# Add other libraries needed
LDLIBS += -lfl # For Flex library
LDLIBS += -lm  # For math library, if ever needed

# Phony targets (targets that are not actual files)
.PHONY: all clean

# Default target: build the compiler
all: $(TARGET)

# Rule to link the target executable
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Rules for generating C files from .l and .y files
lex.yy.c: flowscript.l flowscript.tab.h
	$(FLEX) $(FLEX_FLAGS) -o $@ $<

# flowscript.tab.h is generated along with flowscript.tab.c due to -d
flowscript.tab.c flowscript.tab.h: flowscript.y ast.h # ast.h is included via %code requires
	$(BISON) $(BISON_FLAGS) -o flowscript.tab.c $<

# Rules for compiling .c source files to .o object files
# These explicit rules help manage dependencies on header files correctly.

ast.o: ast.c ast.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

codegen.o: codegen.c codegen.h ast.h flowscript.tab.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

lex.yy.o: lex.yy.c flowscript.tab.h ast.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

flowscript.tab.o: flowscript.tab.c flowscript.tab.h ast.h codegen.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

flowscript_compiler.o: flowscript_compiler.c ast.h codegen.h flowscript.tab.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# --- Targets for compiling and running FlowScript test file ---
TEST_FS_FILE ?= test.fs
GENERATED_LL_FILE = output.ll
TEST_FS_EXECUTABLE = test_fs_executable

# Target to compile the .ll file to an executable
$(TEST_FS_EXECUTABLE): $(GENERATED_LL_FILE)
	@echo "Compiling $(GENERATED_LL_FILE) to $(TEST_FS_EXECUTABLE) using clang..."
	clang $(GENERATED_LL_FILE) -o $(TEST_FS_EXECUTABLE)
	@echo "$(TEST_FS_EXECUTABLE) created."

# Target to generate output.ll by running the flowscript_compiler
$(GENERATED_LL_FILE): $(TARGET) $(TEST_FS_FILE)
	@echo "Generating $(GENERATED_LL_FILE) from $(TEST_FS_FILE) using ./$(TARGET)..."
	./$(TARGET) < $(TEST_FS_FILE) > /dev/null 2>&1 # Suppress compiler's own stdout/stderr for this step
	@echo "$(GENERATED_LL_FILE) generated."

# Target to build the compiler, then generate .ll, then compile .ll to executable
build_test_executable: $(TEST_FS_EXECUTABLE)

# Target to do all of the above and then run the test executable
run_test: build_test_executable
	@echo "Running $(TEST_FS_EXECUTABLE)..."
	./$(TEST_FS_EXECUTABLE) | cat
	@echo "Test run complete."

# Add these to .PHONY if they don't represent actual files consistently
.PHONY: build_test_executable run_test

# Clean rule: remove generated files
clean:
	rm -f $(TARGET) $(OBJECTS) lex.yy.c flowscript.tab.c flowscript.tab.h \
	$(GENERATED_LL_FILE) $(TEST_FS_EXECUTABLE) output.o *.core 