#pragma once

#include<stddef.h>
#include<stdint.h>

#define IRQ_BASE_VECTOR 32
#define IRQ_VECTOR_COUNT 16

enum irq_vector_t : uint8_t {
	IRQ0  = IRQ_BASE_VECTOR + 0,
	IRQ1  = IRQ_BASE_VECTOR + 1,
	IRQ2  = IRQ_BASE_VECTOR + 2,
	IRQ3  = IRQ_BASE_VECTOR + 3,
	IRQ4  = IRQ_BASE_VECTOR + 4,
	IRQ5  = IRQ_BASE_VECTOR + 5,
	IRQ6  = IRQ_BASE_VECTOR + 6,
	IRQ7  = IRQ_BASE_VECTOR + 7,
	IRQ8  = IRQ_BASE_VECTOR + 8,
	IRQ9  = IRQ_BASE_VECTOR + 9,
	IRQ10 = IRQ_BASE_VECTOR + 10,
	IRQ11 = IRQ_BASE_VECTOR + 11,
	IRQ12 = IRQ_BASE_VECTOR + 12,
	IRQ13 = IRQ_BASE_VECTOR + 13,
	IRQ14 = IRQ_BASE_VECTOR + 14,
	IRQ15 = IRQ_BASE_VECTOR + 15
};

struct idt_entry32_t {
	uint16_t base_low;
	uint16_t selector;
	uint8_t  zero;
	uint8_t  flags;
	uint16_t base_high;
} __attribute__((packed));

struct idt_ptr32_t {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct idt_entry64_t {
	uint16_t base_low;
	uint16_t selector;
	uint8_t  ist;
	uint8_t  flags;
	uint16_t base_middle;
	uint32_t base_high;
	uint32_t zero;
} __attribute__((packed));

struct idt_ptr64_t {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed));
