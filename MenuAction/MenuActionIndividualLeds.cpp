#include "MenuActionIndividualLeds.h"
#include "MenuActionExecFunc.h"
#include "MenuActionLed.h"
#include "LCDScreen.h"
#include "Menu.h"
#include "mbed.h"
#include <vector>
#include <sstream>

MenuActionIndividualLeds::MenuActionIndividualLeds(
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

MenuActionIndividualLeds::~MenuActionIndividualLeds() {
    if(this->menu)
        delete this->menu;
}

void MenuActionIndividualLeds::execute(void) {
    this->menu = new Menu("Individual Leds\nSelection:", mainLCD);
    this->inMenu = true;
    this->selectedOptionState.clear();
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

void MenuActionIndividualLeds::execute(void * arg) {
    execute();
}

void MenuActionIndividualLeds::setUI(void) {
    mainLCD->clear();
    uint32_t ledsIOSize = ledsIO.size();
    for(uint32_t i = 0; i < ledsIOSize; ++i) {
        std::stringstream sstm;
        sstm << "| Enable led " << i + 1 << "  |";
        menu->addItem(sstm.str(), 
                      new MenuActionLed(ledsIO[i]));
        selectedOptionState.push_back(false);
    }
    menu->addSeparator(' ');
    menu->addItem(" < Back             ", new MenuActionExecFunc(backAction));
    menu->display();
} 

MenuActionIndividualLeds* MenuActionIndividualLeds::instance;

void MenuActionIndividualLeds::backAction(void) {
    if(instance != NULL) {
        instance->inMenu = false;
        delete instance->menu;
        for(uint32_t i = 0; i < instance->ledsIO.size(); ++i) {
            *(instance->ledsIO[i]) = false;
        }
    }
}

void MenuActionIndividualLeds::upBtnAction(void) {
    menu->selectPreviousItem();
    menu->display();
}

void MenuActionIndividualLeds::downBtnAction(void) {
    menu->selectNextItem();
    menu->display();
}

void MenuActionIndividualLeds::enterBtnAction(void) {
    uint32_t selectedItem = menu->getSelectedItem();
    
    if(selectedItem < ledsIO.size()) {
        selectedOptionState[selectedItem] = !selectedOptionState[selectedItem];
        
        std::stringstream sstm;        
        if(selectedOptionState[selectedItem])
            sstm << "| Disable led " << selectedItem + 1 << " |";
        else
            sstm << "| Enable led " << selectedItem + 1 << "  |";
            
        menu->editLabel(selectedItem, sstm.str());
        menu->display();  
    }
      
    menu->performAction();
}