#include <CVGATerminal.h>

#include <PlatformX86.h>


inline uint16_t Cursor::index() {
    return (y*kVGATerminalWidth) + x;
}

inline void Cursor::move(uint8_t x, uint8_t y) {
    this->x = x; this->y = y;
    this->updateBiosCursorReference();
}

inline void Cursor::tab() {
    this->x += 4;
    this->x -= (this->x%4);
    this->updateBiosCursorReference();
}

inline void Cursor::nextLine() {
    this->move(0, this->y+1);
}

inline bool Cursor::atEnd() {
    return y == kVGATerminalHeight;
}

inline void Cursor::increment() {
    x+=1;
    if(x >= kVGATerminalWidth) {
        x=0; y+=1;
    }
    updateBiosCursorReference();
}

inline void Cursor::updateBiosCursorReference() {
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (this->index() & 0xFF) );
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) (this->index() >> 8) & 0xFF);
}

void CVGATerminal::init() {
    this->_buffer = (TermChar*)0xC03FF000;
    moveCursor(0,0);

    for(int x=0;x<kVGATerminalWidth; x++) {
        for(int y=0; y<kVGATerminalHeight; y++) {
            _buffer[x+y].setColor(kVgaColorLightGrey, kVgaColorBlack);
        }
    }
    clear();

    this->printf("[VGATerminal] initialized\n");
}

void CVGATerminal::scroll() {
    /** Slide all lines up one to make room for the newline */
    for(int i=0; i<(kVGATerminalHeight-1); i++) {
        for(int j=0; j<kVGATerminalWidth; j++) {
            this->_buffer[(i*kVGATerminalWidth)+j] = (this->_buffer[((i+1)*kVGATerminalWidth) + j]);
        }
    }
    /** Clear newline */
    for(int x = 0; x < kVGATerminalWidth; x++) {
        this->_buffer[((kVGATerminalHeight-1)*kVGATerminalWidth)+x].setChar(' ');
    }
    moveCursor(0, kVGATerminalHeight-1);
}

void CVGATerminal::putChar(char c) {
    if(c == '\n') {
        if( cursor.atEnd() ) scroll();
        cursor.nextLine();
    }else if(c == '\t') {
        cursor.tab();
    }else {
        this->_buffer[cursor.index()].setChar(c);
        cursor.increment();
        if( cursor.atEnd() ) scroll();
    }
}

void CVGATerminal::moveCursor(uint8_t x, uint8_t y) {
    this->cursor.move(x,y);
}

void CVGATerminal::printf(const char *str) {
    for(size_t i=0; i<strlen(str); i++ ){
        putChar(str[i]);
    }
}

void CVGATerminal::clear() {
    for(int i=0;i<(kVGATerminalWidth*kVGATerminalHeight); i++) {
        this->_buffer[i].setChar(' ');
    }
    this->moveCursor(0,0);
}

void CVGATerminal::updateBiosCursorReference() {
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (this->cursor.index() & 0xFF) );
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) (this->cursor.index() >> 8) & 0xFF);
}


CVGATerminal VGATerminal;
