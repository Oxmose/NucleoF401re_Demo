#include "mbed.h"
#include "main.h"
#include "Menu.h"
#include "MenuActionIndividualLeds.h"
#include "MenuActionFlowPatterns.h"
#include "MenuActionExecFunc.h"
#include "MenuActionRGBLed.h"
#include "MenuActionSensors.h"
#include "LCDScreen.h"
#include "OLEDScreen.h"
#include "RGBLed.h"
#include "Sensor.h"
#include "LumSensor.h"

volatile bool shell_run = false;

/* Init buttons */
DigitalIn eventBtnUp(BTN_0_PIN);
DigitalIn eventBtnDown(BTN_1_PIN);
DigitalIn eventBtnEnter(BTN_2_PIN);

/* Init leds */
DigitalOut DLED_0(LED_0);
DigitalOut DLED_1(LED_1);
DigitalOut DLED_2(LED_2);

/* Init RGBLed */
RGBLed rgbLed(RGB_R, RGB_G, RGB_B);

/* Init sensors */
Sensor *lumSensor = new LumSensor(SENSOR_LUM, "Luminosity");
    
/* Init LCD screen */
LCDScreen *mainLCD = new OLEDScreen();

/* Init main menu */
Menu menu("Main menu\nPlease select:", mainLCD);

void setup() {
    pc.baud(115200);
    pc.format(8, SerialBase::None, 1);
}

void upBtn() {
    menu.selectPreviousItem();
    menu.display();
}

void downBtn() {
    menu.selectNextItem();
    menu.display();
}

void enterBtn() {
    menu.performAction();
    mainLCD->clear();
    if(shell_run)
        menu.display();
}

void exitFunction(void) {
    shell_run = false;
}

void os_run() {   
    /* Init leds vector */
    std::vector<DigitalOut*> leds;
    leds.push_back(&DLED_0);
    leds.push_back(&DLED_1);
    leds.push_back(&DLED_2);
    
    /* Init sensor vector */
    std::vector<Sensor*> sensors;    
    sensors.push_back(lumSensor);
    
    menu.addItem(" Individual leds    ", 
                 new MenuActionIndividualLeds(mainLCD, leds, &eventBtnEnter, 
                                              &eventBtnUp,&eventBtnDown));
                 
    menu.addItem(" Flow patterns      ",
                  new MenuActionFlowPatterns(mainLCD, leds, &eventBtnEnter, 
                                             &eventBtnUp,&eventBtnDown));
                                             
    menu.addItem(" RGB led management ", 
                 new MenuActionRGBLed(mainLCD, &rgbLed, &eventBtnEnter, 
                                              &eventBtnUp,&eventBtnDown));
                                             
    menu.addItem(" Sensors reading ", 
                 new MenuActionSensors(mainLCD, sensors, &eventBtnEnter, 
                                              &eventBtnUp,&eventBtnDown));
    
    menu.addSeparator(' ');
                           
    menu.addItem(" Exit               ",
                  new MenuActionExecFunc(exitFunction));
    
    menu.display();
    
    shell_run = true;
    while(shell_run) {
        if(eventBtnDown) {
            /* Unbound */
            while(eventBtnDown);
            downBtn();
        }
        else if(eventBtnUp) {
            /* Unbound */
            while(eventBtnUp);
            upBtn();
        }
        else if(eventBtnEnter) {
            /* Unbound */
            while(eventBtnEnter);
            enterBtn();
        }
        wait(0.1);
    }
}

int main() {    
    setup(); 
    os_run();
    
    OLEDScreen *oledLCD = (OLEDScreen*) mainLCD;
    
    oledLCD->clear();
    oledLCD->printHeader("        HALTED");
    oledLCD->display();
    
    for(int i = 0; i < 24; ++i) {
        oledLCD->drawBitmap(40, 16, LOGO_BITMAP, LOGO_WIDTH, LOGO_HEIGHT, WHITE);
        oledLCD->fillRect(40, 16 + i, 48, 48 - (i * 2), BLACK);
        oledLCD->display();
    }
    oledLCD->drawBitmap(40, 16, LOGO_BITMAP, LOGO_WIDTH, LOGO_HEIGHT, WHITE);
    oledLCD->display();
    
    delete lumSensor;
    delete oledLCD;
}



