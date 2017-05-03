#ifndef __LCDSCREEN_H_
#define __LCDSCREEN_H_

#include "mbed.h"
#include <string>

class LCDScreen {
    public:
        virtual ~LCDScreen(void) {};
        virtual void printf(string str) = 0;
        virtual uint32_t getCharLines(void) = 0;
        virtual void setHighlight(bool enable) = 0;
        virtual void printHeader(string str) = 0;
        virtual void display(void) = 0;
        virtual void clear(void) = 0;
        virtual uint32_t getTextCursorX(void) = 0;
        virtual uint32_t charWidth(void) = 0;
        virtual uint32_t getCharLineWidth(void) = 0;
};

#endif /* __LCDSCREEN_H_ */