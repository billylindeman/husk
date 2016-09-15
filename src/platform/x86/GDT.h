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
    uint8_t data[8];

    inline void base(uint32_t base);
    inline void limit(uint32_t limit);
    inline void accessByte(GDTEntryAccessByte accessByte);
    inline void flags(uint8_t sizeBit, uint8_t granularityBit);

} GDTEntryType;


extern GDTDescriptorType GDTDescriptor;
extern GDTEntryType GDT[256];


extern void GDTInit();
extern void GDTFlush();
#endif
