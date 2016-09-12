

boot:
	i686-elf-as boot.s -o boot.o

kernel:
	i686-elf-g++ -c kernel.cc -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

clean:
	rm -f *.o
	rm -f bos.bin

all: clean boot kernel
	i686-elf-gcc -T linker.ld -o bos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc


run:
	qemu-system-i386 -kernel bos.bin
