#ifndef __MENU_ACTION_RGB_MANAGER_H_
#define __MENU_ACTION_RGB_MANAGER_H_

#include "MenuAction.h"
#include "RGBLed.h"
enum RGB_MANAGER_MODE {
    STATE_CONF,
    RED_CONF,
    BLUE_CONF,
    GREEN_CONF
};

class MenuActionRGBManager : public MenuAction {
    public:
        MenuActionRGBManager(RGBLed *rgbLed, RGB_MANAGER_MODE mode);
        virtual void execute(void);
        virtual void execute(void* arg);
            
    private:
        RGBLed *rgbLed;
        RGB_MANAGER_MODE mode;
};

#endif /* __MENU_ACTION_RGB_MANAGER_H_ */
