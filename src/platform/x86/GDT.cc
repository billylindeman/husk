

#include <GDT.h>

#include <PlatformX86.h>

#define asm __asm__
#define volatile __volatile__




static GDTDescriptorType GDTDescriptor;
GDTEntryType GDT[256];
extern void GDTFlushInternal();

void GDTInit() {
    platform.printk("[GDT] Initizing GDTR\n");
    GDTDescriptor.offset = (uint32_t)&GDT;
    GDTDescriptor.size = sizeof(GDT);

    /** Install GDT descriptor into GDTR */

    platform.printk("[GDT] Setting up memory map\n");

    GDT[0].base(0);
    GDT[0].limit(0);
    GDT[0].accessByte(0);

    GDT[1].base(0);
    GDT[1].limit(0xFFFFFFFF);
    GDT[1].accessByte(kGDTAccessByteCode);
    GDT[1].flags(1,1);

    GDT[2].base(0);
    GDT[2].limit(0xFFFFFFFF);
    GDT[2].accessByte(kGDTAccessByteData);
    GDT[2].flags(1,1);

    X86InterruptsDisable();
    GDTFlushInternal();
    X86InterruptsEnable();
}

void GDTFlushInternal() {
    asm volatile("lgdt (%0)" :: "r"(&GDTDescriptor) );
    asm goto ("jmp $0x08, %0" :::: _GDTFlushRet);
_GDTFlushRet:
    asm ("mov $0x10, %ax");
    asm ("mov %ax, %ds");
    asm ("mov %ax, %es");
    asm ("mov %ax, %fs");
    asm ("mov %ax, %gs");
    asm ("mov %ax, %ss");
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

inline void GDTEntryType::flags(uint8_t sizeBit, uint8_t granularityBit) {
    data[6] |= (sizeBit & 0x1 << 6) & 0xF0;
    data[6] |= (granularityBit & 0x1 << 7) & 0xF0;
}

inline void GDTEntryType::accessByte(GDTEntryAccessByte accessByte) {
    data[5] = accessByte;
}
//
// inline uint8_t GDTEntryAccessByte::present() {
//     return data & 0b100000;
// }
