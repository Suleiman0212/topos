#include "idt.h"

IdtEntry idt_entries[IDT_ENTRIES_NUM];
IdtPtr idt_ptr;

extern void idt_flush(uint32_t);

void idt_initialize() {
  idt_ptr.limit = sizeof(IdtEntry) * IDT_ENTRIES_NUM - 1;
  idt_ptr.base = (uint32_t)(uintptr_t)&idt_entries;

  memset(&idt_entries, 0, sizeof(IdtEntry) * IDT_ENTRIES_NUM);

  // Master 0x20 commands and 0x21 data
  // Slave 0xA0 commands and 0xA1 data
  outb(0x20, 0x11);
  outb(0xA0, 0x11);

  outb(0x21, 0x20);
  outb(0xA1, 0x28);

  outb(0x21, 0x04);
  outb(0xA1, 0x02);

  outb(0x21, 0x01);
  outb(0xA1, 0x01);

  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  idt_set_gate(0, (uint32_t)(uintptr_t)isr0, 0x08, 0x8E);
  idt_set_gate(1, (uint32_t)(uintptr_t)isr1, 0x08, 0x8E);
  idt_set_gate(2, (uint32_t)(uintptr_t)isr2, 0x08, 0x8E);
  idt_set_gate(3, (uint32_t)(uintptr_t)isr3, 0x08, 0x8E);
  idt_set_gate(4, (uint32_t)(uintptr_t)isr4, 0x08, 0x8E);
  idt_set_gate(5, (uint32_t)(uintptr_t)isr5, 0x08, 0x8E);
  idt_set_gate(6, (uint32_t)(uintptr_t)isr6, 0x08, 0x8E);
  idt_set_gate(7, (uint32_t)(uintptr_t)isr7, 0x08, 0x8E);
  idt_set_gate(8, (uint32_t)(uintptr_t)isr8, 0x08, 0x8E);
  idt_set_gate(9, (uint32_t)(uintptr_t)isr9, 0x08, 0x8E);
  idt_set_gate(10, (uint32_t)(uintptr_t)isr10, 0x08, 0x8E);
  idt_set_gate(11, (uint32_t)(uintptr_t)isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint32_t)(uintptr_t)isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint32_t)(uintptr_t)isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint32_t)(uintptr_t)isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint32_t)(uintptr_t)isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint32_t)(uintptr_t)isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint32_t)(uintptr_t)isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint32_t)(uintptr_t)isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint32_t)(uintptr_t)isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint32_t)(uintptr_t)isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint32_t)(uintptr_t)isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint32_t)(uintptr_t)isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint32_t)(uintptr_t)isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint32_t)(uintptr_t)isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint32_t)(uintptr_t)isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint32_t)(uintptr_t)isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint32_t)(uintptr_t)isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint32_t)(uintptr_t)isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint32_t)(uintptr_t)isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint32_t)(uintptr_t)isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint32_t)(uintptr_t)isr31, 0x08, 0x8E);

  idt_set_gate(32, (uint32_t)(uintptr_t)irq0, 0x08, 0x8E);
  idt_set_gate(33, (uint32_t)(uintptr_t)irq1, 0x08, 0x8E);
  idt_set_gate(34, (uint32_t)(uintptr_t)irq2, 0x08, 0x8E);
  idt_set_gate(35, (uint32_t)(uintptr_t)irq3, 0x08, 0x8E);
  idt_set_gate(36, (uint32_t)(uintptr_t)irq4, 0x08, 0x8E);
  idt_set_gate(37, (uint32_t)(uintptr_t)irq5, 0x08, 0x8E);
  idt_set_gate(38, (uint32_t)(uintptr_t)irq6, 0x08, 0x8E);
  idt_set_gate(39, (uint32_t)(uintptr_t)irq7, 0x08, 0x8E);
  idt_set_gate(40, (uint32_t)(uintptr_t)irq8, 0x08, 0x8E);
  idt_set_gate(41, (uint32_t)(uintptr_t)irq9, 0x08, 0x8E);
  idt_set_gate(42, (uint32_t)(uintptr_t)irq10, 0x08, 0x8E);
  idt_set_gate(43, (uint32_t)(uintptr_t)irq11, 0x08, 0x8E);
  idt_set_gate(44, (uint32_t)(uintptr_t)irq12, 0x08, 0x8E);
  idt_set_gate(45, (uint32_t)(uintptr_t)irq13, 0x08, 0x8E);
  idt_set_gate(46, (uint32_t)(uintptr_t)irq14, 0x08, 0x8E);
  idt_set_gate(47, (uint32_t)(uintptr_t)irq15, 0x08, 0x8E);

  idt_set_gate(128, (uint32_t)(uintptr_t)isr128, 0x08, 0x8E); // System calls
  idt_set_gate(177, (uint32_t)(uintptr_t)isr177, 0x08, 0x8E); // System calls

  idt_flush((uint32_t)(uintptr_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector,
                  uint8_t flags) {
  idt_entries[num].base_low = base & 0xFFFF;
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;
  idt_entries[num].selector = selector;
  idt_entries[num].always0 = 0;
  idt_entries[num].flags = flags | 0x60;
}

const char *exeption_messages[] = {"Division By Zero",
                                   "Debug",
                                   "Non Maskable Interrupt",
                                   "Breakpoint",
                                   "Into Detected Overflow",
                                   "Out of Bounds",
                                   "Invalid Opcode",
                                   "No Coprocessor",
                                   "Double fault",
                                   "Coprocessor Segment Overrun",
                                   "Bad TSS",
                                   "Segment not present",
                                   "Stack fault",
                                   "General protection fault",
                                   "Page fault",
                                   "Unknown Interrupt",
                                   "Coprocessor Fault",
                                   "Alignment Fault",
                                   "Machine Check",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved",
                                   "Reserved"};

void isr_handler(InterruptRegisters *regs) {
  if (regs->int_no < 32) {
    terminal_write_string("\n@[R]EXEPTION@[!]!:\t");
    terminal_write_string(exeption_messages[regs->int_no]);
    terminal_write_string("\nSystem halted.");
    for (;;)
      ;
  }
  if (regs->int_no == 128) {
    // Syscall catch
  }
}

void *irq_routines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void irq_install_handler(int irq, void (*handler)(InterruptRegisters *r)) {
  irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) { irq_routines[irq] = 0; }

void irq_handler(InterruptRegisters *regs) {
  void (*handler)(InterruptRegisters *regs);

  handler = irq_routines[regs->int_no - 32];

  if (handler) {
    handler(regs);
  }

  if (regs->int_no >= 40) {
    outb(0xA0, 0x20);
  }

  outb(0x20, 0x20);
}
