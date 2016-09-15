#ifndef PLATFORM_X86
#define PLATFORM_X86

#include <stdint.h>


#include <IPlatform.h>
#include <CVGATerminal.h>

class PlatformX86 : IPlatform<PlatformX86> {
private:
    CVGATerminal vga;
public:
    void init();
    void printk(char *str);
};

extern "C" {
    void outb(uint16_t port, uint8_t val);
    uint8_t inb(uint16_t port);
}

extern PlatformX86 platform;

#endif
