#include <PlatformX86.h>

#include <GDT.h>
#include <IDT.h>
#include <PIC.h>

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
    asm ("cli");
}
void X86InterruptsEnable(){
    asm ("sti");
}

void PlatformX86::printk(const char *str) {
    this->vga.printf(str);
}

void PlatformX86::init() {
    this->vga.init();
    platform.printk("[PlatformX86] Platform Initialization\n");

    GDTInit();
    IDTInit();
    PIC.init();

    PIC.unmask(2);
    PIC.unmask(0);

}

void PlatformX86::halt(){
    for(;;) {
        asm ("hlt");
    }
}
