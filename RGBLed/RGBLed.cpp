#include "mbed.h"
#include "RGBLed.h"

RGBLed::RGBLed(PinName redPin, PinName greenPin, PinName bluePin) {
    redPwm   = new PwmOut(redPin);
    greenPwm = new PwmOut(greenPin);
    bluePwm  = new PwmOut(bluePin);
    
    redPwm->period(0.01);
    greenPwm->period(0.01);
    bluePwm->period(0.01);
    
    redValue   = 0;
    greenValue = 0;
    blueValue  = 0;
    
    disable();
}

RGBLed::~RGBLed(void) {
    delete redPwm;
    delete greenPwm;
    delete bluePwm;
}
        
void RGBLed::setRed(uint8_t value) {
    redValue = value;
}
void RGBLed::setGreen(uint8_t value) {
    greenValue = value;
}
void RGBLed::setBlue(uint8_t value) {
    blueValue = value;

}

void RGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    setRed(red);
    setGreen(green);
    setBlue(blue);
}
void RGBLed::getColor(uint8_t *red, uint8_t *green, uint8_t *blue) {
    if(red)
        *red = redValue;
    
    if(green)
        *green = greenValue;
    
    if(blue)
        *blue = blueValue;
}

uint8_t RGBLed::getRed(void) {
    return redValue;
}
uint8_t RGBLed::getGreen(void) {
    return greenValue;
}
uint8_t RGBLed::getBlue(void) {
    return blueValue;
}

bool RGBLed::getState(void) {
    return enabled;
}

void RGBLed::enable(void) {
    *redPwm   = ((double)redValue / 255.0);
    *greenPwm = ((double)greenValue / 255.0);
    *bluePwm  = ((double)blueValue / 255.0);
    
    enabled = true;
}
void RGBLed::disable(void) {
    *redPwm   = 0;
    *greenPwm = 0;
    *bluePwm  = 0;
    
    enabled = false;
}

void RGBLed::update(void) {
    if(enabled) {
        *redPwm   = ((double)redValue / 255.0);
        *greenPwm = ((double)greenValue / 255.0);
        *bluePwm  = ((double)blueValue / 255.0);
    }
}