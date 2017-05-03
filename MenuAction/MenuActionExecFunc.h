#ifndef __MENU_ACTION_EXEC_FUNC_H_
#define __MENU_ACTION_EXEC_FUNC_H_

#include "MenuAction.h"

class MenuActionExecFunc : public MenuAction {
    public:
        MenuActionExecFunc(void (*func)(void));
        MenuActionExecFunc(void (*func)(void*));
        virtual void execute(void);
        virtual void execute(void *arg);
    
    private:
        void (*func)(void);
        void (*funcArg)(void*);
};

#endif /* __MENU_ACTION_EXEC_FUNC_H_ */
