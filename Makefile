# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O0 -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/app

IGNORE = LinkedList_withObject.cpp

SRCS = $(filter-out $(SRC_DIR)/$(IGNORE), $(wildcard $(SRC_DIR)/*.cpp))

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)
	@$(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean