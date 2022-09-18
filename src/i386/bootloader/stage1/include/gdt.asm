gdt_start:

gdt_null:

	DD 0x00000000
	DD 0x00000000

gdt_code:

	DW 0xFFFF
	DW 0x0000
	DB 0x00
	DB 0x9A
	DB 0xCF
	DB 0x00

gdt_data:

	DW 0xFFFF
	DW 0x0000
	DB 0x00
	DB 0x92
	DB 0xCF
	DB 0x00

gdt_end:

gdt_descriptor:

	DW gdt_end - gdt_start - 1
	DD gdt_start

CODE_SEG EQU gdt_code - gdt_start
DATA_SEG EQU gdt_data - gdt_start