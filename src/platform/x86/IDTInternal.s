
.section .text
.global _IDTInternalFaultHandler
_IDTInternalFaultHandler:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    call _IDTFaultHandler
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret

.global _ISRInternal
_ISRInternal:
    pushal
    call isr
    popal
    iret

.global _IRQInternal
_IRQInternal:
    pushal
    call irq
    popal
    iret
