;function to enter protected mode.
enter_protected:
	cli ;disable the switches.
	lgdt[gdt_descriptor] ;loads the global description table.
	;enter protected mode.
	mov eax, cr0
	or eax, 0x00000001
	mov cr0, eax
	ret ;returns to where the function was called.