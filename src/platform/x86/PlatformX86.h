#ifndef PLATFORM_X86
#define PLATFORM_X86

#include <IPlatform.h>
#include <stdint.h>

class PlatformX86 : IPlatform<PlatformX86> {
public:
    void init();
};

extern "C" {
    void outb(uint16_t port, uint8_t val);
    uint8_t inb(uint16_t port);
}

#endif
