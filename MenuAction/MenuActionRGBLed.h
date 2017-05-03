#ifndef __MENU_ACTION_RGB_LED_H_
#define __MENU_ACTION_RGB_LED_H_

#include "LCDScreen.h"
#include "Menu.h"
#include "MenuAction.h"
#include "RGBLed.h"
#include "mbed.h"

class MenuActionRGBLed: public MenuAction {
    public:
        MenuActionRGBLed(LCDScreen *mainLCD,
                                 RGBLed *rgbLed, 
                                 DigitalIn *enterBtn, 
                                 DigitalIn *upBtn, 
                                 DigitalIn *downBtn);
                                 
        virtual ~MenuActionRGBLed();
        virtual void execute(void);
        virtual void execute(void *arg);
        void setUI(void);
        void enterBtnAction(void);
        void upBtnAction(void);
        void downBtnAction(void);
        static void backAction(void);
    
    private:
        string alignInt(uint32_t alignWidth, char alignChar, int32_t value);
    
        RGBLed *rgbLed;
        DigitalIn *enterBtn;
        DigitalIn *upBtn;
        DigitalIn *downBtn;
        Menu *menu;
        LCDScreen *mainLCD;
        volatile bool inMenu;
        static MenuActionRGBLed *instance;
        int32_t selectedItem;
};

#endif /* __MENU_ACTION_RGB_LED_H_ */