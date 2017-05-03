#ifndef __MENU_ACTION_LED_FLOW_H_
#define __MENU_ACTION_LED_FLOW_H_

#include "MenuAction.h"
#include "mbed.h"
#include <string>
#include <vector>

enum FLOW_MODE_E{LED_FLOW_LINEAR, 
                 LED_FLOW_LINEAR_ONCE, 
                 LED_FLOW_BLINK_EVEN, 
                 LED_FLOW_MORSE};

class MenuActionLedFlow : public MenuAction {
    public:
        MenuActionLedFlow(std::vector<DigitalOut*> &ledsIO, 
                          FLOW_MODE_E, 
                          DigitalIn* canceler,
                          string message = "");
        virtual void execute(void);
        virtual void execute(void *arg);
        void defaultMode(void);
        void linearMode(void);
        void linearOnceMode(void);
        void blinkEvenMode(void);
        void morseMode(void);
        
    private:
        std::vector<DigitalOut*> ledsIO;
        std::vector<bool> states;
        FLOW_MODE_E flowMode;
        DigitalIn *canceler;
        string message;
};

#endif /* __MENU_ACTION_LED_FLOW_H_ */
