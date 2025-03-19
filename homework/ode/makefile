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

# Source files: List of all source files to be compiled
SRCS = main.cpp ../includes/matrix.cpp odeint.cpp ../splines/spline.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt
# Datafile
HARMOSCILLATOR = harmosc.csv
LOTKAVOLTERRA = lotkaVolterra.csv
LOTKAVOLTERRAINTERPOLATED = lotkaVolterraInterpolated.csv
DAMPEDOSCILLATIONS = dampedOscillations.csv
ORBITS = orbits.csv
THREEBODYPROBLEM = threeBodyProblem.csv
# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET) output plot.harmoscil.svg plot.lotkaVolterra.svg plot.dampedOsc.svg plot.lotkaVolterraInterpolated.svg plot.orbits.svg plot.threeBodyProblem.svg

# Rule to run the executable and redirect the output to a file
output : $(TARGET)
	./$(TARGET) > $(OUTPUT)

plot.harmoscil.svg : $(HARMOSCILLATOR)
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set title 'Harm oscilator'; \
	plot \"$<\" using 1:2 with linespoints title 'y = cos(x)', \
		 \"$<\" using 1:3 with linespoints title 'dy = -sin(x)'; \
	" | tee log.$@.gpi | gnuplot

plot.lotkaVolterra.svg : $(LOTKAVOLTERRA) 
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 't'; \
	set ylabel 'size'; \
	set title 'lotka volterra equations'; \
	plot \"$<\" using 1:2 with linespoints title 'x', \
		 \"$<\" using 1:3 with linespoints title 'y'; \
	" | tee log.$@.gpi | gnuplot

plot.lotkaVolterraInterpolated.svg : $(LOTKAVOLTERRAINTERPOLATED)
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 't'; \
	set ylabel 'size'; \
	set title 'lotka volterra equations interpolated'; \
	plot \"$<\" using 1:2 with points title 'x', \
		 \"$<\" using 1:3 with points title 'y'; \
	" | tee log.$@.gpi | gnuplot

plot.dampedOsc.svg : $(DAMPEDOSCILLATIONS) 
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 't'; \
	set ylabel 'size'; \
	set title 'Damped oscilator'; \
	plot \"$<\" using 1:2 with linespoints title 'theta(t)', \
		 \"$<\" using 1:3 with linespoints title 'omega(t)'; \
	" | tee log.$@.gpi | gnuplot

plot.orbits.svg : $(ORBITS) 
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set size ratio -1; \
	set title 'Planetary orbits'; \
	plot \"$<\" using (1/column(2))*cos(column(1)):(1/column(2))*sin(column(1)) with lines title 'Circular', \
		 \"$<\" using (1/column(3))*cos(column(1)):(1/column(3))*sin(column(1)) with lines title 'Elliptical', \
		 \"$<\" using (1/column(4))*cos(column(1)):(1/column(4))*sin(column(1)) with lines title 'Relativistic'; \
	" | tee log.$@.gpi | gnuplot

plot.threeBodyProblem.svg : $(THREEBODYPROBLEM) 
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'y'; \
	set size ratio -1; \
	set title 'Three Body Problem'; \
	plot \"$<\" using 2:3 with lines title 'Planet 1', \
		 \"$<\" using 4:5 with lines title 'Planet 2', \
		 \"$<\" using 6:7 with lines title 'Planet 3', \
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
	rm -f $(OBJS) $(TARGET) $(OUTPUT) plot.harmoscil.svg plot.lotkaVolterra.svg log.plot.lotkaVolterra.svg.gpi \
	log.plot.harmoscil.svg.gpi $(DAMPEDOSCILLATIONS) $(LOTKAVOLTERRAINTERPOLATED) $(LOTKAVOLTERRA) $(HARMOSCILLATOR) \
	$(THREEBODYPROBLEM) plot.dampedOsc.svg plot.threeBodyProblem.svg


# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean output
