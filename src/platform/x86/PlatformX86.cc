#include <PlatformX86.h>

#include <GDT.h>
#include <IDT.h>

extern PlatformX86 platform;

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

void X86InterruptsDisable(){
    asm ("sti");
}
void X86InterruptsEnable(){
    asm ("cli");
}

void PlatformX86::printk(const char *str) {
    this->vga.printf(str);
}

void PlatformX86::init() {
    this->vga.init();
    platform.printk("[PlatformX86] Platform Initialization\n");
// @placeholder
//
//     Step by step, now that you've grabbed the whole thing and know what's to be done:
// Make space for the interrupt descriptor table
// Tell the CPU where that space is (see GDT Tutorial: lidt works the very same way as lgdt)
// Tell the PIC that you no longer want to use the BIOS defaults (see Programming the PIC chips)
// Write a couple of ISR handlers (see Interrupt Service Routines) for both IRQs and exceptions
// Put the addresses of the ISR handlers in the appropriate descriptors (in Interrupt Descriptor Table)
// Enable all supported interrupts in the IRQ mask (of the PIC)

    GDTInit();
    IDTInit();
    // IDT::Init();
    // PIC::Init();

}

void PlatformX86::halt(){
    for(;;) {
        asm ("hlt");
    }
}
