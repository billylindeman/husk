#ifndef GDT_H
#define GDT_H

struct GDTRecord {
    uint16_t size;
    uint32_t offset;
};


typedef struct {
    uint8_t data[8];

    inline void base(uint32_t base) {
        data[2] = source.base & 0xFF;
        data[3] = (source.base >> 8) & 0xFF;
        data[4] = (source.base >> 16) & 0xFF;
        data[7] = (source.base >> 24) & 0xFF;
    }
    inline void limit(uint32_t limit) {
        target[0] = source.limit & 0xFF;
        target[1] = (source.limit >> 8) & 0xFF;
        target[6] |= (source.limit >> 16) & 0xF;
    }
} GDTEntry;

typedef struct {
// fill in with access bits and params
} GDTEntryAccessByte;


GDTEntry GDT[256];

static void GDTInit() {
    GDT[0]

}

#endif
