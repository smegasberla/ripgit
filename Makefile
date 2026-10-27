# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc/include

# Directories
BIN_DIR = bin
SRC_DIR = src

# Target executable name
TARGET = $(BIN_DIR)/ripgit

# Source files (main.cpp in root, plus any additional files in src if needed)
SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp)

# Object files mirrored into BIN_DIR (e.g. main.cpp -> bin/main.o, src/common.cpp -> bin/src/common.o)
OBJS = $(addprefix $(BIN_DIR)/,$(SRCS:.cpp=.o))

# Default rule (runs clean first, then creates dir and builds target)
all: clean $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files under BIN_DIR, creating subdirs as needed
$(BIN_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts: wipe bin/, and sweep the whole tree for any
# stray .o/.obj files or old binaries left outside bin/ by previous builds
clean:
	rm -rf $(BIN_DIR)
	find . -path ./$(BIN_DIR) -prune -o \( -name '*.o' -o -name '*.obj' \) -print -exec rm -f {} +
	@if [ -f ripgit ]; then rm -f ripgit; fi

.PHONY: all clean
