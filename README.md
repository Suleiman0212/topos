# 💻 TopOS

Monolith `X86` operating system with `GRUB` bootloader.
Made for **fun** and **educational** purposes.

## 📦 Features

- GRUB bootloader
- Terminal output
- Serial port support

## 🔧 Prerequisites

- [`just`](https://github.com/casey/just) — a command runner (alternative to `make`)
- `i686-elf-gcc`, `i686-elf-as`, `i686-elf-ld` — cross-compilation toolchainfor
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

### Bootloader

- [x] GRUB bootloader
- [ ] Custom bootloader

### Drivers

- [x] **Terminal** (through `VGA Text Mode`) driver (text output)
- [x] **Serial** driver (COM port)
- [x] **Timer** driver
- [ ] **Keyboard** driver
- [ ] **Storage** drivers
  - [ ] **PATA** driver (ATA/IDE)
  - [ ] **AHCI** driver (SATA)
  - [ ] **NVMe** driver, if I feel brave enough.

### System

- [x] **GDT, IDT, IRQ**
- [ ] **Memory management**
- [ ] **Binary loader**
- [ ] **System calls**
- [ ] **File System**

### UI and Languages

- [ ] **Modal shell**
- [ ] **Scripting language / shell interpreter**
- [ ] **Assembler** like NASM
- [ ] **Compilable, system level language** like C

### Applications

- [ ] **POSIX like utilites**
- [ ] **Text editor**
- [ ] **File manager**
- [ ] **Base devel**
- [ ] **Log viewver**
- [ ] **Calculator**
