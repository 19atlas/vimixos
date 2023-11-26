[BITS 32]
;import the bootloader function from bootloader.cpp.
[EXTERN bootloader]
;call the bootloader function.
call bootloader
;creates an infinite loop by jumping to the current memory address.
jmp $