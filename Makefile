# Toolchain prefix
TOOLCHAIN ?= arm-none-eabi-
CC      = $(TOOLCHAIN)gcc
CXX     = $(TOOLCHAIN)g++
LD      = $(TOOLCHAIN)g++
OBJCOPY = $(TOOLCHAIN)objcopy
SIZE    = $(TOOLCHAIN)size

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Find all source files
C_SOURCES   = $(shell find $(SRC_DIR) -name '*.c')
CPP_SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')

# Object files output structure
C_OBJS   = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CPP_OBJS = $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS     = $(C_OBJS) $(CPP_OBJS)

# Target output binary name
TARGET = $(BUILD_DIR)/output.elf

# Compilation Flags (Targeting VEX V5 ARM Cortex-A9)
ARCH_FLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard
CFLAGS     = $(ARCH_FLAGS) -O2 -Wall -g -I$(INC_DIR)
CXXFLAGS   = $(ARCH_FLAGS) -O2 -Wall -g -std=c++11 -I$(INC_DIR)
LDFLAGS    = $(ARCH_FLAGS) -lm -lc -lgcc

# Default Build Rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

# Compile C source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
