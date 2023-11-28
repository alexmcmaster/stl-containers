# Makefile

# Compiler to use
CXX := g++

# Compiler flags
CXXFLAGS := -Iinclude -Wall -std=c++11

# Source directory
SRCDIR := src

# Object files directory
OBJDIR := obj

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Executable name
EXECUTABLE := run_analysis

# Default target
all: $(EXECUTABLE)

# Linking the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object files directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean target
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
