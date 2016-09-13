


SRC_PATH := "./src"


#OBJECT CONFIG
INCLUDEPATHS += -I"$(SRC_PATH)"
INCLUDEPATHS += $(foreach dir, $(shell find $(SRC_PATH) -type d), -I"$(dir)")

OBJS = $(patsubst %.c,%.o, $(shell find $(SRC_PATH) -type f -name *.c))
OBJS += $(patsubst %.cc,%.o, $(shell find $(SRC_PATH) -type f -name *.cc))
OBJS += $(patsubst %.s,%.o, $(shell find $(SRC_PATH) -type f -name *.s))



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
