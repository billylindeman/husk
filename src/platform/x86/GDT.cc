
#include <GDT.h>

#include <PlatformX86.h>

GDTDescriptorType GDTDescriptor;
GDTEntryType GDT[256];

void GDTInit() {
    platform.printk("[GDT] Initizing GDTR\n");
    GDTDescriptor.offset = (uint32_t)&GDT;
    GDTDescriptor.size = sizeof(GDT);

    __asm__ volatile("lgdt (%0)" :: "r"(&GDTDescriptor) );
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

inline uint8_t GDTEntryAccessByte::present() {
    return data & 0b100000;
}
