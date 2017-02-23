#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/tos.kernel isodir/boot/tos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
set timeout=0
set default=0 # Set the default menu entry

menuentry "tos" {
	multiboot /boot/tos.kernel
}
EOF
grub-mkrescue -o tos.iso isodir
