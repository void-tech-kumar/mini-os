; MiniOS Bootloader
; 16-bit BIOS boot sector

bits 16
org 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov si, message

print:
    lodsb
    cmp al, 0
    je hang

    mov ah, 0x0E
    mov bh, 0x00
    int 0x10

    jmp print

hang:
    cli
    hlt
    jmp hang

message db 13, 10, "MiniOS Bootloader Started!", 13, 10, 0

times 510 - ($ - $$) db 0
dw 0xAA55
