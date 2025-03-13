# Makefile for compiling main.cpp and cleaning up generated files

# Compiler: Specify the C++ compiler to use (g++ in this case) if needed.
# clang maybe
CXX = g++ -O2

# Compiler flags: Options passed to the compiler during compilation
# -Wall: Enable all compiler warnings to catch potential issues
# -std=c++23: Use the C++23 standard for compilation
# -Wextra: Extra errors
# -ferror-limit=1: tells the compiler to stop after encountering one error

CXXFLAGS += -Wall -std=c++23

# Linker flags: Libraries to link against (e.g., -lm for math functions)
# -lm → Links libm (Math library)
# -lpthread → Links libpthread (POSIX Threads)
# -lstdc++ → Links libstdc++ (C++ Standard Library)
# -lsqlite3 → Links libsqlite3 (SQLite library)
LDLIBS += -lm -lstdc++

# Target executable: The name of the final executable file to be created
TARGET = main

# Source files: List of all source files to be compiled
SRCS = main.cpp EVD.cpp hydrogen.cpp tests.cpp ../includes/matrix.cpp ../includes/log.cpp
# Output file: The name of the file where the output will be redirected
# Outputs
OUTPUT = Output.txt
EIGEN_DATA = eigenvalues.csv
CONVERGENCE_DATA_DELTA_R = convergenceDeltaR.csv
CONVERGENCE_DATA_DELTA_R_PARALLEL = convergenceDeltaRParallel.csv
CONVERGENCE_DATA_DELTA_RMAX = convergenceDeltaRmax.csv
CONVERGENCE_DATA_DELTA_RMAX_PARALLEL = convergenceDeltaRmaxParallel.csv
RMAX_DATA = rmax.csv

# Define a sequence of test values
DR_VALUES := $(shell seq 0.05 0.05 0.95)  # Δr from 0.1 to 1.0
RMAX_VALUES := $(shell seq 1 0.5 20)     # rmax from 5 to 20

# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET) parallelDeltaRmax parallelDeltaR output mergeLogs plot.eigenvalues.svg plot.convergenceDeltaR.svg plot.convergenceDeltaRmax.svg plot.convergenceDeltaRParallel.svg plot.convergenceDeltaRmaxParallel.svg

plot.eigenvalues.svg : $(EIGEN_DATA)
	echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set xlabel 'Eigenfunctions'; \
	set ylabel 'Eigenvalues'; \
	set title 'QR Factorization Complexity'; \
	set grid; \
	set key right; \
	set zeroaxis; \
	set xrange [0:60]; \
	f1(x) = 2*x*exp(-x); \
	f2(x) = -x*(1-x/2)*exp(-x/2)/sqrt(2); \
	f3(x) = 2*x*(1-2*x/3 + 2*x*x/27)*exp(-x/3)/sqrt(27); \
	f4(x) = (1.0/4.0) * x * (1.0 - (3.0/4.0)*x + (1.0/8.0)*(x**2) - (1.0/192.0)*(x**3)) * exp(-x/4.0); \
	plot '$<' using 1:2 with points title 'ψ1-numerical', \
		 '$<' using 1:3 with points title 'ψ2-numerical', \
		 '$<' using 1:4 with points title 'ψ3-numerical', \
		 '$<' using 1:5 with points title 'ψ4-numerical', \
		 f1(x) with lines title 'ψ1-analytical', \
		 f2(x) with lines title 'ψ2-analytical', \
		 f3(x) with lines title 'ψ3-analytical', \
		 f4(x) with lines title 'ψ4-analytical'; \
	" | tee log.$(EIGEN_DATA).gpi | gnuplot

plot.convergenceDeltaR.svg : $(CONVERGENCE_DATA_DELTA_R)
	echo "\
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set title 'ε0 of Δr'; \
	set xlabel 'Δr'; \
	set ylabel 'ε0'; \
	set grid; \
	set yrange [-0.51:-0.41]; \
	set xrange [0:1]; \
	plot '$<' with linespoints title 'ε0 of Δr datapoints'; \
	" | tee log.$(CONVERGENCE_DATA_DELTA_R).gpi | gnuplot

plot.convergenceDeltaRmax.svg : $(CONVERGENCE_DATA_DELTA_RMAX)
	echo "\
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set title 'ε_0 of r_{max}'; \
	set xrange [2:12]; \
	set xlabel 'r_{max}'; \
	set ylabel 'ε_0'; \
	set grid; \
	plot '$<' with linespoints title 'ε0 of Δrmax datapoints'; \
	" | tee log.$(CONVERGENCE_DATA_DELTA_RMAX).gpi | gnuplot

plot.convergenceDeltaRParallel.svg : $(CONVERGENCE_DATA_DELTA_R_PARALLEL)
	echo "\
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set title 'ε0 of Δr'; \
	set xlabel 'Δr'; \
	set ylabel 'ε0'; \
	set grid; \
	set yrange [-0.51:-0.41]; \
	set xrange [0:1]; \
	plot '$<' with points title 'ε0 of Δr datapoints'; \
	" | tee log.$(CONVERGENCE_DATA_DELTA_R_PARALLEL).gpi | gnuplot

plot.convergenceDeltaRmaxParallel.svg : $(CONVERGENCE_DATA_DELTA_RMAX_PARALLEL)
	echo "\
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set title 'ε_0 of r_{max}'; \
	set xrange [2:12]; \
	set xlabel 'r_{max}'; \
	set ylabel 'ε_0'; \
	set grid; \
	plot '$<' with points title 'ε0 of Δrmax datapoints'; \
	" | tee log.$(CONVERGENCE_DATA_DELTA_RMAX_PARALLEL).gpi	| gnuplot

# Rule to run the executable and redirect the output to a file
output : $(TARGET)
	./$(TARGET) > $(OUTPUT) -rut; ./$(TARGET) >> $(OUTPUT) -hs 80,0.2

parallelDeltaR : $(TARGET)
	@> $(CONVERGENCE_DATA_DELTA_R_PARALLEL)
	@for dr in $(DR_VALUES); do \
		(time -ao log.dr.$$dr -f "$$dr %e" ./$(TARGET) -ddr $$dr & ); \
	done

# Measure convergence with rmax
parallelDeltaRmax: $(TARGET)
	@> $(CONVERGENCE_DATA_DELTA_RMAX_PARALLEL)
	@for rmax in $(RMAX_VALUES); do \
		(time -ao log.rmax.$$rmax -f "$$rmax %e" ./$(TARGET) -ddrm $$rmax & ); \
	done
	

mergeLogs : 
	@echo "Running convergence for Δr in parallel..." >> $(OUTPUT)
	@echo "Δr   time(s)" >> $(OUTPUT)
	@for dr in $(DR_VALUES); do cat log.dr.$$dr >> $(OUTPUT); done; wait
	@$(RM) log.dr.*

	@echo "Running convergence for rmax in parallel..." >> $(OUTPUT)
	@echo "rmax time(s)" >> $(OUTPUT)
	@for rmax in $(RMAX_VALUES); do cat log.rmax.$$rmax >> $(OUTPUT); done; wait
	@$(RM) log.rmax.*



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
	rm -f $(OBJS) $(TARGET) $(OUTPUT) $(EIGEN_DATA) $(CONVERGENCE_DATA_DELTA_R) $(CONVERGENCE_DATA_DELTA_RMAX) $(RMAX_DATA) \
	log.convergenceDeltaR.csv.gpi log.convergenceDeltaRmax.csv.gpi log.eigenvalues.csv.gpi plot.convergenceDeltaR.svg \
	plot.convergenceDeltaRmax.svg plot.eigenvalues.svg convergenceDeltaRmaxParallel.csv convergenceDeltaRParallel.svg log. \
	log.convergenceDeltaRmaxParallel.csv.gpi log.convergenceDeltaRParallel.csv.gpi plot.convergenceDeltaRParallel.svg \
	plot.convergenceDeltaRmaxParallel.svg convergenceDeltaRParallel.csv

# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean plot.eigenvalues.svg plot.convergenceDeltaR.svg plot.convergenceDeltaRmax.svg
