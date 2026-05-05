# Makefile for sam3x8e -- runs inside the sam3x8e-build Docker container.
# Targets: all (default), compile_commands, clean

ARCH       := sam3x8e
SRC_DIR    := src
BUILD_DIR  := obj/$(ARCH)
DIST_DIR   := out/$(ARCH)
TARGET_DIR := arch/$(ARCH)
VENDOR_DIR := vendor

CC      := arm-none-eabi-gcc
LD      := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy

CFLAGS  := -mcpu=cortex-m3 -mthumb -ffreestanding -mno-unaligned-access \
           -I$(SRC_DIR) \
           -I$(VENDOR_DIR)/sam/include \
           -I$(VENDOR_DIR)/cmsis/include \
           -D__SAM3X8E__

LDFLAGS := -T $(TARGET_DIR)/linker.ld --gc-sections

FIRMWARE_ELF := $(DIST_DIR)/firmware.elf
FIRMWARE_BIN := $(DIST_DIR)/firmware.bin

C_SOURCES := $(shell find $(SRC_DIR) -name '*.c')
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
OBJECTS   := $(C_OBJECTS)

.PHONY: all compile_commands clean

all: $(FIRMWARE_BIN)

$(FIRMWARE_BIN): $(FIRMWARE_ELF)
	$(OBJCOPY) -O binary $< $@

$(FIRMWARE_ELF): $(OBJECTS)
	mkdir -p $(DIST_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# requires bear (installed in the Docker image)
compile_commands:
	bear -- make -f make/Makefile all

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)
