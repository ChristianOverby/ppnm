# Rule to build output.exe from test.cpp
output.exe : test.cpp
	g++ test.cpp -o output.exe

# Phony target to clean up generated files
.PHONY : clean
clean:
	rm --force output.exe
