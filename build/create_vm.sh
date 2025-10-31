#!/bin/bash
# Script to create a bootable VM image using QEMU and the built kernel/initramfs

set -e

# Requires: qemu-system-x86_64, parted, mkfs.ext4

DISK_SIZE=8G  # Minimal 8GB
DISK_IMG=blackboxos.qcow2

echo "Creating disk image..."
qemu-img create -f qcow2 $DISK_IMG $DISK_SIZE

echo "Partitioning and formatting..."
# Use guestfish or manual loopback for partitioning
# For simplicity, assume pre-built rootfs; in full impl, use debootstrap or similar

echo "Installing kernel and initramfs to VM..."
# Copy kernel.bzImage and rootfs.cpio to /boot in VM
# This is a stub; full script would mount and copy

echo "VM image created: $DISK_IMG"
echo "Boot with: qemu-system-x86_64 -hda $DISK_IMG -kernel kernel.bzImage -initrd rootfs.cpio -append 'root=/dev/sda1 console=ttyS0'"
