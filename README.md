# TopOS

Small monolith operating system with GRUB bootloader.

## Prerequsites

- [`just`](https://github.com/casey/just) — a command runner (alternative to `make`)
- `i686-elf-gcc`, `i686-elf-as`, `i686-elf-ld` — cross-compilation toolchain for i686 (you'll need to build it manually)
- `grub-mkrescue` — to create a bootable ISO with GRUB
- `qemu-system-i386` - to run OS

### For Arch Linux

Install the base dependencies:

```bash
sudo pacman -S just grub dosfstools xorriso qemu
```

## Building ISO

```bash
git clone https://github.com/Suleiman0212/TopOS
cd topos/
just build
just iso
```

## Running

```bash
just build
just iso
just run

# OR

just test # clean, build, iso, run
```
