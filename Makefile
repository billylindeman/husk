



#OBJECT CONFIG
OBJS  = $(patsubst %.c,%.o,$(wildcard src/*.c))
OBJS += $(patsubst %.c,%.o,$(wildcard src/*/*.c))
OBJS += $(patsubst %.cc,%.o,$(wildcard src/*.cc))
OBJS += $(patsubst %.cc,%.o,$(wildcard src/*/*.cc))
OBJS += $(patsubst %.s,%.o,$(wildcard src/*.s))

#TOOLCHAIN CONFIG
CFLAGS   := -std=c++11 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -fpermissive
CXXFLAGS :=

TARGET := i686-elf-
AS  := $(TARGET)as
CC  := $(TARGET)gcc
CXX := $(TARGET)g++
CPP := $(TARGET)cpp
LD  := $(TARGET)ld

## OBJECT TARGETS
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.cc
	${CXX} ${CFLAGS} ${CXXFLAGS} -c $< -o $@

%.o: %.s
	${AS} $< -o $@



## OTHER TARGETS
husk-kernel: ${OBJS}
	$(CXX) ${CFLAGS} ${CXXFLAGS}-T linker.ld -o $(@).bin ${OBJS}

run:
	qemu-system-i386 -kernel husk-kernel.bin

all: husk-kernel

.PHONY: clean
clean:
	-rm -f src/*.o src/*/*.o src/*/*/*o
	-rm -f husk-kernel
