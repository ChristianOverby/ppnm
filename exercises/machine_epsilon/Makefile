# Makefile for compiling main.cpp and cleaning up generated files

# Compiler: Specify the C++ compiler to use (g++ in this case) comment out to use system compiler
# CXX = g++ 

# Compiler flags: Options passed to the compiler during compilation
# -Wall: Enable all compiler warnings to catch potential issues
# -std=c++23: Use the C++23 standard for compilation
CXXFLAGS = -Wall -std=c++23

# Linker flags: Libraries to link against (e.g., -lm for math functions)
# -lm → Links libm (Math library)
# -lpthread → Links libpthread (POSIX Threads)
# -lstdc++ → Links libstdc++ (C++ Standard Library)
# -lsqlite3 → Links libsqlite3 (SQLite library)
LDLIBS = -lm

# Target executable: The name of the final executable file to be created
TARGET = main

# Source files: List of all source files to be compiled (only main.cpp here)
SRCS = main.cpp

# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET)

# Rule to link object files and create the final executable
# $(TARGET): The name of the executable (main)
# $(OBJS): The object files needed to create the executable
# $(CXX): The compiler to use (g++)
# $(CXXFLAGS): Compiler flags (e.g., -Wall, -std=c++23)
# -o $(TARGET): Specifies the output file name for the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

# Rule to compile each .cpp file into an object file
# %.o: A pattern rule that matches any .o file
# %.cpp: The corresponding .cpp file for the .o file
# $<: Represents the first dependency (the .cpp file)7
# $@ is the name of the target being generated
# -o $@: Specifies the output file name (the .o file)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target: Removes all generated files (object files and the executable)
# rm -f: Forcefully remove files without prompting for confirmation
# $(OBJS): Removes all object files
# $(TARGET): Removes the final executable
clean:
	rm -f $(OBJS) $(TARGET) output.txt

# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean
