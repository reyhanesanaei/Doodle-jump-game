CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS ?= -lsfml-graphics -lsfml-window -lsfml-system

SOURCES := main.cpp $(shell find src -name '*.cpp')
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := DoodleJump

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
