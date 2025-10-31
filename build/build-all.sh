#!/bin/bash
# Complete build script for BlackboxOS

set -e

# Prerequisites check
command -v wget >/dev/null 2>&1 || { echo "Install wget: sudo apt install wget"; exit 1; }
command -v git >/dev/null 2>&1 || { echo "Install git: sudo apt install git"; exit 1; }
# Add more checks as needed

KERNEL_VER=5.15.0
BUSYBOX_VER=1.35.0
WLROOTS_REPO=https://github.com/swaywm/wlroots.git

mkdir -p build_temp images

cd build_temp

# Kernel
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-$KERNEL_VER.tar.xz
tar xf linux-$KERNEL_VER.tar.xz
cd linux-$KERNEL_VER
make defconfig
# Custom config
sed -i 's/# CONFIG_PREEMPT is not set/CONFIG_PREEMPT=y/' .config
sed -i 's/# CONFIG_ZRAM is not set/CONFIG_ZRAM=y/' .config
make -j$(nproc)
cp arch/x86/boot/bzImage ../../images/vmlinuz
cd ..

# Busybox init
wget https://busybox.net/downloads/busybox-$BUSYBOX_VER.tar.bz2
tar xf busybox-$BUSYBOX_VER.tar.bz2
cd busybox-$BUSYBOX_VER
make defconfig
make -j$(nproc)
cp busybox ../../images/init
cd ..

# Wlroots compositor stub
git clone $WLROOTS_REPO
cd wlroots
meson build
ninja -C build
cp build/libwlroots.so ../../images/
cd ..

# Create initramfs
mkdir initramfs
cp ../images/init initramfs/
cp ../images/libwlroots.so initramfs/
cd initramfs
find . | cpio -o -H newc > ../rootfs.cpio
cd ..

# ISO creation (stub: use mkisofs or similar)
# For demo, create minimal ISO
echo "Creating ISO..."
mkisofs -o ../../images/os-v1.0.0-x86_64.iso -b images/vmlinuz -c boot.cat .

# VM image
qemu-img create -f qcow2 ../../images/os-v1.0.0-x86_64.qcow2 8G

cd ..
rm -rf build_temp

# Checksums
cd images
sha256sum * > checksums.txt
cd ..

echo "Build complete. Artifacts in images/"
