[BITS 32]
;importa da kernel.cpp la funzione main.
[EXTERN main]
;chiama la funzione main.
call main
;crea un ciclo infinito saltando all'indirizzo di memoria corrente.
jmp $

[GLOBAL memcpy_sse]
memcpy_sse:
	push ebp
	mov ebp, esp
	push esi
	push edi
	pushf
	cld
	mov edi, [ebp + 8]
	mov esi, [ebp + 12]
	mov eax, [ebp + 16]
	mov ecx, eax
	shr ecx, 6
	jz .endloop64
.loop64: 
	prefetchnta [esi + 64]
	prefetchnta [esi + 96] 
	movq mm1, [esi +  0]
	movq mm2, [esi +  8] 
	movq mm3, [esi + 16] 
	movq mm4, [esi + 24] 
	movq mm5, [esi + 32] 
	movq mm6, [esi + 40] 
	movq mm7, [esi + 48] 
	movq mm0, [esi + 56] 
	movntq [edi +  0], mm1
	movntq [edi +  8], mm2 
	movntq [edi + 16], mm3 
	movntq [edi + 24], mm4 
	movntq [edi + 32], mm5 
	movntq [edi + 40], mm6 
	movntq [edi + 48], mm7 
	movntq [edi + 56], mm0 
	add esi, 64 
	add edi, 64 
	loop .loop64
	emms 
.endloop64:
	mov ecx, eax
	and ecx, 0x3F
	shr ecx, 3
	jz .endloop8
.loop8:
	movq mm1, [esi]
	movq [edi], mm1
	add esi, 8 
	add edi, 8 
	loop .loop8
	emms 
.endloop8:
	mov ecx, eax
	and ecx, 7
	repe movsb
.done:
	popf
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
	ret

[GLOBAL enable_sse]
enable_sse:
	mov eax, cr0
	and ax, 0xFFFB
	or ax, 0x2
	mov cr0, eax
	mov eax, cr4
	or ax, 3 << 9
	mov cr4, eax
	ret

[GLOBAL gdt_flush]
gdt_flush:
	mov eax, [esp+4]
	lgdt [eax]
	mov eax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush
.flush:
	ret

[GLOBAL idt_flush]
idt_flush:
	mov eax, [esp+4]
	lidt [eax]
	sti
	ret

%MACRO ISR_NOERRCODE 1
	[GLOBAL isr%1]
	isr%1:
	cli
	push byte 0
	push byte %1
	jmp isr_common_stub
%ENDMACRO

%MACRO ISR_ERRCODE 1
	[GLOBAL isr%1]
	isr%1:
	cli
	push byte %1
	jmp isr_common_stub
%ENDMACRO

%MACRO IRQ 2
	[GLOBAL irq%1]
	irq%1:
	cli
	push byte 0
	push byte %2
	jmp irq_common_stub
%ENDMACRO

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

[EXTERN isr_handler]

isr_common_stub:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	call isr_handler
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8
	sti
	iret

[EXTERN irq_handler]
irq_common_stub:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	call irq_handler
	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	popa
	add esp, 8
	sti
	iret