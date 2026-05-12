# ================================================
# Machina - Makefile (Windows CMD optimized) copied from GROK
# ================================================

BUILD_DIR   := build
TARGET      := $(BUILD_DIR)/Machina.exe

CXX         := g++
CXXFLAGS    := -g -O0 -std=c++17 -Wall -Wextra

SRC         := $(wildcard *.cpp)
OBJ         := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean run debug

all: dirs $(TARGET)

# Create build directory
dirs:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

# Linking
$(TARGET): $(OBJ)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
$(BUILD_DIR)/%.o: %.cpp
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@del /q *.o 2>nul
	@cls
	@echo Build files cleaned.

# Run
run: all
	@echo Running...
	@echo -----------------------------------
	@$(TARGET)

# Show debug info
debug:
	@echo Sources: $(SRC)
	@echo Objects: $(OBJ)
	@echo Target : $(TARGET)

# Quick rebuild
rebuild: clean all