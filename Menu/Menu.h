#ifndef __MENU_H_
#define __MENU_H_

#include "mbed.h"
#include "MenuAction.h"
#include "LCDScreen.h"
#include <string>

typedef struct MenuItem {
    MenuItem   *previous;
    MenuItem   *next;
    string     label;
    MenuAction *action;
    bool       isSeparator;
} MenuItem;

class Menu {
    public:
        /* Constructor / Destructor */
        Menu(string title, LCDScreen *screen);
        ~Menu(void);
        
        void performAction(void);
        void performAction(void *arg);

        void selectItem(uint32_t index);
        void selectNextItem(void);
        void selectPreviousItem(void);
        
        uint32_t getSelectedItem(void);
        string getSelectedItemLabel(void);
        
        int32_t addItem(string label, MenuAction *action, 
                        bool isSeparator = false);
        int32_t addSeparator(char sepChar);
        void editLabel(uint32_t index, string newLabel);
        void deleteItem(uint32_t index);
        
        uint32_t size(void);
        
        void display(void);
        
        void scrollUp(void);
        void scrollDown(void);
    private:
        LCDScreen *screen;
        uint32_t lastDisplayedItem;
        
        string   title;
        uint32_t ssize;
        uint32_t selectedIndex;
        MenuItem *selectedItem;
        MenuItem *items;
};

#endif /* __MENU_H_ */