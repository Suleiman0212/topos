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
  {{CC}} {{CFLAGS}} -c src/kernel/heap.c -o out/heap.o

  {{CC}} {{CFLAGS}} -c src/drivers/terminal.c -o out/terminal.o
  {{CC}} {{CFLAGS}} -c src/drivers/serial.c -o out/serial.o
  {{CC}} {{CFLAGS}} -c src/drivers/keyboard.c -o out/keyboard.o

  {{CC}} {{CFLAGS}} -c src/cpu/gdt.c -o out/gdt.o
  {{ASM}} {{ASFLAGS}} src/cpu/gdt.s -o out/gdts.o
  {{CC}} {{CFLAGS}} -c src/cpu/idt.c -o out/idt.o
  {{ASM}} {{ASFLAGS}} src/cpu/idt.s -o out/idts.o
  {{CC}} {{CFLAGS}} -c src/cpu/pit.c -o out/pit.o

  {{CC}} {{CFLAGS}} -c src/std/mem.c -o out/mem.o
  {{CC}} {{CFLAGS}} -c src/std/str.c -o out/str.o

  {{CC}} {{CFLAGS}} -c src/applications/shell.c -o out/shell.o

  {{LD}} {{LDFLAGS}} -o bin/topos.bin out/boot.o out/kernel.o out/heap.o out/gdt.o out/gdts.o out/idt.o out/idts.o out/pit.o out/terminal.o out/serial.o out/keyboard.o out/mem.o out/str.o out/shell.o

grub:
  mkdir -p isodir/boot/grub
  cp bin/topos.bin isodir/boot/topos.bin
  cp grub.cfg isodir/boot/grub/grub.cfg
  grub-mkrescue -o topos.iso isodir

run:
  qemu-system-i386 -cdrom topos.iso -serial stdio -display sdl

clean:
  rm -rf out/ bin/

one: build grub run
