


SRC_PATH := "./src"

#INCLUDE CONFIG
#  recursively adds dir's to include root
INCLUDE += -I"$(SRC_PATH)"
INCLUDE += $(foreach dir, $(shell find $(SRC_PATH) -type d), -I"$(dir)")

#OBJECT CONFIG
OBJS = $(patsubst %.c,%.o, $(shell find $(SRC_PATH) -type f -name *.c))
OBJS += $(patsubst %.cc,%.o, $(shell find $(SRC_PATH) -type f -name *.cc))
OBJS += $(patsubst %.s,%.o, $(shell find $(SRC_PATH) -type f -name *.s))

OBJS += $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
OBJS += $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

#TOOLCHAIN CONFIG
ASFlags  := -gstabs+
CFLAGS   := -std=c++11 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -fpermissive -g
CXXFLAGS :=

TARGET := i686-elf-
AS  := $(TARGET)as
CC  := $(TARGET)gcc
CXX := $(TARGET)g++
CPP := $(TARGET)cpp
LD  := $(TARGET)ld
GDB := $(TARGET)gdb

## OBJECT TARGETS
%.o: %.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

%.o: %.cc
	${CXX} ${CFLAGS} ${CXXFLAGS} ${INCLUDE} -c $< -o $@

%.o: %.s
	${AS} ${ASFLAGS} $< -o $@



## OTHER TARGETS
husk-kernel: ${OBJS}
	$(CXX) ${CFLAGS} ${CXXFLAGS}-T linker.ld -o $(@).bin ${OBJS}

run: husk-kernel
	qemu-system-i386 -kernel husk-kernel.bin

debug: husk-kernel
	qemu-system-i386 -kernel husk-kernel.bin -S -s &
	${GDB} -ex "file husk-kernel.bin" \
		-ex "target remote localhost:1234"

all: husk-kernel

.PHONY: clean
clean:
	-rm -f src/*.o src/*/*.o src/*/*/*o
	-rm -f husk-kernel
