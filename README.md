# 💻 TopOS

Monolith `X86` operating system with `GRUB` bootloader.
Made for **fun** and **educational** purposes.

## 📦 Features

- GRUB bootloader
- Terminal output
- Serial port support
- Keyboard support
- Simple shell

## 🔧 Prerequisites

- [`just`](https://github.com/casey/just) — a command runner (alternative to `make`)
- `i686-elf-gcc`, `i686-elf-as`, `i686-elf-ld` — cross-compilation toolchain
  for i686 (you'll need to build it manually)
- `grub-mkrescue`, `xorriso` — to create a bootable ISO with GRUB
- `qemu-system-i386` - to run OS

## 🛠 Building & Run

### Build ISO

You can write ISO on your hard-drive and launch **TopOS** on real hardware!

```bash
git clone https://github.com/Suleiman0212/TopOS
cd topos/

just build
just iso
```

Or you can launch it under QEMU!

```bash
# Manually
just build
just iso
just run # qemu-system-i386 topos.iso

# Or one command

just one # clean, build, iso, run
```

## 🧪 Roadmap

### Milestone 1: Base Boot & Output

- [x] GRUB Bootloader
- [x] Terminal (VGA)
- [x] Serial Driver
- [x] Timer
- [x] GDT / IDT / IRQ

### Milestone 2: Input & Memory

- [x] Keyboard
- [ ] Memory Management

### Milestone 3: Shell & Execution

- [ ] Modal Shell
- [ ] Scripting Language
- [ ] Binary Loader
- [ ] System Calls

### Milestone 4: Storage & FS

- [ ] PATA / AHCI / NVMe Drivers
- [ ] File System

### Milestone 5: Language & Apps

- [ ] Assembler
- [ ] C Compiler
- [ ] POSIX Utilities
- [ ] Text Editor

## Goal

> `TopOS` is a project that I want turn to **simple dev system**,
> where you can launch OS, write your own program in the embedded editor,
> compile and launch it.
>
> `TopOS` author - _Suleiam Kirimov_.
