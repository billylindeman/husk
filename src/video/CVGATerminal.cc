#include "CVGATerminal.h"

extern "C" {
    #include "../outport.h"
}

inline uint16_t Cursor::index() {
    return (y*kVGATerminalWidth) + x;
}

inline void Cursor::move(uint8_t x, uint8_t y) {
    this->x = x; this->y = y;
    this->updateBiosCursorReference();
}

inline void Cursor::nextLine() {
    this->move(0, this->y+1);
}

inline void Cursor::increment() {
    x+=1;
    updateBiosCursorReference();
}

inline void Cursor::updateBiosCursorReference() {
    outportb(0x3D4, 0x0F);
    outportb(0x3D5, (uint8_t) (this->index() & 0xFF) );
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (uint8_t) (this->index() >> 8) & 0xFF);
}

void CVGATerminal::init() {
    this->_buffer = (TermChar*)0xB8000;
    moveCursor(0,0);

    for(int x=0;x<kVGATerminalWidth; x++) {
        for(int y=0; y<kVGATerminalHeight; y++) {
            _buffer[x+y].setColor(kVgaColorLightGrey, kVgaColorBlack);
        }
    }

    clear();
}

void CVGATerminal::putChar(char c) {
    if(c == '\n') {
        cursor.nextLine();
    }else {
        this->_buffer[cursor.index()].setChar(c);
        cursor.increment();
    }
}

void CVGATerminal::moveCursor(uint8_t x, uint8_t y) {
    this->cursor.move(x,y);
}

void CVGATerminal::printf(char *str) {
    for(size_t i=0; i<strlen(str); i++ ){
        putChar(str[i]);
    }
}

void CVGATerminal::clear() {
    for(int i=0;i<(kVGATerminalWidth*kVGATerminalHeight); i++) {
        this->_buffer[i].setChar(' ');
    }
}

void CVGATerminal::updateBiosCursorReference() {
    outportb(0x3D4, 0x0F);
    outportb(0x3D5, (uint8_t) (this->cursor.index() & 0xFF) );
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (uint8_t) (this->cursor.index() >> 8) & 0xFF);
}


CVGATerminal VGATerminal;
