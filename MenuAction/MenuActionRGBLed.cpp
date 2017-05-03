#include "LCDScreen.h"
#include "MenuActionRGBLed.h"
#include "MenuAction.h"
#include "MenuActionExecFunc.h"
#include "MenuActionRGBManager.h"
#include "RGBLed.h"
#include "mbed.h"
#include <sstream>
#include <math.h>

MenuActionRGBLed::MenuActionRGBLed(LCDScreen *mainLCD,
                         RGBLed *rgbLed, 
                         DigitalIn *enterBtn, 
                         DigitalIn *upBtn, 
                         DigitalIn *downBtn) {
    this->mainLCD = mainLCD;
    this->rgbLed  = rgbLed;
    
    this->enterBtn = enterBtn;
    this->upBtn    = upBtn;
    this->downBtn  = downBtn;
    
    this->inMenu       = false;
    this->selectedItem = -1;
    
    this->instance = this;
}
                                 
MenuActionRGBLed::~MenuActionRGBLed() {
    if(menu)
        delete menu;
}

void MenuActionRGBLed::execute(void) {
    this->menu = new Menu("RGB led management\nSelection:", mainLCD);
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

void MenuActionRGBLed::execute(void * arg) {
    execute();
}

void MenuActionRGBLed::setUI(void) {
    mainLCD->clear();
    
    uint8_t redValue   = rgbLed->getRed();
    uint8_t greenValue = rgbLed->getGreen();
    uint8_t blueValue  = rgbLed->getBlue();
    
    bool state = rgbLed->getState();
    
    std::stringstream ss;
    ss << "| Red   -> " << alignInt(3, ' ', redValue) << "      |";
    
    menu->addItem(ss.str(),
                  new MenuActionRGBManager(rgbLed, RED_CONF));
                                        
    ss.str(string());
    ss << "| Green -> " << alignInt(3, ' ', greenValue) << "      |";                                                        
    menu->addItem(ss.str(), 
                  new MenuActionRGBManager(rgbLed, GREEN_CONF));
                  
    ss.str(string());
    ss << "| Blue  -> " << alignInt(3, ' ', blueValue) << "      |";                                                          
    menu->addItem(ss.str(),
                  new MenuActionRGBManager(rgbLed, BLUE_CONF));
                
    string stateStr;                       
    if(state)       
        stateStr = "| Disable           |";
    else 
        stateStr = "| Enable            |";
        
    menu->addItem(stateStr, new MenuActionRGBManager(rgbLed, STATE_CONF));
                                            
    menu->addSeparator(' ');
    menu->addItem(" < Back", new MenuActionExecFunc(backAction));
    menu->display();
}

void MenuActionRGBLed::enterBtnAction(void) {
    /* Values labels */
    if(menu->getSelectedItem() < menu->size() - 3) {
        if(selectedItem == menu->getSelectedItem()) {
            string label = menu->getSelectedItemLabel();
            string newLabel = label.substr(0, 15) + "     |";
            menu->editLabel(selectedItem, newLabel); 
            selectedItem = -1;
            menu->display();
        }
        else {
            if(selectedItem == -1) { 
                selectedItem = menu->getSelectedItem();
                string label = menu->getSelectedItemLabel();
                
                string newLabel = label.substr(0, 15) + "<-   |";
                menu->editLabel(selectedItem, newLabel); 
                menu->display();
            }
        }
    }
    /* En/Disable label */
    else if(menu->getSelectedItem() == menu->size() - 3) {        
        if(!rgbLed->getState()) {
            menu->editLabel(menu->getSelectedItem(), "| Disable           |");
        }
        else {
            menu->editLabel(menu->getSelectedItem(), "| Enable            |");
        }
        menu->display();
        menu->performAction(0);
    }
    else {
        menu->performAction();
    }
}

void MenuActionRGBLed::upBtnAction(void){
    if(selectedItem == -1) {
        menu->selectPreviousItem();
        menu->display();
    }
    else {
        int32_t inc = 1;
        menu->performAction(&inc);
        string label = menu->getSelectedItemLabel();
        string newLabel = label.substr(0, 11) + 
                          alignInt(3, ' ', inc) + 
                          label.substr(14, label.size());
                          
        menu->editLabel(selectedItem, newLabel); 
        menu->display();
    }
}

void MenuActionRGBLed::downBtnAction(void){
    if(selectedItem == -1) {
        menu->selectNextItem();
        menu->display();
    }
    else {
        int32_t inc = -1;
        menu->performAction(&inc);
        string label = menu->getSelectedItemLabel();
        string newLabel = label.substr(0, 11) + 
                          alignInt(3, ' ', inc) + 
                          label.substr(14, label.size());
                          
        menu->editLabel(selectedItem, newLabel); 
        menu->display();
    }
}

MenuActionRGBLed* MenuActionRGBLed::instance;

void MenuActionRGBLed::backAction(void){
    if(instance != NULL) {
        instance->inMenu = false;
        delete instance->menu;
        
        instance->rgbLed->disable();
    }
}

string MenuActionRGBLed::alignInt(uint32_t alignWidth, char alignChar, 
                                  int32_t value) {
    
    
    stringstream ss;

    if(value == 0) {
        for(uint32_t i = 0; i < alignWidth - 1; ++i)
            ss << alignChar;
        
        ss << 0;
        return ss.str();
    }

    uint32_t size = floor(log10((double)value)) + 1;
    if(value < 0)
        ++size;
    
    if(size > alignWidth) {
        ss << value;
        return ss.str();
    }
    
    for(uint32_t i = alignWidth; i - size > 0; --i) {
        ss << alignChar;
    }

    ss << value;
    
    return ss.str();            
}