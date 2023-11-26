#pragma once

#include"stdio.h"
#include"ports.h"

typedef struct regs {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers_t; 

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler); 

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define DIVIDE_BY_ZERO 0
#define DEBUG 1
#define NON_MASKABLE_INTERRUPT 2
#define BREAKPOINT 3
#define OVERFLOW 4
#define BOUND_RANGE_EXCEEDED 5
#define INVALID_OPCODE 6
#define DEVICE_NOT_AVAILABLE 7
#define DOUBLE_FAULT 8
#define COPROCESSOR_SEGMENT_OVERRUN 9
#define INVALID_TSS 10
#define SEGMENT_NOT_PRESENT 11
#define STACK_SEGMENT_FAULT 12
#define GENERAL_PROTECTION_FAULT 13
#define PAGE_FAULT 14
#define RESERVED1 15
#define X87FLOATING_POINT_EXCEPTION 16
#define ALIGMENT_CHECK 17
#define MACHINE_CHECK 18
#define SIMD_FLOATING_POINT_EXCEPTION 19
#define VIRTUALIZATION_EXCEPTION 20
#define CONTROL_PROTECTION_EXCEPTION 21
#define RESERVED2 22
#define RESERVED3 23
#define RESERVED4 24
#define RESERVED5 25
#define RESERVED6 26
#define RESERVED7 27
#define HYPERVISOR_INJECTION_EXCEPTION 28
#define VMM_COMUNICATION_EXCEPTION 29
#define SECURITY_EXCEPTION 30
#define RESERVED8 31

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler){ interrupt_handlers[n] = handler; }

extern "C" void isr_handler(registers_t regs){
	set_color(0x4);
	switch(regs.int_no) {
		case DIVIDE_BY_ZERO:
			printf("Divide by zero.");
			break;
		case DEBUG:
			printf("Debug.");
			break;
		case NON_MASKABLE_INTERRUPT:
			printf("Non maskable interrupt.");
			break;
		case BREAKPOINT:
			printf("Breakpoint.");
			break;
		case OVERFLOW:
			printf("Overflow.");
			break;
		case BOUND_RANGE_EXCEEDED:
			printf("Bound range exceeded.");
			break;
		case INVALID_OPCODE:
			printf("Invalid opcode.");
			break;
		case DEVICE_NOT_AVAILABLE:
			printf("Device not available.");
			break;
		case DOUBLE_FAULT:
			printf("Double fault.");
			asm("cli; hlt");
			break;
		case COPROCESSOR_SEGMENT_OVERRUN:
			printf("Coprocessor segment overrun.");
			break;
		case INVALID_TSS:
			printf("Invalid TSS.");
			break;
		case SEGMENT_NOT_PRESENT:
			printf("Segment not present.");
			break;
		case STACK_SEGMENT_FAULT:
			printf("Stack segment fault.");
			break;
		case GENERAL_PROTECTION_FAULT:
			printf("General protection fault.");
			break;
		case PAGE_FAULT:
			printf("Page fault.");
			break;
		case X87FLOATING_POINT_EXCEPTION:
			printf("x87 floating point exception.");
			break;
		case ALIGMENT_CHECK:
			printf("Aligment check.");
			break;
		case MACHINE_CHECK:
			printf("Machine check.");
			asm("cli; hlt");
			break;
		case SIMD_FLOATING_POINT_EXCEPTION:
			printf("SIMD floating point exception.");
			break;
		case VIRTUALIZATION_EXCEPTION:
			printf("Virtualization exception.");
			break;
		case CONTROL_PROTECTION_EXCEPTION:
			printf("Control protection exception.");
			break;
		case HYPERVISOR_INJECTION_EXCEPTION:
			printf("Hypervisor injection exception.");
			break;
		case VMM_COMUNICATION_EXCEPTION:
			printf("VMM comunication exception.");
			break;
		case SECURITY_EXCEPTION:
			printf("Security exception.");
			break;
		default:
			printf("unhandled interrupt 0x%x\n", regs.int_no);
			break;
	}
}

extern "C" void irq_handler(registers_t r){
	if(r.int_no >= 40){
		outb(0xa0, 0x20);
	}
	outb(0x20, 0x20);
	if(interrupt_handlers[r.int_no] != 0){
		isr_t handler = interrupt_handlers[r.int_no];
		handler(r);
	}
}