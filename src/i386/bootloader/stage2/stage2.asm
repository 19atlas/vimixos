[BITS 32]
;importa da bootloader.cpp la funzione bootloader.
[EXTERN bootloader]
;chiama la funzione bootloader.
call bootloader
;crea un ciclo infinito saltando all'indirizzo di memoria corrente.
jmp $