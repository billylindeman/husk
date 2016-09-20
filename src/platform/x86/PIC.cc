#include <PIC.h>

CPIC PIC;

void CPIC::init() {
    CPIC::remap(32, 40);
}

void CPIC::remap(uint8_t pic1Vector, uint8_t pic2Vector)
{
    //save old PIC masks
	unsigned char picOneMask, picTwoMask;
	picOneMask = inb(kPIC1DataPort);
	picTwoMask = inb(kPIC2DataPort);

	outb(kPIC1CommandPort, kPICICW1Init+kPICICW1_ICW1);  // starts the initialization sequence (in cascade mode)
	// io_wait();
	outb(kPIC2CommandPort, kPICICW1Init+kPICICW1_ICW1);
	// io_wait();
	outb(kPIC1DataPort, pic1Vector);                 // ICW2: Master PIC vector offset
	// io_wait();
	outb(kPIC2DataPort, pic2Vector);                 // ICW2: Slave PIC vector offset
	// io_wait();
	outb(kPIC1DataPort, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	// io_wait();
	outb(kPIC2DataPort, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	// io_wait();

	outb(kPIC1DataPort, kPICICW48086);
	// io_wait();
	outb(kPIC2DataPort, kPICICW48086);
	// io_wait();

	outb(kPIC1DataPort, picOneMask);   // restore saved masks.
	outb(kPIC2DataPort, picTwoMask);
}
