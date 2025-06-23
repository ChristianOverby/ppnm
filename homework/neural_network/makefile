# Makefile for compiling main.cpp and cleaning up generated files

# Compiler: Specify the C++ compiler to use (g++ in this case) if needed.
# clang maybe
CXX += -O2

# Compiler flags: Options passed to the compiler during compilation
# -Wall: Enable all compiler warnings to catch potential issues
# -std=c++23: Use the C++23 standard for compilation
# -Wextra: Extra errors
# --fmax-errors=1: tells the compiler to stop after encountering one error

CXXFLAGS += -Wall -Wextra -std=c++23

# Linker flags: Libraries to link against (e.g., -lm for math functions)
# -lm → Links libm (Math library)
# -lpthread → Links libpthread (POSIX Threads)
# -lstdc++ → Links libstdc++ (C++ Standard Library)
# -lsqlite3 → Links libsqlite3 (SQLite library)
LDLIBS += -lm -lstdc++

# Target executable: The name of the final executable file to be created
TARGET = main

# Source files: List of all source files to be compiled
SRCS = main.cpp ../includes/matrix.cpp ann.cpp ../minimisation/minimiser.cpp ../linear_equations/QRGS.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt
# Extract the first value of column 8 from ann_results.csv
FIRST_VAL=$(shell awk 'NR==1 {print $$6}' ann_approximation.csv)

# Datafile
ANNDATA = ann_approximation.csv

# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET) output plot.ann.svg

# Rule to run the executable and redirect the output to a file
output : $(TARGET)
	./$(TARGET) > $(OUTPUT)

plot.ann.svg : $(ANNDATA)
	@echo " \
	set terminal svg size 1200,900 background 'white'; \
	set output \"$@\"; \
	set multiplot layout 2,2 title 'ANN function approximations'; \
	set grid; \
	set title 'Ann f(x) approximation'; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set zeroaxis; \
	set samples 1500; \
	f(x) = cos(5*x-1)*exp(-x*x); \
	plot f(x) with lines title 'Analytical function', \
			 '$<' using 1:2 with points title 'Training data', \
			 '$<' using 1:3 with lines title 'ANN approximation'; \
	set title 'Ann derivative f(x) approximation'; \
	set xlabel 'x'; \
	set key top right; \
	plot '$<' using 1:4 with lines title 'ANN derivative approximation'; \
	set title 'Ann 2nd derivative f(x) approximation'; \
	set xlabel 'x'; \
	plot '$<' using 1:5 with lines title 'ANN 2nd derivative approximation'; \
	set title 'Ann integral f(x) approximation'; \
	set xlabel 'x'; \
	plot '$<' using 1:6 with lines title 'ANN integral approximation'; \
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
	rm -f $(OBJS) $(TARGET) $(OUTPUT) log.plot.ann.svg.gpi ann_approximation.csv plot.ann.svg log.plot.2ann.svg.gpi

# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean output plot.ann.svg plot.2ann.svg 
