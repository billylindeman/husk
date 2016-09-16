#ifndef PLATFORM_X86
#define PLATFORM_X86

#include <stdint.h>

#define asm __asm__
#define volatile __volatile__

#include <IPlatform.h>
#include <CVGATerminal.h>

class PlatformX86 : IPlatform<PlatformX86> {
private:
    CVGATerminal vga;
public:
    void init();
    void printk(const char *str);
    void halt();
};

extern "C" {
    void outb(uint16_t port, uint8_t val);
    uint8_t inb(uint16_t port);

    void X86InterruptsEnable();
    void X86InterruptsDisable();
}

extern PlatformX86 platform;

#endif
