

boot:
	mkdir -p build/
	i686-elf-as src/boot.s -o build/boot.o

kernel:
	mkdir -p build/
	i686-elf-g++ -c src/kernel.cc -o build/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

clean:
	rm -fr build/

all: clean boot kernel
	mkdir -p build/
	i686-elf-gcc -T linker.ld -o build/husk-kernel.bin -ffreestanding -O2 -nostdlib build/*.o -lgcc


run:
	qemu-system-i386 -kernel build/husk-kernel.bin
