;function of reading from disk.
disk_read:
	;read data from the disk with the given parameters at the specified memory address.
	mov ah, 0x02					;function for reading from disk.
	mov ch, 0x00					;disk cylinder number.
	mov dh, 0x00					;disk head number.
	push 0x0000						;es contains the memory segment.
	pop es
	;calls switch 0x13 to read from disk with given parameters.
	int 0x13
	;on a successful read the ah register equals zero.
	cmp ah, 0x00
	;if not, jump to the disk_read_error label.
	jne disk_read_error
	;returns to where the disk_read function was called.
	ret

;if unsuccessful print error
disk_read_error:
	call hataYaz
	hlt