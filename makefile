# Directories
BUILD_DIR = obj
SRC_DIR = src
LIB_DIR = lib

# Compiler
CXX = clang++

# Flags: Compile, more warnings, use C++17, enable debugging symbols and include path
CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++17 -g -fstandalone-debug -I$(LIB_DIR)

# Binaries
TARGET = binary
TESTS = tests

# Source
CPP_SOURCE = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/test.cpp, $(wildcard $(SRC_DIR)/*))
 
# Headers
HPP_SOURCE = $(wildcard $(LIB_DIR)/*)
 
# Objects
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(BUILD_DIR),$(CPP_SOURCE)))
 
# Command used at clean target
RM = rm -rf
 
# Compilation and linking
all: obj $(TARGET) test

$(TARGET): $(OBJ) ./$(BUILD_DIR)/main.o
	$(CXX) $^ -o $@
 
./$(BUILD_DIR)/main.o: ./$(SRC_DIR)/main.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@

test: obj $(TESTS)

$(TESTS): $(OBJ) $(BUILD_DIR)/test.o
	$(CXX) $^ -lgtest -o $@
	./$(TESTS)

./$(BUILD_DIR)/test.o: ./$(SRC_DIR)/test.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@

./$(BUILD_DIR)/%.o: ./$(SRC_DIR)/%.cpp ./$(LIB_DIR)/%.hpp
	$(CXX) $< $(CXXFLAGS) -o $@
 
obj:
	@ test -d $(BUILD_DIR) && true || mkdir -p $(BUILD_DIR)
 
clean:
	@ $(RM) ./$(BUILD_DIR)/*.o $(TARGET) $(TESTS) *~
	@ test -d $(BUILD_DIR) && rmdir $(BUILD_DIR) || true
 
.PHONY: all clean obj test
