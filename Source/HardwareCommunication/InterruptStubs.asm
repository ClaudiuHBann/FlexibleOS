.set IRQ_BASE, 0x20

.section .text

.extern _ZN16InterruptManager15HandleInterruptEhj
.extern g_kernelDataSegmentSelector

.macro HandleException num
.global _ZN16InterruptManager16HandleException\num\()Ev
_ZN16InterruptManager16HandleException\num\()Ev:
    movb $\num, (interruptNumber)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptNumber)
    jmp int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x0C

int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    # Set kernel data segments for interrupt handler
    movw g_kernelDataSegmentSelector, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp
    push (interruptNumber)
    call _ZN16InterruptManager15HandleInterruptEhj
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

.global _ZN16InterruptManager15InterruptIgnoreEv
_ZN16InterruptManager15InterruptIgnoreEv:
    iret

.data
    interruptNumber: .byte 0