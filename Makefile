# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc/include

# Directories
BIN_DIR = bin
SRC_DIR = src

# Target executable
TARGET = $(BIN_DIR)/ripgit

# Source files
SRCS_ROOT = main.cpp
SRCS_SUB = $(wildcard $(SRC_DIR)/*.cpp)

# Map all object files directly into the bin/ directory
OBJS = $(BIN_DIR)/main.o $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS_SUB))

# Default rule
all: $(BIN_DIR) $(TARGET)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile root source files (like main.cpp) into bin/
$(BIN_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile src/ source files into bin/
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts inside bin/
clean:
	rm -rf $(BIN_DIR)/*

.PHONY: all clean
