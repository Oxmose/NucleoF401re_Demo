#ifndef __OLEDSCREEN_H_
#define __OLEDSCREEN_H_

#include "LCDScreen.h"
#include "Adafruit_SSD1306.h"

/* I2C PINS */
#define I2C_SDA D14
#define I2C_SCL D15

/* OLED LCD */
#define OLED_LCD_ADDR   0x78
#define OLED_LCD_WIDTH  128
#define OLED_LCD_HEIGHT 64

/* GP PINS */
#define GP_0_PIN D13

/* SETTINGS */
#define RESERVED_LINES 2
#define CHAR_LINES     6
#define CHAR_LINE_HEIGHT 8

class OLEDScreen : public LCDScreen {
    public:
        OLEDScreen();
        virtual ~OLEDScreen();
        
        virtual void printf(string str);
        virtual uint32_t getCharLines(void);
        virtual void setHighlight(bool enable);
        virtual void printHeader(string str);
        virtual void display(void);
        virtual void clear(void);
        virtual uint32_t getTextCursorX(void);
        virtual uint32_t charWidth(void);
        virtual uint32_t getCharLineWidth(void);
        
        void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, 
                        int16_t w, int16_t h, uint16_t color);
        void fillRect(int16_t x, int16_t y, int16_t w, 
                      int16_t h, uint16_t color);
    
    private:
        /* LCD I2C connection */
        I2C *i2c_lcd;

        /* 128x64 OLED LCD */
        Adafruit_SSD1306_I2c *lcd;

};

#endif /* __OLEDSCREEN_H_ */