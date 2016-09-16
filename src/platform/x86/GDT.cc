

#include <GDT.h>

#include <PlatformX86.h>

GDTDescriptorType GDTDescriptor;
GDTEntryType GDT[3];
extern void GDTFlushInternal();

void GDTInit() {
    platform.printk("[GDT] Initizing GDTR\n");
    GDTDescriptor.offset = (uint32_t)&GDT;
    GDTDescriptor.size = sizeof(GDT);

    /** Install GDT descriptor into GDTR */
    platform.printk("[GDT] Setting up memory segments\n");
    GDT[0].configure(0,0,0,0);
    GDT[1].configure(0,0xFFFFFFFF,kGDTAccessByteCode, 0xCF);
    GDT[2].configure(0,0xFFFFFFFF,kGDTAccessByteData, 0xCF);


    X86InterruptsDisable();
    GDTFlushInternal();
    X86InterruptsEnable();
    platform.printk("[GDT] Flush Complete\n");
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

inline void GDTEntryType::configure(uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    this->base_low = (base & 0xFFFF);
    this->base_middle = (base >> 16) & 0xFF;
    this->base_high = (base >> 24) & 0xFF;
    this->limit_low = (limit & 0xFFFF);
    this->granularity = ((limit >> 16) & 0x0F);
    this->granularity |= (granularity & 0xF0);
    this->access = access;
}
