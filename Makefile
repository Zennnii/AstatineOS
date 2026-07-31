CC = x86_64-elf-gcc
AS = nasm

CFLAGS = -Iinclude \
         -Ilimine \
         -ffreestanding \
         -fno-stack-protector \
         -fno-pic \
         -fno-asynchronous-unwind-tables \
         -fno-unwind-tables \
         -mno-red-zone \
         -m64 \
         -mcmodel=kernel \
         -Wall \
         -Wextra

ASFLAGS = -f elf64

LDFLAGS = -nostdlib -static -no-pie -T linker.ld

BUILD_DIR = build/kernel

C_SRCS := $(shell find src -name '*.c')
ASM_SRCS := $(shell find src -name '*.asm')

C_OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))
ASM_OBJS := $(patsubst src/%.asm,$(BUILD_DIR)/%.o,$(ASM_SRCS))

OBJS := $(C_OBJS) $(ASM_OBJS)

all: $(BUILD_DIR)/kernel.elf

$(BUILD_DIR)/kernel.elf: $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

# c files
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# assembly files
$(BUILD_DIR)/%.o: src/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean