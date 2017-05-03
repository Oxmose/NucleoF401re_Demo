#include "MenuActionFlowPatterns.h"
#include "MenuActionExecFunc.h"
#include "MenuActionLedFlow.h"
#include "LCDScreen.h"
#include "Menu.h"
#include "mbed.h"
#include <vector>
#include <sstream>

MenuActionFlowPatterns::MenuActionFlowPatterns(
                                 LCDScreen *mainLCD,
                                 std::vector<DigitalOut*> &ledsIO, 
                                 DigitalIn *enterBtn, 
                                 DigitalIn *upBtn, 
                                 DigitalIn *downBtn) {
    this->ledsIO = ledsIO;
    
    this->enterBtn = enterBtn;
    this->upBtn = upBtn;
    this->downBtn = downBtn;
    
    this->inMenu = true;
    this->mainLCD = mainLCD;
    
    instance = this;
}

MenuActionFlowPatterns::~MenuActionFlowPatterns() {
    if(this->menu)
        delete this->menu;
}

void MenuActionFlowPatterns::execute(void) {
    this->menu = new Menu("Led flow patterns\nSelection:", mainLCD);
    this->inMenu = true;
    setUI();   

    while(inMenu) {
        if(*downBtn) {
            /* Unbound */
            while(*downBtn);
            downBtnAction();
        }
        else if(*upBtn) {
            /* Unbound */
            while(*upBtn);
            upBtnAction();
        }
        else if(*enterBtn) {
            /* Unbound */
            while(*enterBtn);
            enterBtnAction();
        }
        wait(0.1);
    }
}

void MenuActionFlowPatterns::execute(void * arg) {
    execute();
}

void MenuActionFlowPatterns::setUI(void) {
    mainLCD->clear();
    
    menu->addItem("|       Linear      |", 
                  new MenuActionLedFlow(ledsIO, LED_FLOW_LINEAR, 
                                        enterBtn));
                                                               
    menu->addItem("|    Linear Once    |", 
                 new MenuActionLedFlow(ledsIO, LED_FLOW_LINEAR_ONCE, 
                                       enterBtn));
                                                               
    menu->addItem("|     Blink Even    |",
                 new MenuActionLedFlow(ledsIO, LED_FLOW_BLINK_EVEN, 
                                       enterBtn));
                                                            
    menu->addItem("|     Morse SOS     |", 
                 new MenuActionLedFlow(ledsIO, LED_FLOW_MORSE, 
                                       enterBtn));
    menu->addSeparator(' ');
    menu->addItem(" < Back", new MenuActionExecFunc(backAction));
    menu->display();
} 

MenuActionFlowPatterns* MenuActionFlowPatterns::instance;

void MenuActionFlowPatterns::backAction(void) {
    if(instance != NULL) {
        instance->inMenu = false;
        delete instance->menu;
        
        for(uint32_t i = 0; i < instance->ledsIO.size(); ++i) {
            *(instance->ledsIO[i]) = false;
        }
    }    
}

void MenuActionFlowPatterns::upBtnAction(void) {
    menu->selectPreviousItem();
    menu->display();
}

void MenuActionFlowPatterns::downBtnAction(void) {
    menu->selectNextItem();
    menu->display();
}

void MenuActionFlowPatterns::enterBtnAction(void) {
    if(menu->getSelectedItem() < menu->size() - 1) {
        mainLCD->clear();
        mainLCD->printHeader("Flow pattern\nRunning...");
        mainLCD->setHighlight(true);
        mainLCD->printf(" < Back");
        mainLCD->setHighlight(false);
        mainLCD->display();
    }          
    menu->performAction();
    if(inMenu) {
        mainLCD->clear();
        menu->display();
    }
}