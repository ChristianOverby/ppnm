# Makefile for compiling main.cpp and cleaning up generated files

# Compiler: Specify the C++ compiler to use (g++ in this case) if needed.
# clang maybe
CXX = g++ -O2

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
SRCS = main.cpp ../includes/matrix.cpp ../includes/vmatrix.cpp QRGS.cpp tests.cpp ../includes/log.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt
PLOT_DATA_OUTPUT = benchmark.csv

# Object files: List of object files to be generated from the source files
# This replaces the .cpp extension with .o for each source file
# $(patsubst pattern, replacement, text)`: This Make function performs pattern substitution.
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# Default target: The target that will be built when you run `make` without arguments
# It depends on the $(TARGET) rule, which will build the executable
all: $(TARGET) output

plot.benchmark.svg : $(PLOT_DATA_OUTPUT)
	@echo " \
		set terminal svg background 'white'; \
		set output \"$@\"; \
		set xlabel 'Matrix Size N'; \
		set ylabel 'Time (seconds)'; \
		set title 'QR Factorization Complexity'; \
		set grid; \
		set key left top; \
		set zeroaxis; \
		f(x) = a * x**3; \
		fit f(x) '$<' using 1:2 via a; \
		plot '$<' using 1:2 with points title 'Measured Time', \
		     f(x) with lines title 'O(N³) Fit'; \
	" | tee log.benchmark.gpi | gnuplot
# Target: $(PLOT_DATA_OUTPUT)
# This target measures the execution time of QR-factorizing an NxN matrix
# for various values of N and stores the results in $(PLOT_DATA_OUTPUT).
# awk line to divide the recorded time by 2 since it's run twice
# add line for more repititions... awk -v n=$$N '{ if ($$1 == n) $$2 = $$2 / $(REPETITIONS); print $$1, $$2; }' $@ > temp && mv temp $@;
REPETITIONS = 1
$(PLOT_DATA_OUTPUT): $(TARGET)
	> $@
	for N in $$(seq 100 10 700); do \
		time --format="$$N %e" --output=$@ --append ./$(TARGET) -ssq $$N,$(REPETITIONS); \
	done

# Rule to run the executable and redirect the output to a file
output : $(TARGET)
	./$(TARGET) -rut > $(OUTPUT)
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
	rm -f $(OBJS) $(TARGET) Output.txt output.txt outputData.txt \
	inputData.txt $(PLOT_DATA_OUTPUT) plot.benchmark.svg log.benchmark.gpi fit.log err out

# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean
