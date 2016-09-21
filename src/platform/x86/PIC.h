#ifndef PIC_H
#define PIC_H


#include <stdint.h>

#include <PlatformX86.h>

const uint8_t kPIC1BaseAddress = 0x20;
const uint8_t kPIC1CommandPort = kPIC1BaseAddress;
const uint8_t kPIC1DataPort    = (kPIC1BaseAddress+1);

const uint8_t kPIC2BaseAddress = 0xA0;
const uint8_t kPIC2CommandPort = kPIC2BaseAddress;
const uint8_t kPIC2DataPort    = (kPIC2BaseAddress+2);


const uint8_t kPICCommandEOI             = 0x20;

const uint8_t kPICICW1UseICW4            = 0x01;  /** ICW4 (not) needed           */
const uint8_t kPICICW1Single             = 0x02;  /** Single (cascade) mode       */
const uint8_t kPICICW1Interval4          = 0x04;  /** Call address inverval 4 (8) */
const uint8_t kPICICW1Level              = 0x08;  /** Level triggered (edge) mode */
const uint8_t kPICICW1Init               = 0x10;  /** Initialization - required   */

const uint8_t kPICICW48086               = 0x01;  /** 8086/88 (MCS-80/85) mode    */
const uint8_t kPICICW4Auto               = 0x02;  /** Auto (normal) EOI           */
const uint8_t kPICICW4BufferSlave        = 0x08;  /** Buffered mode slave         */
const uint8_t kPICICW4BufferMaster       = 0x0C;  /** BUffered mode master        */
const uint8_t kPICICW4SpecialFullyNested = 0x10;  /** Special fully nested (not)  */


class CPIC {

public:
    static void init();
    static void remap(uint8_t pic1Vector, uint8_t pic2Vector);
    static void eoi(uint8_t irq);

    static void mask(uint8_t irq);
    static void unmask(uint8_t irq);
};

extern CPIC PIC;


#endif
