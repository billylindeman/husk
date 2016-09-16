#include <IDT.h>
#include <PlatformX86.h>

IDTDescriptorType IDTDescriptor;
IDTEntry IDT[256];



void isr() {
    platform.halt();
    platform.printk("\n\n----INTERRUPTED!----n\n");
}

void IDTInit() {
    platform.printk("[IDT] Initializing\n");

    X86InterruptsDisable();

    IDTDescriptor.offset = (uint32_t)&IDT;
    IDTDescriptor.size = sizeof(&IDT);
    asm volatile("lidt (%0)" :: "r"(&IDTDescriptor) );

    X86InterruptsEnable();

    platform.printk("[IDT] Table Loaded\n");

    platform.printk("[IDT] Installing test handler into 49\n");
    IDT[49].configure((uint32_t)&isr, 0x8, kIDTGateTypeInterrupt32);

    platform.printk("[IDT] Triggering int $49");
    asm ("int $49");

}

void IDTEntry::configure(uint32_t address, uint16_t codeSegmentSelector, uint8_t type) {
    this->offset_1 = address & 0xFFFF;
    this->offset_2 = address >> 16 & 0xFFFF;
    this->zero = 0x00;
    this->selector = 0x8;               // GDT Selector 0x8 is kernel code segment
    // this ->type_attr = 0b10000000;      // set present bit
    // this ->type_attr |= (type & 0x0F);  // set type attribute

    this->type_attr = 0x8E;
}
