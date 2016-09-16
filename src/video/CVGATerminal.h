#ifndef VGATERMINAL_H
#define VGATERMINAL_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <string.h>

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

static const int kVGATerminalWidth = 80;
static const int kVGATerminalHeight = 25;

typedef struct {
    uint8_t character;
    uint8_t color;

    inline void setColor(uint8_t fg, uint8_t bg) {
		color = fg | bg << 4;
	}

	inline void setChar(char c) {
		character = c;
	}
} TermChar;


typedef struct {
	uint8_t x;
	uint8_t y;

	inline uint16_t index();
	inline void move(uint8_t x, uint8_t y);
	inline void tab();
	inline void nextLine();
	inline void increment();
	inline void updateBiosCursorReference();
} Cursor;

class CVGATerminal {
private:
	TermChar* _buffer;

	void updateBiosCursorReference();
public:
	Cursor cursor;

	void init();
	void putChar(char c);
    void moveCursor(uint8_t x, uint8_t y);
    void printf(const char *str);
    void clear();

};

extern CVGATerminal VGATerminal;

#endif
