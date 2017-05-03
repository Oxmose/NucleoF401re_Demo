#include "Adafruit_SSD1306.h"
#include "OLEDScreen.h"

OLEDScreen::OLEDScreen(void) {
    i2c_lcd = new I2C(I2C_SDA, I2C_SCL);
    lcd = new Adafruit_SSD1306_I2c(*i2c_lcd, GP_0_PIN, OLED_LCD_ADDR, OLED_LCD_HEIGHT, OLED_LCD_WIDTH);
}

OLEDScreen::~OLEDScreen(void) {
    delete i2c_lcd;
    delete lcd;
}

void OLEDScreen::printf(string str) {
    if(lcd->getTextCursorY() < CHAR_LINE_HEIGHT * 2) {
        lcd->setTextCursor(0, 2 * CHAR_LINE_HEIGHT);
    }
    lcd->printf("%s", str.c_str());
}

uint32_t OLEDScreen::getCharLines(void) {
    return CHAR_LINES;
}

void OLEDScreen::setHighlight(bool enable) {
    lcd->setTextColor(enable ? BLACK : WHITE, enable ? WHITE : BLACK);
}

void OLEDScreen::printHeader(string str) {
    lcd->setTextCursor(0, 0);
    lcd->printf("%s", str.c_str());
    lcd->setTextCursor(0, CHAR_LINE_HEIGHT * 2);
}

void OLEDScreen::display(void) {
    lcd->display();
}

void OLEDScreen::clear(void) {
    lcd->clearDisplay();
    lcd->setTextCursor(0, 0);
}

uint32_t OLEDScreen::getTextCursorX(void) {
    return lcd->getTextCursorX();
}

uint32_t OLEDScreen::charWidth(void) {
    return 6;
}

uint32_t OLEDScreen::getCharLineWidth(void) {
    return 21;
}

void OLEDScreen::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, 
                            int16_t w, int16_t h, uint16_t color) {
    lcd->drawBitmap(x, y, bitmap, w, h, color);
}

void OLEDScreen::fillRect(int16_t x, int16_t y, int16_t w, 
                          int16_t h, uint16_t color) {
    lcd->fillRect(x, y, w, h, color);
}