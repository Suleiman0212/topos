#include "gdt.h"
#include "../util/mem.h"
#include <stdint.h>

GdtEntry gdt_entries[GDT_ENTRIES_NUM];
GdtPtr gdt_ptr;
TssEntry tss_entry;

extern void gdt_flush(GdtPtr *);
extern void tss_flush();

void gdt_initialize() {
  gdt_ptr.limit = (sizeof(GdtEntry) * GDT_ENTRIES_NUM) - 1;
  gdt_ptr.base = (uint32_t)(uintptr_t)gdt_entries;

  gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User code segment
  tss_write(5, 0x10, 0x0);

  gdt_flush(&gdt_ptr);
  tss_flush();
}

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran) {
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_hight = (base >> 24) & 0xFF;

  gdt_entries[num].limit = (limit & 0xFFFF);
  gdt_entries[num].flags = (limit >> 16) & 0x0F;
  gdt_entries[num].flags |= (gran & 0xF0);

  gdt_entries[num].access = access;
}

void tss_write(int32_t num, uint16_t ss0, uint32_t esp0) {
  uint32_t base = (uint32_t)(uintptr_t)&tss_entry;
  uint32_t limit = base + sizeof(TssEntry);

  gdt_set_gate(num, base, limit, 0xE9, 0x00);
  memset(&tss_entry, 0, sizeof(TssEntry));

  tss_entry.ss0 = ss0;
  tss_entry.esp0 = esp0;

  tss_entry.cs = 0x08 | 0x3;
  tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs =
      0x10 | 0x3;
}
