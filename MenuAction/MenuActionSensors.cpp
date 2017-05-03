#include "mbed.h"
#include "MenuActionSensors.h"
#include "MenuActionExecFunc.h"
#include "Sensor.h"
#include "LCDScreen.h"
#include "Menu.h"
#include <vector>
#include <sstream>

MenuActionSensors::MenuActionSensors(LCDScreen *mainLCD,
                  std::vector<Sensor*> &sensors, 
                  DigitalIn *enterBtn, 
                  DigitalIn *upBtn, 
                  DigitalIn *downBtn) {
    this->mainLCD = mainLCD;
    this->sensors = sensors;
    
    this->enterBtn = enterBtn;
    this->upBtn    = upBtn;
    this->downBtn  = downBtn;
    
    this->instance = this;
}

MenuActionSensors::~MenuActionSensors(void) {
    if(this->menu)
        delete this->menu;
}

void MenuActionSensors::execute(void) {
    float updateRate = 1;
    stringstream ss;
    ss << "Sensors display\nUpdating every " << updateRate << "s";
    this->menu = new Menu(ss.str(), mainLCD);
    inMenu = true;
    setUI();
    
    float refreshBtn = 0.1;
    uint32_t initCountDown = updateRate / refreshBtn;
    uint32_t countDown = initCountDown;
    
    while(inMenu) {
        --countDown;
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
        wait(refreshBtn);
        if(countDown == 0) {
            countDown = initCountDown;
            for(uint32_t i = 0; i < sensors.size(); ++i) {
                sensors[i]->update();
                string value = sensors[i]->toString();
                while(value.size() < 21) {
                    value = value + " ";
                }
                menu->editLabel(i, value);
            }
            menu->display();
        }
    }
}
void MenuActionSensors::execute(void *arg) {
    execute();
}

void MenuActionSensors::setUI(void) {
    mainLCD->clear();
    
    for(uint32_t i = 0; i < sensors.size(); ++i) {
        menu->addItem(sensors[i]->toString(), NULL);
    }

    menu->addSeparator(' ');
    menu->addItem(" < Back", new MenuActionExecFunc(backAction));
    menu->display();
}

void MenuActionSensors::enterBtnAction(void) {
    menu->performAction();
    if(inMenu)
        menu->display();
}
void MenuActionSensors::upBtnAction(void) {
    menu->selectPreviousItem();
    menu->display();
}
void MenuActionSensors::downBtnAction(void) {
    menu->selectNextItem();
    menu->display();
}

MenuActionSensors *MenuActionSensors::instance;

void MenuActionSensors::backAction(void) {
    if(instance) {
        instance->inMenu = false;
        delete instance->menu;
    }
}