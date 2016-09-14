#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct {
    uint16_t size;
    uint32_t offset;
} __attribute__((__packed__)) GDTDescriptorType;

typedef struct {
    uint8_t data[8];

    inline void base(uint32_t base);
    inline void limit(uint32_t limit);

} GDTEntryType;

typedef struct {
    uint8_t data;
    inline uint8_t present();

} GDTEntryAccessByte;


extern GDTDescriptorType GDTDescriptor;
extern GDTEntryType GDT[256];


extern void GDTInit();
#endif
