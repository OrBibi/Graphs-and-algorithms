#orbibiariel@gmail.com

# Compiler settings
CXX = g++  # The C++ compiler
CXXFLAGS = -Wall -g -std=c++11 -Itests -Isrc  # Compiler flags: Enable warnings, debug info, C++11, and include paths for tests and source files
LDFLAGS = -L/usr/local/lib  # Linker flags for library locations

# Source files
SRC = src/Algorithms.cpp src/Graph.cpp src/Queue.cpp src/Vector.cpp src/UnionFind.cpp 
TEST_SRC = tests/test_graph.cpp  
DOCTEST_HEADER = tests/doctest.h  
MAIN_SRC = src/main.cpp  

# Object files
OBJ = $(SRC:.cpp=.o) $(TEST_SRC:.cpp=.o)  
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)  

# Build the test_graph executable (this runs the unit tests)
test_graph: $(OBJ)  
	$(CXX) $(CXXFLAGS) -o test_graph $(OBJ)  

# Run the unit tests
test: test_graph  
	./test_graph  # Execute the test_graph program

# Build the main_program executable (this runs the main program)
main_program: $(SRC) $(MAIN_OBJ)  
	$(CXX) $(CXXFLAGS) -o main_program $(SRC) $(MAIN_OBJ)  

# Build and run the main program
Main: main_program  
	./main_program  

# Build the test_graph executable (default target)
all: test_graph  

# Clean up generated files (executables and object files)
clean:  
	rm -f test_graph $(OBJ) $(MAIN_OBJ) main_program  

# Run valgrind on the test_graph executable to check for memory leaks
valgrind: test_graph  
	valgrind --leak-check=full ./test_graph  