#ifndef IDT_H
#define IDT_H
#include <stdint.h>

typedef struct {
    uint16_t size;
    uint32_t offset;
} IDTDescriptorType;

typedef struct {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t zero;      // unused, set to 0
   uint8_t type_attr; // type and attributes, see below
   uint16_t offset_2; // offset bits 16..31

   inline void configure(uint32_t address, uint16_t codeSegmentSelector, uint8_t type);
} IDTEntry;


const static uint8_t kIDTGateTypeTask32 = 0x5;
const static uint8_t kIDTGateTypeInterrupt16 = 0x6;
const static uint8_t kIDTGateTypeTrap16 = 0x7;
const static uint8_t kIDTGateTypeInterrupt32 = 0xE;
const static uint8_t kIDTGateTypeTrap32 = 0xF;


extern IDTDescriptorType IDTDescriptor;
extern IDTEntry IDT[256];

extern "C" {
    void IDTInit();
}



#endif
