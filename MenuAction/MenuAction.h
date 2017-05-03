#ifndef __MENU_ACTION_H_
#define __MENU_ACTION_H_

class MenuAction {
    public:
        virtual void execute(void) = 0;
        virtual void execute(void *arg) = 0;
};

#endif /* __MENU_ACTION_H_ */