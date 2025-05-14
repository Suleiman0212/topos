set shell := ["bash", "-cu"]

CC := "$HOME/opt/cross/bin/i686-elf-gcc"
ASM := "$HOME/opt/cross/bin/i686-elf-as"
LD := "$HOME/opt/cross/bin/i686-elf-ld"

CFLAGS := "-std=gnu99 -ffreestanding -O2 -Wall -Wextra"
ASFLAGS := ""
LDFLAGS := "-T linker.ld -nostdlib"

build: clean
  mkdir -p out/ bin/
  {{ASM}} {{ASFLAGS}} src/boot/boot.s -o out/boot.o
  {{CC}} {{CFLAGS}} -c src/kernel/kernel.c -o out/kernel.o
  {{CC}} {{CFLAGS}} -c src/drivers/terminal.c -o out/terminal.o
  {{CC}} {{CFLAGS}} -c src/drivers/serial.c -o out/serial.o

  {{LD}} {{LDFLAGS}} -o bin/topos.bin out/boot.o out/kernel.o out/terminal.o out/serial.o

grub:
  mkdir -p isodir/boot/grub
  cp bin/topos.bin isodir/boot/topos.bin
  cp grub.cfg isodir/boot/grub/grub.cfg
  grub-mkrescue -o topos.iso isodir

run:
  qemu-system-i386 -cdrom topos.iso -serial stdio

clean:
  rm -rf out/ bin/

test: build grub run
