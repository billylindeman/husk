#include <IDT.h>
#include <PlatformX86.h>


IDTDescriptorType IDTDescriptor;
IDTEntry IDT[256];

extern void do_test();
extern "C" void _IDTInternalFaultHandler(void);
extern "C" void _ISRInternal(void);

extern "C" void isr() {
    platform.printk("INT $0x40 Triggered!\n");
}

void IDTInit() {
    platform.printk("[IDT] Initializing\n");

    X86InterruptsDisable();

    IDTDescriptor.offset = (uint32_t)&IDT;
    IDTDescriptor.size = sizeof(IDT);

    X86InterruptsEnable();

    platform.printk("[IDT] Table Loaded\n");

    platform.printk("[IDT] Installing test handler into 49\n");
    for(int i=0; i<256; i++) {
        IDT[i].configure((uint32_t)&_IDTInternalFaultHandler, 0x8, kIDTGateTypeInterrupt32);
    }

    IDT[49].configure((uint32_t)&_ISRInternal, 0x8, kIDTGateTypeInterrupt32);
    asm volatile("lidt (%0)" :: "r"(&IDTDescriptor) );

    platform.printk("[IDT] Triggering int $49\n");
    asm ("int $49");

}

extern "C" void _IDTFaultHandler() {
    platform.printk("[PANIC] Fault Detected! \n");
    platform.halt();
}

void IDTEntry::configure(uint32_t address, uint16_t codeSegmentSelector, uint8_t type) {
    this->offset_1 = address & 0xFFFF;
    this->offset_2 = (address >> 16) & 0xFFFF;
    this->zero = 0x00;
    this->selector = 0x8;               // GDT Selector 0x8 is kernel code segment
    // this ->type_attr = 0b10000000;      // set present bit
    // this ->type_attr |= (type & 0x0F);  // set type attribute

    this->type_attr = 0x8E;
}
