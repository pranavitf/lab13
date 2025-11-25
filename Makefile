# Makefile for Lab 13

# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Target executable name
TARGET = lab13

# Source files
SRCS = lab13.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the program
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean