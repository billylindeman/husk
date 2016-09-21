#include <PIC.h>

CPIC PIC;

void CPIC::init() {
    CPIC::remap(0x20, 0x28);
}

void CPIC::remap(uint8_t pic1Vector, uint8_t pic2Vector)
{
    //save old PIC masks
	unsigned char picOneMask, picTwoMask;
	picOneMask = inb(kPIC1DataPort);
	picTwoMask = inb(kPIC2DataPort);

	outb(kPIC1CommandPort, kPICICW1Init+kPICICW1UseICW4);  // starts the initialization sequence (in cascade mode)
	outb(kPIC2CommandPort, kPICICW1Init+kPICICW1UseICW4);

	outb(kPIC1DataPort, pic1Vector);                 // ICW2: Master PIC vector offset
	outb(kPIC2DataPort, pic2Vector);                 // ICW2: Slave PIC vector offset

	outb(kPIC1DataPort, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(kPIC2DataPort, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)

	outb(kPIC1DataPort, kPICICW48086);
	outb(kPIC2DataPort, kPICICW48086);

	outb(kPIC1DataPort, 0xff);
	outb(kPIC2DataPort, 0xff);
}

void CPIC::eoi(uint8_t irq) {
    if(irq > 8) outb(kPIC2CommandPort, kPICCommandEOI);
    outb(kPIC1CommandPort,kPICCommandEOI);
}

void CPIC::mask(uint8_t irq) {
    uint16_t port;
	uint8_t value;
	if (irq < 8) {
		port = kPIC1DataPort;
	} else {
		port = kPIC2DataPort;
		irq -= 8;
	}

	value = inb(port);
	value |= (1 << irq);
	outb(port, value);
}

void CPIC::unmask(uint8_t irq) {
    uint16_t port;
	uint8_t value;
	if (irq < 8) {
		port = kPIC1DataPort;
	} else {
		port = kPIC2DataPort;
		irq -= 8;
	}
	value = inb(port);
	value &= ~(1 << irq);
	outb(port, value);
}
