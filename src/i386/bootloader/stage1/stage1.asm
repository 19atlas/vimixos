[ORG 0x7C00]
[BITS 16]

;l'indirizzo di memoria del gestore d'avvio.
BOOTLOADER_ADDRESS EQU 0x1000

;salta corto all'etichetta _bootloader.
jmp short _bootloader
nop

;il blocco dei parametri del SIEB.
BPB_OEM:					db 'SOLE    '
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

;traccia d'avvio estesa.
EBR_DRIVE_NUMBER:			db 0x00
EBR_RESERVED:				db 0x00
EBR_SIGNATURE:				db 0x29
EBR_VOLUME_ID:				db 0x11, 0x11, 0x11, 0x11
EBR_VOLUME_LABEL:			db 'DISK       '
EBR_SYSTEM_ID:				db 'FAT12   '

;etichetta _bootloader.
_bootloader:

	;muovi in EBR_DRIVE_NUMBER il numero del disco d'avvio.
	mov [EBR_DRIVE_NUMBER], dl

	;svuota lo schermo reimpostando la modalita` grafica.
	mov ah, 0x00					;funzione per il cambio della modalita` grafica.
	mov al, 0x03					;modalita` grafica 0x03 testo 80x25 caratteri.
	;chiama l'interruttore 0x10 per reimpostare la modalita` grafica.
	int 0x10

	;carica il prossimo settore all'indirizzo di memoria 0x7E00.
	;imposta i parametri per la funzione di lettura dal disco.
	mov al, 0x01					;numero di settori da leggere.
	mov bx, 0x7E00					;indirizzo di memoria dove caricare i dati.
	mov cl, 0x02					;numero del settore da cui partire.
	;chiama la funzione della lettura dal disco.
	call disk_read

	;salta all'etichetta _bootloader16.
	jmp _bootloader16

;includi le sorgenti.
%INCLUDE"src/i386/bootloader/stage1/include/disk.asm"
%INCLUDE"src/i386/bootloader/stage1/include/gdt.asm"
%INCLUDE"src/i386/bootloader/stage1/include/protected_mode.asm"

;riempi il resto del settore esclusi gli ultimi due octeti con degli 0.
TIMES 510-($-$$) DB 0x00
;gli ultimi due octeti devono essere 0x55 e 0xAA affinche` il disco sia avviabile.
DW 0xAA55

;etichetta _bootloader16
_bootloader16:

	;imposta i registri dei segmenti.
	;disabilita gli interruttori.
	cli
	mov ax, 0x0000
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00
	;riabilita gli interruttori.
	sti

	;carica il gestore d'avvio all'indirizzo di memoria sopra specificato.
	;imposta i parametri per la funzione di lettura dal disco.
	mov al, 0x20					;numero di settori da leggere.
	mov bx, BOOTLOADER_ADDRESS		;indirizzo di memoria dove caricare i dati.
	mov cl, 0x03					;numero del settore da cui partire.
	;chiama la funzione della lettura dal disco.
	call disk_read

	;entra nella modalita` protetta.
	;chiama la funzione enter_protected.
	call enter_protected
	;salta all'etichetta _bootloader32.
	jmp CODE_SEG:_bootloader32

[BITS 32]

_bootloader32:

	;imposta i registri dei segmenti.
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	;abilita la linea A20 per utilizzare tutta la memoria disponibile.
	in al, 0x92
	or al, 0x02
	out 0x92, al

	;imposta la pila del gestore d'avvio e del sistema operativo.
	mov ebp, 0x10000
	mov esp, ebp

	;salta all'indirizzo di memoria del gestore d'avvio.
	jmp BOOTLOADER_ADDRESS

;riempi il resto del settore con degli 0.
TIMES 1024-($-$$) DB 0x00