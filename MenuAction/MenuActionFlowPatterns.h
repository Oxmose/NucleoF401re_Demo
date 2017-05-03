#ifndef __MENU_ACTION_FLOW_PATTERNS_H_
#define __MENU_ACTION_FLOW_PATTERNS_H_

#include "LCDScreen.h"
#include "Menu.h"
#include "MenuAction.h"
#include "MenuActionLedFlow.h"
#include "mbed.h"
#include <vector>

class MenuActionFlowPatterns: public MenuAction {
    public:
        MenuActionFlowPatterns(LCDScreen *mainLCD,
                                 std::vector<DigitalOut*> &ledsIO, 
                                 DigitalIn *enterBtn, 
                                 DigitalIn *upBtn, 
                                 DigitalIn *downBtn);
        virtual ~MenuActionFlowPatterns();
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
        static MenuActionFlowPatterns *instance;
};

#endif /* __MENU_ACTION_FLOW_PATTERNS_H_ */