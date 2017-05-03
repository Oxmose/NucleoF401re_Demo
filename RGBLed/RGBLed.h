#ifndef __RGB_LED_H_
#define __RGB_LED_H_

#include "mbed.h"

class RGBLed {
    public:
        RGBLed(PinName redPin, PinName greenPin, PinName bluePin);
        ~RGBLed(void);
        
        void setRed(uint8_t value);
        void setGreen(uint8_t value);
        void setBlue(uint8_t value);
        
        uint8_t getRed(void);
        uint8_t getGreen(void);
        uint8_t getBlue(void);
        
        void setColor(uint8_t red, uint8_t green, uint8_t blue);
        void getColor(uint8_t *red, uint8_t *green, uint8_t *blue);
        
        bool getState(void);
        
        void enable(void);
        void disable(void);
        
        void update(void);
        
    private:
        PwmOut *redPwm;
        PwmOut *greenPwm;
        PwmOut *bluePwm;
        
        uint8_t redValue;
        uint8_t greenValue;
        uint8_t blueValue;
        
        bool enabled;
};

#endif /* __RGB_LED_H_ */