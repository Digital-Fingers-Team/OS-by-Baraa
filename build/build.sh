#!/bin/bash
# Reproducible build script for BlackboxOS minimal kernel + init + compositor

set -e

# Assumptions: Running on Ubuntu/Debian host with build tools installed
# Install deps: sudo apt install build-essential git bc flex bison libssl-dev

KERNEL_VERSION=5.15.0
COMPOSITOR_REPO=https://github.com/swaywm/wlroots.git  # Fork and optimize later

echo "Building minimal Linux kernel..."
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-$KERNEL_VERSION.tar.xz
tar xf linux-$KERNEL_VERSION.tar.xz
cd linux-$KERNEL_VERSION
make defconfig
# Apply custom config for speed/security
echo "CONFIG_PREEMPT=y" >> .config
echo "CONFIG_ZRAM=y" >> .config
echo "CONFIG_SECURITY_APPARMOR=y" >> .config
make -j$(nproc)
cp arch/x86/boot/bzImage ../kernel.bzImage
cd ..

echo "Building minimal init (systemd stub)..."
# For demo, use busybox as init
wget https://busybox.net/downloads/busybox-1.35.0.tar.bz2
tar xf busybox-1.35.0.tar.bz2
cd busybox-1.35.0
make defconfig
make -j$(nproc)
cp busybox ../init
cd ..

echo "Building compositor (wlroots-based)..."
git clone $COMPOSITOR_REPO wlroots
cd wlroots
meson build
ninja -C build
cp build/libwlroots.so ../libwlroots.so
cd ..

echo "Creating initramfs..."
mkdir initramfs
cp init initramfs/
cp libwlroots.so initramfs/
# Add minimal /bin/sh, /etc/passwd, etc.
echo "Creating rootfs.cpio..."
cd initramfs
find . | cpio -o -H newc > ../rootfs.cpio
cd ..

echo "Kernel built: kernel.bzImage"
echo "Initramfs: rootfs.cpio"
echo "To boot in QEMU: qemu-system-x86_64 -kernel kernel.bzImage -initrd rootfs.cpio -append 'console=ttyS0'"
