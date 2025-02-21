# Makefile for compiling main.cpp and cleaning up generated files

# Compiler: Specify the C++ compiler to use (g++ in this case) if needed.
# CXX = g++ 

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

# Source files: List of all source files to be compiled (only main.cpp here)
SRCS = main.cpp includes/functions.cpp

# Output file: The name of the file where the output will be redirected
OUTPUT = Output.txt

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
	@echo "-1	-0.842700793\n-0.4	-0.428392355\n0 0\n0.4	0.428392355\n1	0.842700793" > erfData.txt

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

plot.erf.svg : Output.txt erfData.txt
		echo " \
	  set terminal svg background 'white'; \
	  set output \"$@\"; \
	  set zeroaxis; \
	  plot \
	   \"$<\" index 0 with lines title \"erf(x)\" \
	   , \"erfData.txt\" with points title \"Tabulated erf(x)\"; \
	" | tee log.erf.gpi | gnuplot

plot.gamma.svg : Output.txt
		echo " \
        set terminal svg background 'white'; \
		set zeroaxis lt -1; \
		set xtics axis; \
		set ytics axis; \
        set output \"$@\"; \
		set key bottom right; \
		set title 'Gamma function'; \
		set arrow from 0, graph 0 to 0, graph 1 nohead lw 2 lc rgb 'blue' dashtype 2; \
		set arrow from -1, graph 0 to -1, graph 1 nohead lw 2 lc rgb 'blue' dashtype 2; \
		set arrow from -2, graph 0 to -2, graph 1 nohead lw 2 lc rgb 'blue' dashtype 2; \
		set arrow from -3, graph 0 to -3, graph 1 nohead lw 2 lc rgb 'blue' dashtype 2; \
		set arrow from -4, graph 0 to -4, graph 1 nohead lw 2 lc rgb 'blue' dashtype 2; \
        plot [-5:5][-5:5]\
            \"$<\" index 1 with lines lw 2 lc rgb 'red' title 'Gamma(x)' \
            , \"$<\" index 3 with points title 'factorial of N'; \
    " | tee log.gamma.gpi | gnuplot

plot.lngamma.svg : Output.txt
		echo " \
        set terminal svg background 'white'; \
		set zeroaxis lt -1; \
		set xtics axis; \
		set ytics axis; \
        set output \"$@\"; \
		set key bottom right; \
		set title 'Gamma function'; \
        plot [0:5][-1:5]\
            \"$<\" index 2 with lines lw 2 lc rgb 'red' title 'Gamma(x)'; \
    " | tee log.lngamma.gpi | gnuplot

# set palette rgb 33,13,10;
# Custom HSV palette: cyan → blue → magenta → red → yellow → green → cyan
plot.complexGamma.svg : Output.txt
	echo "\
	set terminal svg background 'white'; \
	set output \"complex_gamma_surface_plot.svg\"; \
	set xlabel \"Re(z)\"; \
	set ylabel \"Im(z)\"; \
	set zlabel \"|Gamma(z)|\"; \
	set xrange [-5:5]; \
	set yrange [-5:5]; \
	set zrange [0:6]; \
	set cbrange [-pi:pi]; \
	set pm3d interpolate 0,0; \
	set pm3d corners2color c1; \
	set pm3d at s; \
	set palette model HSV functions (gray + 0.5 - int(gray + 0.5)), 0.8, 0.9; \
	set view 60, 330; \
	set xyplane relative 0; \
	splot \"Output.txt\" using 1:2:3:4 with pm3d notitle; \
	" | tee log.complexGamma.gpi | gnuplot

plot.complexGamma.png : Output.txt
	echo "\
	set terminal png background 'white'; \
	set output \"complex_gamma_surface_plot.png\"; \
	set xlabel \"Re(z)\"; \
	set ylabel \"Im(z)\"; \
	set zlabel \"|Gamma(z)|\"; \
	set xrange [-5:5]; \
	set yrange [-5:5]; \
	set zrange [0:6]; \
	set cbrange [-pi:pi]; \
	set pm3d interpolate 0,0; \
	set pm3d corners2color c1; \
	set pm3d at s; \
	set palette model HSV functions (gray + 0.5 - int(gray + 0.5)), 0.8, 0.9; \
	set view 60, 330; \
	set xyplane relative 0; \
	splot \"Output.txt\" using 1:2:3:4 with pm3d notitle; \
	" | tee log.complexGamma.png.gpi | gnuplot

# Clean target: Removes all generated files (object files and the executable)
# rm -f: Forcefully remove files without prompting for confirmation
# $(OBJS): Removes all object files
# $(TARGET): Removes the final executable
clean:
	rm -f $(OBJS) $(TARGET) Output.txt plot.gamma.svg plot.test.svg log.gamma.gpi erfData.txt plot.erf.svg log.erf.gpi test.gpi data.txt \
	log.gamma.gpi plot.complexGamma.svg gamma_surface_plot.svg log.complexGamma.gpi plot.lngamma.svg log.lngamma.gpi \
	complex_gamma_surface_plot.svg complex_gamma_surface_plot.png log.complexGamma.png.gpi

# Phony targets: Targets that are not actual files but are used as commands
# all: The default target to build the executable
# clean: The target to clean up generated files
.PHONY: all clean
