# C++ 项目
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
LDFLAGS  = -lraylib -lm 
LDLIBS   = -lpthread

SRC_DIR   = src
INC_DIR   = include
BUILD_DIR = build
BIN_DIR   = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET  = $(BIN_DIR)/doublePendulum

CPPFLAGS = -I$(INC_DIR)

all: $(TARGET)

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

rebuild: clean all

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O3 -DNDEBUG
release: all

run: $(TARGET)
	./$(TARGET)

depend: $(SOURCES)
	$(CXX) $(CPPFLAGS) -MM $^ > .depend

-include .depend

.PHONY: all clean rebuild debug release run depend
