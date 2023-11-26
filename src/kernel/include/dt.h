#pragma once

#include"memory.h"
#include"ports.h"
#include<stddef.h>
#include<stdint.h>

//global description table entry structure.
struct gdt_entry_t {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t  base_middle;
	uint8_t	 access;
	uint8_t	 granularity;
	uint8_t  base_high;
}__attribute__((packed));

//pointer structure of the global description table.
struct gdt_ptr_t {
  uint16_t limit;
  uint32_t base;
}__attribute__((packed));

//switches description table entry structure.
struct idt_entry_t {
	uint16_t base_low;
	uint16_t kernel_cs;
	uint8_t  zero;
	uint8_t  flags;
	uint16_t base_high;
}__attribute__((packed));

//pointer structure of the switch description table.
struct idt_ptr_t {
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

//declaration of the global variables of the description tables.
gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

//global description table unload function.
extern "C" void gdt_flush(uint32_t);

//function of setting the gates of the global description table.
static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;
	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;
	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access      = access;
}

//global description table initialization function.
static void initialize_gdt(){
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (uint32_t)&gdt_entries;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	gdt_flush((uint32_t)&gdt_ptr);
}

//switch service managers.
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

//download function of the switch description table.
extern "C" void idt_flush(uint32_t);

//switch description table gate setting function.
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags){
	idt_entries[num].base_low  = base & 0xFFFF;
	idt_entries[num].base_high = (base >> 16) & 0xFFFF;
	idt_entries[num].kernel_cs = sel;
	idt_entries[num].zero	    = 0;
	idt_entries[num].flags     = flags;
}

//switch description table gate setting function.
static void initialize_idt(){
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_ptr.base  = (uint32_t)&idt_entries;
	memset(&idt_entries, 0, sizeof(idt_entry_t)*256);
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
	idt_set_gate(0, (uint32_t)isr0 , 0x08, 0x8E);
	idt_set_gate(1, (uint32_t)isr1 , 0x08, 0x8E);
	idt_set_gate(2, (uint32_t)isr2 , 0x08, 0x8E);
	idt_set_gate(3, (uint32_t)isr3 , 0x08, 0x8E);
	idt_set_gate(4, (uint32_t)isr4 , 0x08, 0x8E);
	idt_set_gate(5, (uint32_t)isr5 , 0x08, 0x8E);
	idt_set_gate(6, (uint32_t)isr6 , 0x08, 0x8E);
	idt_set_gate(7, (uint32_t)isr7 , 0x08, 0x8E);
	idt_set_gate(8, (uint32_t)isr8 , 0x08, 0x8E);
	idt_set_gate(9, (uint32_t)isr9 , 0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
	idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8e);
	idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8e);
	idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8e);
	idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8e);
	idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8e);
	idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8e);
	idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8e);
	idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8e);
	idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8e);
	idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8e);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8e);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8e);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8e);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8e);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8e);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8e);
	idt_flush((uint32_t)&idt_ptr);
}

//description table initialization function.
void initialize_dt(){
	initialize_gdt();
	initialize_idt();
}