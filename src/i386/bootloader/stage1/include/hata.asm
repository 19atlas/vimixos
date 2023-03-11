hataYaz:
    mov ebx, 0xb8000    ;Video Memory
    mov si, HataMsg ; load the address of the message into si
    jmp .print
.print:
    mov ah, 0x0e ; set the video function to write a character with attribute
    mov bh, 0x00 ; page number
    mov bl, 0x07 ; attribute (white text on black background)
.next_char:
    lodsb ; load the next character from si al = next chracter
    cmp al, 0 ; check if we have reached the end of the string
    je .finish ; if so, jump to finish
    int 0x10 ; otherwise, write the character to the screen
    jmp .next_char
.finish:
    hlt
    jmp $
HataMsg: db "VIMIZ DISK HATASI",0x0D, 0x0a,"disk okunamiyor...", 0