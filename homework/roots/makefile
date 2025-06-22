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
SRCS = main.cpp roots.cpp ../includes/matrix.cpp ../linear_equations/QRGS.cpp ../ode/odeint.cpp ../splines/spline.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt

# Datafile
WAVEFUN = wavefunction_interpolated.csv
CONV = convergence.csv

# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET) output plot.wavefunction.svg plot.convergence.svg

# Rule to run the executable and redirect the output to a file
output : $(TARGET)
	./$(TARGET) > $(OUTPUT)

# Plot Wavefunction
plot.wavefunction.svg : $(WAVEFUN)
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'r(Bohr radia)'; \
	set ylabel 'Radial probability'; \
	set title 'Numerical and analytical wavefunction'; \
	f(x) = x*exp(-x); \
	plot \"$<\" using 1:2 with points title 'Numerical wavefunction', \
		 f(x) with lines title 'Analytical wavefunction'; \
	" | tee log.$@.gpi | gnuplot

plot.convergence.svg : $(CONV)
	@echo " \
	set terminal svg size 1200,900 background 'white'; \
	set output \"$@\"; \
	set multiplot layout 2,2 title 'Convergence plots'; \
	set grid; \
	set title 'E0(rmin)'; \
	set xlabel 'rmin'; \
	set ylabel 'E0'; \
	set key top left; \
	f(x) = x*exp(-x); \
	plot \"$<\" using 1:5 with points title 'E0(rmin)', \
		 -0.5 lt -1 linecolor 'red' title 'Analytical E0'; \
	set xrange [0:10]; \
	set yrange [-1:2.5]; \
	set title 'E0(rmax)'; \
	set xlabel 'rmax'; \
	set key top right; \
	plot \"$<\" using 2:6 with points title 'E0(rmax)', \
		 -0.5 lt -1 linecolor 'red' title 'Analytical E0'; \
	set xrange [*:*]; \
	set yrange [-0.49:-0.51]; \
	set logscale x; \
	set title 'E0(acc)'; \
	set xlabel 'acc'; \
	plot \"$<\" using 3:7 with points title 'E0(acc)', \
		 -0.5 lt -1 linecolor 'red' title 'Analytical E0'; \
		 set xrange [1000:10e-10]; \
	set yrange [-0.49:-0.51]; \
	set xrange [*:*]; \
	set logscale x; \
	set title 'E0(eps)'; \
	set xlabel 'eps'; \
	plot \"$<\" using 4:8 with points title 'E0(eps)', \
		 -0.5 lt -1 linecolor 'red' title 'Analytical E0'; \
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
	rm -f $(OBJS) $(TARGET) $(OUTPUT) $(WAVEFUN) $(CONV) plot.wavefunction.svg plot.convergence.svg log.plot.wavefunction.svg.gpi log.plot.convergence.svg.gpi
 
# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean output plot.wavefunction.svg plot.convergence.svg 
