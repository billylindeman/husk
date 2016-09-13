

#include <stddef.h>
#include <stdint.h>

#include "video/CVGATerminal.h"

extern "C"
void kernel_main(void) {
	VGATerminal.init();
	VGATerminal.clear();

	VGATerminal.printf("[husk] kernel init\n");
	VGATerminal.printf("\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");
	VGATerminal.printf("This is a test\n");

	for(;;) {
		asm("hlt");
	}
}
