#ifndef __MENU_ACTION_SENSORS_H_
#define __MENU_ACTION_SENSORS_H_

#include "mbed.h"
#include "MenuAction.h"
#include "Sensor.h"
#include "LCDScreen.h"
#include "Menu.h"
#include <vector>

class MenuActionSensors : public MenuAction {
    public:
        MenuActionSensors(LCDScreen *mainLCD,
                          std::vector<Sensor*> &sensors, 
                          DigitalIn *enterBtn, 
                          DigitalIn *upBtn, 
                          DigitalIn *downBtn);
        virtual ~MenuActionSensors(void);
        
        virtual void execute(void);
        virtual void execute(void *arg);
        
        void setUI(void);
        
        void enterBtnAction(void);
        void upBtnAction(void);
        void downBtnAction(void);
        
        static void backAction(void);
    
    private:
        std::vector<Sensor*> sensors;
        LCDScreen *mainLCD;
        Menu *menu;
        DigitalIn *enterBtn;
        DigitalIn *upBtn;
        DigitalIn *downBtn;
        bool inMenu;
        static MenuActionSensors *instance;
};

#endif /* __MENU_ACTION_SENSORS_H_ */