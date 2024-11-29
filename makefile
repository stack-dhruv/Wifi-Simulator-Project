# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
CXXFLAGS_DEBUG = -std=c++17 -Wall -Wextra -g -DDEBUG
CXXFLAGS_OPT = -std=c++17 -Wall -O3
SRCDIR = src
BUILDDIR = build
BINDIR = bin
LIBDIR = lib

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Shared library
LIBRARY = $(LIBDIR)/libwifi_simulator.so

# Executable targets
TARGET_DEBUG = $(BINDIR)/wifi_simulator_debug
TARGET_OPT = $(BINDIR)/wifi_simulator_opt

# Default target
all: setup $(TARGET_DEBUG) $(TARGET_OPT)

# Run setup script
setup:
	@echo "Running setup script..."
	@chmod +x setup.sh
	@./setup.sh

# Link object files to create executable (debug version)
$(TARGET_DEBUG): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)
	$(CXX) $(CXXFLAGS_DEBUG) $(OBJECTS) -o $@ 
	$(CXX) $(CXXFLAGS_DEBUG) -shared -fPIC -o $(LIBRARY) $(OBJECTS)

# Link object files to create executable (optimized version)
$(TARGET_OPT): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)
	$(CXX) $(CXXFLAGS_OPT) $(OBJECTS) -o $@
	$(CXX) $(CXXFLAGS_OPT) -shared -fPIC -o $(LIBRARY) $(OBJECTS)

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/* $(LIBDIR)/*

# Debug target to print variables
print-%:
	@echo '$*=$($*)'

# Explicit rebuilding of objects is not required
.PHONY: all clean setup print-%

# Ensure build, bin, and lib directories exist
$(shell mkdir -p $(BUILDDIR) $(BINDIR) $(LIBDIR))