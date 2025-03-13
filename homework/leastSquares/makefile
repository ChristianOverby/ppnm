# Makefile for compiling main.cpp and cleaning up generated files

# Compiler: Specify the C++ compiler to use (g++ in this case) if needed.
# clang maybe
CXX = g++

# Compiler flags: Options passed to the compiler during compilation
# -Wall: Enable all compiler w	arnings to catch potential issues
# -std=c++23: Use the C++23 standard for compilation
# -Wextra: Extra errors
# -ferror-limit=1: tells the compiler to stop after encountering one error

CXXFLAGS += -Wall -Wextra -std=c++23

# Linker flags: Libraries to link against (e.g., -lm for math functions)
# -lm → Links libm (Math library)
# -lpthread → Links libpthread (POSIX Threads)
# -lstdc++ → Links libstdc++ (C++ Standard Library)
# -lsqlite3 → Links libsqlite3 (SQLite library)
LDLIBS += -lm -lstdc++

# Target executable: The name of the final executable file to be created
TARGET = main

# Source files: List of all source files to be compiled (only main.cpp here)
SRCS = main.cpp ../includes/matrix.cpp lsfitter.cpp ../linear_equations/QRGS.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt
PLOT_DATA_OUTPUT = fitResult.csv

# Extract values from data file
sol_c = $(shell grep -A 1 'Solution c:' $(OUTPUT) | tail -n 1)
stderr_sol = $(shell grep -A 1 'stderr on sol:' $(OUTPUT) | tail -n 1)

# Parse the values
a = $(shell echo $(sol_c) | awk '{print $$1}')
b = $(shell echo $(sol_c) | awk '{print $$2}')
da = $(shell echo $(stderr_sol) | awk '{print $$1}')
db = $(shell echo $(stderr_sol) | awk '{print $$2}')

# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET) output

# Rule to run the executable and redirect the output to a file
output : $(TARGET)
	./$(TARGET) > $(OUTPUT)

plot.datafit.svg : data.csv
	@echo " \
	set terminal svg size 800, 600 background 'white'; \
	set output \"$@\"; \
	set xlabel 'Time t (days)'; \
	set ylabel 'Activity y of ThX (relative units)'; \
	set title 'Decay of ThX'; \
	set grid; \
	set zeroaxis; \
	f(x) = exp($(a))*exp(-$(b)*x); \
	fmin(x) = exp($(a)- $(da))*exp(-($(b)+$(db))*x); \
	fmax(x) = exp($(a)+ $(da))*exp(-($(b)-$(db))*x); \
	plot '$<' with errorbars title 'data', \
		 f(x) title 'F(ĉ) = exp($(a))*exp(-$(b)*x)', \
		 fmin(x) title 'F(ĉ-δc) = exp($(a)- $(da))*exp(-($(b)-$(db))*x)', \
		 fmax(x) title 'F(ĉ+δc) = exp($(a)+ $(da))*exp(-($(b)+$(db))*x)'; \
	" | tee log.$@.gpi | gnuplot

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
# -c compile only dont link to executable
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Clean target: Removes all generated files (object files and the executable)
# rm -f: Forcefully remove files without prompting for confirmation
# $(OBJS): Removes all object files
# $(TARGET): Removes the final executable

clean:
	rm -f $(OBJS) $(TARGET) Output.txt plot.datafit.svg log.plot.datafit.svg.gpi

# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean plot.datafit.svg
