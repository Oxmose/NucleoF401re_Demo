#ifndef __MENU_ACTION_INDIVIDUAL_LEDS_H_
#define __MENU_ACTION_INDIVIDUAL_LEDS_H_

#include "LCDScreen.h"
#include "Menu.h"
#include "MenuAction.h"
#include "MenuActionLed.h"
#include "mbed.h"
#include <vector>

class MenuActionIndividualLeds : public MenuAction {
    public:
        MenuActionIndividualLeds(LCDScreen *mainLCD,
                                 std::vector<DigitalOut*> &ledsIO, 
                                 DigitalIn *enterBtn, 
                                 DigitalIn *upBtn, 
                                 DigitalIn *downBtn);
        virtual ~MenuActionIndividualLeds();
        virtual void execute(void);
        virtual void execute(void *arg);
        void setUI(void);
        void enterBtnAction(void);
        void upBtnAction(void);
        void downBtnAction(void);
        static void backAction(void);
    
    private:
        std::vector<DigitalOut*> ledsIO;
        DigitalIn *enterBtn;
        DigitalIn *upBtn;
        DigitalIn *downBtn;
        Menu *menu;
        LCDScreen *mainLCD;
        volatile bool inMenu;
        static MenuActionIndividualLeds *instance;
        std::vector<bool> selectedOptionState;
};

#endif /* __MENU_ACTION_INDIVIDUAL_LEDS_H_ */