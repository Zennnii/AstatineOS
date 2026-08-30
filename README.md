# Astatine OS
Astatine is a hobby operating system written in C and x86_64 assembly that boots via the Limine bootloader.
The goal of this project is to build a custom operating system from the ground up while learning low-level programming, computer architecture, and kernel development.

## Current features:

**Implemented:**

- x86_64 kernel with Limine boot support
- Basic framebuffer and serial output
- Interrupt and exception handling
- Architecture initialization and CPU support
- Kernel utility and memory functions
- Basic hardware I/O

**Planned:**

- TSS
- Keyboard drivers
- Memory management
- Virtual memory
- Filesystem support
- Userspace programs

## Building

### Requirements

You need:

- `x86_64-elf-gcc`
- `x86_64-elf-binutils`
- `make`
- `xorriso`
- `qemu-system-x86_64`

### Build

Clone the repository:

```bash
git clone https://github.com/Zennnii/AstatineOS.git
cd AstatineOS
```

Building the kernel:

```bash
make
```

Create the bootable ISO:
```bash
./build.sh
```

## Running

To build and run with qemu:
```bash
./build.sh --run
```

For now the kernel outputs debug messages through COM1 serial.

## Architecture

Astatine currently targets:

- Architecture: x86_64
- Bootloader: Limine
- Language: C
- Compiler: x86_64-elf-gcc

The kernel is built as a freestanding environment without a standard library.

## Third-party Software

Astatine uses the following third-party software:

### Limine Bootloader

Astatine uses the Limine bootloader to boot the kernel.

- Version: v8.7.0
- Repository: https://github.com/limine-bootloader/limine
- License: BSD 2-Clause License

The Limine bootloader is not part of Astatine OS and is licensed separately.
The build script automatically downloads Limine if it is not already present.

## License

Astatine is licensed under the GNU General Public License v2.0.
See the [license](LICENSE) file for details.

Third-party components included or downloaded by the build system may have their own licenses.