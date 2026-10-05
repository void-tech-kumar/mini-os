bits 16
org 0x7C00

KERNEL_OFFSET equ 0x1000

start:
    cli

    mov [boot_drive], dl

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Load kernel from disk
    mov ah, 0x02
    mov al, 0x01
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    mov dl, [boot_drive]
    mov bx, KERNEL_OFFSET
    int 0x13

    jc disk_error

    ; Enter protected mode
    cli

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x01
    mov cr0, eax

    jmp CODE_SEG:init_pm

disk_error:
    mov si, error_message

print_error:
    lodsb
    cmp al, 0
    je halt

    mov ah, 0x0E
    int 0x10

    jmp print_error

halt:
    cli
    hlt
    jmp halt


bits 32

init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000

    ; Jump to loaded kernel
    call KERNEL_OFFSET

    cli

pm_halt:
    hlt
    jmp pm_halt


; -------------------------
; GDT
; -------------------------

gdt_start:

gdt_null:
    dq 0x0000000000000000

gdt_code:
    dq 0x00CF9A000000FFFF

gdt_data:
    dq 0x00CF92000000FFFF

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

boot_drive db 0

error_message db "Disk read error!", 0


times 510 - ($ - $$) db 0
dw 0xAA55
