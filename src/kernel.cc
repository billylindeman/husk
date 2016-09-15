

#include <stddef.h>
#include <stdint.h>

#include <CVGATerminal.h>
#include <PlatformX86.h>


PlatformX86 platform = PlatformX86();

extern "C"
void kernel_start(void) {

	platform.init();


	platform.printk("[husk] Platform Initialized\n");
	platform.printk("\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");
	platform.printk("This is a test\n");

	for(;;) {
		asm("hlt");
	}
}
