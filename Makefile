CC = x86_64-elf-gcc

CFLAGS = -Iinclude \
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

LDFLAGS = -nostdlib -static -no-pie -T linker.ld

BUILD_DIR = build/kernel

SRCS := $(shell find src -name '*.c')
OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR)/kernel.elf

$(BUILD_DIR)/kernel.elf: $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean