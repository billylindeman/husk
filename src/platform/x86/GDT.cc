

#include <GDT.h>

#include <PlatformX86.h>

#define asm __asm__
#define volatile __volatile__


GDTDescriptorType GDTDescriptor;
GDTEntryType GDT[256];

void GDTInit() {
    platform.printk("[GDT] Initizing GDTR\n");
    GDTDescriptor.offset = (uint32_t)&GDT;
    GDTDescriptor.size = sizeof(GDT);

    /** Install GDT descriptor into GDTR */
    asm volatile("lgdt (%0)" :: "r"(&GDTDescriptor) );

    platform.printk("[GDT] Setting up memory map.");

    GDT[0].base(0);
    GDT[0].limit(0);
    GDT[0].accessByte(0);

    GDT[1].base(0);
    GDT[1].limit(0xFFFFFFFF);
    GDT[1].accessByte(kGDTAccessByteCode);

    GDT[2].base(0);
    GDT[2].limit(0xFFFFFFFF);
    GDT[2].accessByte(kGDTAccessByteData);

    GDTFlush();
}

void GDTFlush() {
//     asm volatile ("jmp 0x08:GDTFlushHandler");
// GDTFlushHandler:
//     asm ("mov %ax, 0x10");
//     asm ("mov %ds, %ax");
//     asm ("mov %es, %ax");
//     asm ("mov %fs, ax");
//     asm ("mov %ss, ax");
}

inline void GDTEntryType::base(uint32_t base) {
    data[2] = base & 0xFF;
    data[3] = (base >> 8) & 0xFF;
    data[4] = (base >> 16) & 0xFF;
    data[7] = (base >> 24) & 0xFF;
}

inline void GDTEntryType::limit(uint32_t limit) {
    data[0] = limit & 0xFF;
    data[1] = (limit >> 8) & 0xFF;
    data[6] |= (limit >> 16) & 0xF;
}

inline void GDTEntryType::accessByte(GDTEntryAccessByte accessByte) {
    data[5] = accessByte;
}
//
// inline uint8_t GDTEntryAccessByte::present() {
//     return data & 0b100000;
// }
