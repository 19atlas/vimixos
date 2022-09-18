;funzione per entrare nella modalita` protetta.
enter_protected:

	;disabilita gli interruttori.
	cli
	;carica la tavola di descrizione globale.
	lgdt[gdt_descriptor]
	;entra nella modalita` protetta.
	mov eax, cr0
	or eax, 0x00000001
	mov cr0, eax
	;ritorna a dove e` stata chiamata la funzione enter_protected.
	ret