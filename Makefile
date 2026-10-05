ASM = nasm
CC = gcc
LD = ld
OBJCOPY = objcopy
QEMU = qemu-system-x86_64

BOOT_SRC = kernel/boot/boot.asm
KERNEL_SRC = kernel/core/kernel.c
PROCESS_SRC = kernel/process/process.c
LINKER = kernel/linker.ld

BOOT_BIN = boot.bin
KERNEL_OBJ = kernel.o
PROCESS_OBJ = process.o
KERNEL_ELF = kernel.elf
KERNEL_BIN = kernel.bin
OS_IMAGE = os-image.bin

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector
LDFLAGS = -m elf_i386 -T $(LINKER)

.PHONY: all build run clean

all: build

build: $(OS_IMAGE)

$(BOOT_BIN): $(BOOT_SRC)
	$(ASM) -f bin $(BOOT_SRC) -o $(BOOT_BIN)

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(KERNEL_OBJ)

$(PROCESS_OBJ): $(PROCESS_SRC)
	$(CC) $(CFLAGS) -c $(PROCESS_SRC) -o $(PROCESS_OBJ)

$(KERNEL_ELF): $(KERNEL_OBJ) $(PROCESS_OBJ) $(LINKER)
	$(LD) $(LDFLAGS) -o $(KERNEL_ELF) $(KERNEL_OBJ) $(PROCESS_OBJ)

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $(KERNEL_ELF) $(KERNEL_BIN)

$(OS_IMAGE): $(BOOT_BIN) $(KERNEL_BIN)
	dd if=/dev/zero of=$(OS_IMAGE) bs=512 count=20
	dd if=$(BOOT_BIN) of=$(OS_IMAGE) conv=notrunc
	dd if=$(KERNEL_BIN) of=$(OS_IMAGE) bs=512 seek=1 conv=notrunc

run: build
	$(QEMU) -drive format=raw,file=$(OS_IMAGE)

clean:
	rm -f $(BOOT_BIN) $(KERNEL_OBJ) $(PROCESS_OBJ) $(KERNEL_ELF) $(KERNEL_BIN) $(OS_IMAGE)
