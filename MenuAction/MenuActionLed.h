#ifndef __MENU_ACTION_LED_H_
#define __MENU_ACTION_LED_H_

#include "MenuAction.h"
#include "mbed.h"

class MenuActionLed : public MenuAction {
    public:
        MenuActionLed(DigitalOut *ledIO);
        virtual void execute(void);
        virtual void execute(void *arg);
        DigitalOut *ledIO;
        bool state;
};

#endif /* __MENU_ACTION_LED_H_ */
