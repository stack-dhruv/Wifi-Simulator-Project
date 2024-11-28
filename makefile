CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Executable
TARGET = $(BINDIR)/wifi_simulator

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/*

# Ensure build and bin directories exist
$(shell mkdir -p $(BUILDDIR) $(BINDIR))

.PHONY: all clean