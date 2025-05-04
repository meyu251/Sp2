# author: Meir Yust
# mail: meyu251@gmail.com

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Target executables
MAIN_TARGET = main_exec
TEST_TARGET = test_exec

# Source files
MAIN_SRC = main.cpp Graph.cpp Algorithms.cpp
TEST_SRC = test_main.cpp Graph.cpp Algorithms.cpp

# Object files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Header files
HEADERS = Graph.hpp Algorithms.hpp Data_Structures.hpp

.PHONY: all Main test valgrind clean

all: $(MAIN_TARGET) $(TEST_TARGET)

# Main executable
$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test executable
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generic rule for object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the main program
Main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Run the test program
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run valgrind on the main program
valgrind: $(MAIN_TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(MAIN_TARGET)

# Clean up
clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET) *.o