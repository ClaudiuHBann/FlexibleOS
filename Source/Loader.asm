.set MAGIC, 0x1BADB002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern KernelMain
.extern ConstructorsCall
.global loader

loader:
    mov $kernelStack, %esp
    call ConstructorsCall
    push %eax
    push %ebx
    call KernelMain

_stop:
    cli
    hlt

.section .bss
.space 2 * 1024 * 1024
kernelStack: