# Makefile for compiling main.cpp and cleaning up generated files

# Compiler: Specify the C++ compiler to use (g++ in this case) if needed.
# clang maybe
#CXX += g++

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

# Source files: List of all source files to be compiled (only main.cpp here)
SRCS = main.cpp ../includes/matrix.cpp spline.cpp gen.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt

# Datafiles
LSPLICE = lspline.csv
QSPLICE = qspline.csv
CSPLICE = cspline.csv

# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET) output plot.lspline.svg plot.qspline.svg plot.cspline.svg

# Rule to run the executable and redirect the output to a file
output : $(TARGET)
	./$(TARGET) > $(OUTPUT)

plot.lspline.svg : $(LSPLICE)
	@echo "\
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set title 'lspline'; \
	set yrange [-2:2]; \
	plot \"$<\" using 1:2 with linespoints title 'f(x) = cos(x)',\
		 \"$<\" using 1:3 with linespoints title 'F(x) = sin(x)'; \
	" | tee log.$@.gpi | gnuplot

plot.qspline.svg : $(QSPLICE)
	@echo "\
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set title 'qspline'; \
	set yrange [-2:2]; \
	plot \"$<\" using 1:2 with linespoints title 'f(x) = cos(x)', \
		 \"$<\" using 1:3 with linespoints title 'F(x) = sin(x)', \
		 \"$<\" using 1:4 with linespoints title '-cos(x)'; \
	" | tee log.$@.gpi | gnuplot

plot.cspline.svg : $(CSPLICE)
	@echo "\
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set title 'cspline'; \
	set yrange [-2:2]; \
	plot \"$<\" using 1:2 with linespoints title 'f(x) = cos(x)', \
		 \"$<\" using 1:3 with linespoints title 'F(x) = sin(x)', \
		 \"$<\" using 1:4 with linespoints title 'df(x)/dx = -cos(x)'; \
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
	rm -f $(OBJS) $(TARGET) $(OUTPUT) plot.qspline.svg plot.lspline.svg log.plot.qspline.svg.gpi \
	log.plot.lspline.svg.gpi plot.cspline.svg log.plot.cspline.svg.gpi qspline.csv lspline.csv cspline.csv \
	qspline.svg lspline.svg cspline.svg


# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean output plot.lspline.svg plot.qspline.svg plot.cspline.svg
