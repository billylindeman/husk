

#include <stddef.h>
#include <stdint.h>

#include <CVGATerminal.h>
#include <PlatformX86.h>

auto platform = PlatformX86();


extern "C"
void kernel_start(void) {
	VGATerminal.init();

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
