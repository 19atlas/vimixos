;funzione della lettura dal disco.
disk_read:

	;leggi i dati dal disco con i parametri dati all'indirizzo di memoria specificato.
	mov ah, 0x02					;funzione per la lettura dal disco.
	mov ch, 0x00					;numero del cilindro del disco.
	mov dh, 0x00					;numero della testina del disco.
	push 0x0000						;es contiene il segmento di memoria.
	pop es
	;chiama l'interruttore 0x13 per leggere dal disco con i parametri dati.
	int 0x13
	;ad una lettura con successo il registro ah e` uguale a zero.
	cmp ah, 0x00
	;se non lo e` salta all'etichetta disk_read_error.
	jne disk_read_error
	;ritorna a dove e` stata chiamata la funzione disk_read.
	ret

;funzione per scrivere '!' se si e` verificato un errore durante la lettura dal disco.
disk_read_error:

	mov ah, 0x0E					;funzione per la scrittura di caratteri sullo schermo.
	mov al, 0x21					;il carattere '!' in esadecimale e` 0x21.
	int 0x10
	;ritorna a dove e` stata chiamata la funzione disk_read.
	ret