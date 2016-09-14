#include <PlatformX86.h>

#include <GDT.h>

#define asm __asm__
#define volatile __volatile__

void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
               : "=a"(ret)
               : "Nd"(port) );
   return ret;
}

void PlatformX86::init() {
// @placeholder
//
//     Step by step, now that you've grabbed the whole thing and know what's to be done:
// Make space for the interrupt descriptor table
// Tell the CPU where that space is (see GDT Tutorial: lidt works the very same way as lgdt)
// Tell the PIC that you no longer want to use the BIOS defaults (see Programming the PIC chips)
// Write a couple of ISR handlers (see Interrupt Service Routines) for both IRQs and exceptions
// Put the addresses of the ISR handlers in the appropriate descriptors (in Interrupt Descriptor Table)
// Enable all supported interrupts in the IRQ mask (of the PIC)

    // GDT::Init();
    // IDT::Init();
    // PIC::Init();

}
