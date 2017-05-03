#include "MenuActionRGBManager.h"
#include "RGBLed.h"

MenuActionRGBManager::MenuActionRGBManager(RGBLed *rgbLed,
                                                RGB_MANAGER_MODE mode) {
    this->rgbLed = rgbLed;
    this->mode = mode;
}
void MenuActionRGBManager::execute(void) {
    execute(0);
}
void MenuActionRGBManager::execute(void *arg) {
    uint32_t currentValue;
    int32_t *argPtr = (int32_t*) arg;
    switch(mode) {
        case STATE_CONF:
            if(rgbLed->getState()) {
                rgbLed->disable();
            }
            else {
                rgbLed->enable();
            }
            break;
        case RED_CONF:
            currentValue = (uint32_t) rgbLed->getRed();
            currentValue += *argPtr;
            if(currentValue > 255 && *argPtr < 0)
                currentValue = 255;
            else if(currentValue > 255)
                currentValue = 0;
            rgbLed->setRed((uint8_t) currentValue);
            rgbLed->update();
            *argPtr= currentValue;
            break;
        case GREEN_CONF:
            currentValue = (uint32_t) rgbLed->getGreen();
            currentValue += *argPtr;
            if(currentValue > 255 && *argPtr < 0)
                currentValue = 255;
            else if(currentValue > 255)
                currentValue = 0;
            rgbLed->setGreen((uint8_t) currentValue);
            rgbLed->update();
            *argPtr = currentValue;
            break;
        case BLUE_CONF:
            currentValue = (uint32_t) rgbLed->getBlue();
            currentValue += *argPtr;
            if(currentValue > 255 && *argPtr < 0)
                currentValue = 255;
            else if(currentValue > 255)
                currentValue = 0;
            rgbLed->setBlue((uint8_t) currentValue);
            rgbLed->update();
            *argPtr = currentValue;
            break;
        default:
            break;
    }
    
}