#include "MenuActionLed.h"

MenuActionLed::MenuActionLed(DigitalOut *ledIO) {
    this->ledIO = ledIO;
    state = false;
}

void MenuActionLed::execute(void) {
    state = !state;
    *ledIO = state;
}

void MenuActionLed::execute(void * arg) {
    execute();
}