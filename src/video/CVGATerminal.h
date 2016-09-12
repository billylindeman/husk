#ifndef VGATERMINAL_H
#define VGATERMINAL_H

#include <tuple>

typedef enum kVgaColor {
	kVgaColorBlack = 0,
	kVgaColorBlue = 1,
	kVgaColorGreen = 2,
	kVgaColorCyan = 3,
	kVgaColorRed = 4,
	kVgaColorMagenta = 5,
	kVgaColorBrown = 6,
	kVgaColorLightGrey = 7,
	kVgaColorDarkGrey = 8,
	kVgaColorLightBlue = 9,
	kVgaColorLightGreen = 10,
	kVgaColorLightCyan = 11,
	kVgaColorLightRed = 12,
	kVgaColorLightMagenta = 13,
	kVgaColorLightBrown = 14,
	kVgaColorLightWhite = 15,
} kVgaColor;

typedef struct {
    uint8_t character;
    uint8_t color;
} TerminalChar;
uint8_t makeColor(uint8_t fg, uint8_t bg);


class CVGATerminal {
    static const kWidth = 80;
    static const KHeight = 25;


};

extern CVGATerminal VGATerminal;
#endif
