#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct {
    uint16_t size;
    uint32_t offset;
} __attribute__((__packed__)) GDTDescriptorType;


typedef uint8_t GDTEntryAccessByte;

static const GDTEntryAccessByte kGDTAccessByteCode = 0x9A;
static const GDTEntryAccessByte kGDTAccessByteData = 0x92;


typedef struct GDTEntryType {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
    inline void configure(uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
} GDTEntryType;


extern GDTDescriptorType GDTDescriptor;
extern GDTEntryType GDT[3];


extern void GDTInit();
extern void GDTFlush();
#endif
