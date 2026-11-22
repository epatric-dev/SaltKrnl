BUILD_DIR ?= ../build/kernel
CXX ?= clang++
CC ?= clang
LD ?= ld.lld
OBJCOPY ?= objcopy

CXXFLAGS := -target x86_64-unknown-none-elf -ffreestanding -fno-exceptions \
    -fno-rtti -fno-stack-protector -fno-pic -fno-pie -mno-red-zone \
    -mno-sse -mno-mmx -std=c++17 -Wall -Wextra
ASFLAGS := -target x86_64-unknown-none-elf
LDFLAGS := -m elf_x86_64 -nostdlib -T linker.ld

KERNEL_O := $(BUILD_DIR)/main.o
START_O := $(BUILD_DIR)/start.o
KERNEL_ELF := $(BUILD_DIR)/kernel.elf
KERNEL_BIN := $(BUILD_DIR)/kernel.bin

.PHONY: all clean

all: $(KERNEL_BIN)

$(BUILD_DIR):
	@mkdir -p $@

$(KERNEL_O): main.cpp | $(BUILD_DIR)
	@echo "  CXX $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(START_O): start.S | $(BUILD_DIR)
	@echo "  AS  $@"
	@$(CC) $(ASFLAGS) -c $< -o $@

$(KERNEL_ELF): $(START_O) $(KERNEL_O) linker.ld
	@echo "  LD  $@"
	@$(LD) $(LDFLAGS) $(START_O) $(KERNEL_O) -o $@

$(KERNEL_BIN): $(KERNEL_ELF)
	@echo "  BIN $@"
	@$(OBJCOPY) -O binary $< $@

clean:
	@rm -rf $(BUILD_DIR)
