#include "MenuActionExecFunc.h"

MenuActionExecFunc::MenuActionExecFunc(void (*func)(void)) {
    this->func = func;
}

MenuActionExecFunc::MenuActionExecFunc(void (*funcAerg)(void*)) {
    this->funcArg = funcArg;
}

void MenuActionExecFunc::execute(void) {
    func();
}

void MenuActionExecFunc::execute(void *arg) {
    funcArg(arg);
}