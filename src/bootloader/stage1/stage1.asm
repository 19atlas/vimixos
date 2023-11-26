[ORG 0x7C00]
[BITS 16]

;the memory address of the boot manager.
BOOTLOADER_ADDRESS EQU 0x1000

;jump short to the _bootloader label.
jmp short _bootloader
nop

;SIEB parameter block.
BPB_OEM:					db 'VIMIZ OS'
BPB_BYTES_PER_SECTOR:		dw 0x0200
BPB_SECTORS_PER_CLUSTER:	db 0x01
BPB_RESERVED_SECTORS:		dw 0x000A
BPB_FAT_NUMBER:				db 0x02
BPB_DIR_ENTRIES_NUMBER:		dw 0x00E0
BPB_TOTAL_SECTORS:			dw 0x0B40
BPB_MEDIA_DESCRIPTOR_TYPE:	db 0xF0
BPB_SECTORS_PER_FAT:		dw 0x0009
BPB_SECTORS_PER_TRACK:		dw 0x0012
BPB_HEAD_NUMBER:			dw 0x0002
BPB_HIDDEN_SECTORS:			dd 0x00000000
BPB_LARGE_SECTOR_NUMBER:	dd 0x00000000

;extended boot track.
EBR_DRIVE_NUMBER:			db 0x00
EBR_RESERVED:				db 0x00
EBR_SIGNATURE:				db 0x29
EBR_VOLUME_ID:				db 0x11, 0x11, 0x11, 0x11
EBR_VOLUME_LABEL:			db 'DISK       '
EBR_SYSTEM_ID:				db 'FAT12   '

_bootloader:

	;move the boot disk number to EBR_DRIVE_NUMBER
	mov [EBR_DRIVE_NUMBER], dl

	;clear the screen by resetting the graphics mode.
	mov ah, 0x00					;function for switching the graphics mode.
	mov al, 0x03					;graphics mode 0x03 text 80x25 characters.
	int 0x10 						;call the 0x10 switch to reset the graphics mode.

	;loads the next sector at memory address 0x7E00.
	;sets the parameters for the read from disk function.
	mov al, 0x01					;number of sectors to read.
	mov bx, 0x7E00					;memory address where to load the data.
	mov cl, 0x02					;sector number to start from.

	call disk_read					;calls the read from disk function.

	jmp _bootloader16				;jump to the _bootloader16 label.

;include files
%INCLUDE"src/bootloader/stage1/include/disk.asm"
%INCLUDE"src/bootloader/stage1/include/gdt.asm"
%INCLUDE"src/bootloader/stage1/include/protected_mode.asm"
%INCLUDE"src/bootloader/stage1/include/hata.asm" ;for error screen

;fill the rest of the sector excluding the last two octets with 0s.
TIMES 510-($-$$) DB 0x00
;the last two octets must be 0x55 and 0xAA for the disk to be bootable.
DW 0xAA55

_bootloader16:
	;imposta i registri dei segmenti.
	cli			;disable the switches.
	mov ax, 0x0000
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00
	
	sti			;re-enable the switches.

	;loads the boot manager at the memory address specified above.
	;sets the parameters for the read from disk function.
	mov al, 0x20					;number of sectors to read.
	mov bx, BOOTLOADER_ADDRESS		;memory address where to load the data.
	mov cl, 0x03					;sector number to start from.
	
	call disk_read					;calls the read from disk function.

	call enter_protected			;enter protected mode.
	
	jmp CODE_SEG:_bootloader32		;jump to the _bootloader32 label.

[BITS 32]
_bootloader32:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	;enable line A20 to use all available memory.
	in al, 0x92
	or al, 0x02
	out 0x92, al

	;sets up the boot manager and operating system stack.
	mov ebp, 0x10000
	mov esp, ebp

	;jump to the boot manager memory address.
	jmp BOOTLOADER_ADDRESS

;fill the rest of the sector with 0.
TIMES 1024-($-$$) DB 0x00