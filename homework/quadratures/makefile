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
PYTHONTARGET = main.py

# Source files: List of all source files to be compiled
SRCS = main.cpp quadratureIntegrator.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt

# Datafile
ERFDIFF = erf_difference.csv
ERFINT = erf_int.csv
ERFTAB = erf_tab.csv
ERFAPPROX = erf_approx.csv

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
	. venv/bin/activate; python3 main.py >> $(OUTPUT); deactivate

# Rule to link object files and create the final executable
# $(TARGET): The name of the executable (main)
# $(OBJS): The object files needed to create the executable
# $(CXX): The compiler to use (g++)
# $(CXXFLAGS): Compiler flags (e.g., -Wall, -std=c++23)
# -o $(TARGET): Specifies the output file name for the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)


plot.erf.svg : $(ERFINT) 
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'f(x)'; \
	set title 'Error Function'; \
	plot \"$<\" using 1:2 with lines title 'erf_{int}(x)', \
		 \"$(ERFAPPROX)\" using 1:2 with points pointtype 4 linecolor 3 title 'erf_{approx}(x)', \
	     \"$(ERFTAB)\" using 1:2 with points pointtype 1 linecolor 2 title 'erf_{tabulated}(x)', \
		 \"$(ERFTAB)\" using (\$$1 * -1):(\$$2 * -1) with points pointtype 1 linecolor 2 notitle; \
	" | tee log.$@.gpi | gnuplot

plot.diff.svg : $(ERFDIFF)
	@echo " \
	set terminal svg size 800,600 background 'white'; \
	set output \"$@\"; \
	set grid; \
	set xlabel 'x'; \
	set ylabel 'f(x)'; \
	set title 'Error Function'; \
	plot \"$<\" using 1:2 with points title '|erf_{int}(x)-erf_{tab}(x)|', \
		 \"$<\" using 1:3 with points title '|erf_{approx}(x)-erf_{tab}(x)|'; \
	" | tee log.$@.gpi | gnuplot



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
	rm -f $(OBJS) $(TARGET) $(OUTPUT)

# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean output plot.erf.svg plot.diff.svg
