#!/bin/bash
set -e

# dependency checks
dependencies=(
    git
    make
    xorriso
    qemu-system-x86_64
    x86_64-elf-gcc
    x86_64-elf-ld
)

for cmd in "${dependencies[@]}"; do
    if ! command -v "$cmd" >/dev/null 2>&1; then
        echo "Error: $cmd is not installed."
        exit 1
    fi
done

# limine setup
LIMINE_VERSION="v8.7.0-binary"

if [ ! -f "limine/limine" ]; then
    echo "Limine not found. Downloading Limine $LIMINE_VERSION..."

    rm -rf limine

    git clone https://github.com/limine-bootloader/limine.git \
        --branch="$LIMINE_VERSION" \
        --depth=1 \
        limine

    make -C limine
fi

# build kernel
echo "Building kernel..."

make

# create ISO root
ISO_ROOT="build/iso_root"

echo "Preparing ISO filesystem..."

rm -rf "$ISO_ROOT"

mkdir -p "$ISO_ROOT/boot/limine"

cp build/kernel/kernel.elf \
    "$ISO_ROOT/boot/"

cp limine.conf \
    "$ISO_ROOT/boot/limine/"


cp limine/limine-bios.sys \
   limine/limine-bios-cd.bin \
   limine/limine-uefi-cd.bin \
   "$ISO_ROOT/boot/limine/"


mkdir -p "$ISO_ROOT/EFI/BOOT"

cp limine/BOOTX64.EFI \
   "$ISO_ROOT/EFI/BOOT/"


# build ISO
echo "Creating ISO..."

xorriso -as mkisofs \
    -b boot/limine/limine-bios-cd.bin \
    -no-emul-boot \
    -boot-load-size 4 \
    -boot-info-table \
    --efi-boot boot/limine/limine-uefi-cd.bin \
    -efi-boot-part \
    --efi-boot-image \
    --protective-msdos-label \
    "$ISO_ROOT" \
    -o astatine.iso


# install BIOS bootloader
echo "Installing Limine BIOS boot code..."

./limine/limine bios-install astatine.iso

# run QEMU
if [ "$1" = "--run" ]; then
    echo "Starting QEMU..."

    qemu-system-x86_64 \
        -cdrom astatine.iso \
        -vga std \
        -serial stdio
fi

echo "Build complete: astatine.iso"