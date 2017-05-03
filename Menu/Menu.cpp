#include "mbed.h"
#include "MenuAction.h"
#include "LCDScreen.h"
#include "Menu.h"
#include <string>

Menu::Menu(string title, LCDScreen *screen) {
    this->title = title;
    this->ssize = 0;
    
    this->selectedIndex  = 0;
    this->selectedItem   = NULL;
    this->items          = NULL;
    
    this->screen = screen;
    this->lastDisplayedItem = screen->getCharLines();
}

Menu::~Menu(void) {
    while(ssize != 0) {
        deleteItem(0);
    }
}
        
void Menu::performAction(void) {
    if(selectedItem->action != NULL)
        selectedItem->action->execute();
}

void Menu::performAction(void *arg) {
    if(selectedItem->action != NULL)
        selectedItem->action->execute(arg);
}

void Menu::selectItem(uint32_t index) {
    /* Select item modulo the size */
    selectedIndex = index % ssize;
    
    MenuItem *cursor = items;
    uint32_t i;
    for(i = 0; i < selectedIndex; ++i) {
        selectedItem = cursor->next;
    }    
}

void Menu::selectNextItem(void) {
    if(ssize > 0) {
        if(selectedItem->next->isSeparator) {
            selectedItem = selectedItem->next;
            selectedIndex = (selectedIndex + 1) % ssize;
        }
        selectedItem = selectedItem->next;
        selectedIndex = (selectedIndex + 1) % ssize;
    }
}

void Menu::selectPreviousItem(void) {
    if(ssize > 0) {
        if(selectedItem->previous->isSeparator) {
            selectedItem = selectedItem->previous;
            selectedIndex = 
                        (selectedIndex > 0) ? (selectedIndex - 1) : (ssize - 1);
        }
        
        selectedItem = selectedItem->previous;
        selectedIndex = (selectedIndex > 0) ? (selectedIndex - 1) : (ssize - 1);
    }
}
        
uint32_t Menu::getSelectedItem(void) {
    return selectedIndex;
}

string Menu::getSelectedItemLabel(void) {
    return selectedItem->label;
}

int32_t Menu::addItem(string label, MenuAction *action, 
                      bool isSeparator/* = false */) {
   
    if(items == NULL && isSeparator)
        return -1;
   
    /* Add first item */
    if(items == NULL) {
        items = new MenuItem;
        items->previous = items;
        items->next     = items;
        items->label    = label;
        items->action   = action;
        
        items->isSeparator = false;
        
        ssize = 1;
        selectedItem = items;
        selectedIndex = 0;
        return 0;
    }
    
    /* Add a new item */
    MenuItem *newItem = new MenuItem;
    newItem->isSeparator = isSeparator;
    newItem->action = isSeparator ? NULL : action;
    newItem->label = label;
    newItem->next = items;
    newItem->previous = items->previous;
    items->previous->next = newItem;
    items->previous = newItem;
    ++ssize;
    return ssize - 1;
}

int32_t Menu::addSeparator(char sepChar) {
    string str("");
    for(uint32_t i = 0; i < screen->getCharLineWidth(); ++i)
        str += sepChar;
    return addItem(str, NULL, true);
}

void Menu::editLabel(uint32_t index, string newLabel) {
    if(index >= ssize)
        return;
    
    MenuItem *cursor = items;
    while(index--) {
        cursor = cursor->next;
    }
    if(!cursor->isSeparator)
        cursor->label = newLabel;
}

void Menu::deleteItem(uint32_t index) {
    if(ssize == 0)
        return;
        
    selectedItem = items;
    selectedIndex = 0;
    
    /* Index is index modulo the size */
    index %= ssize;
    
    /* Get the item to delete */
    MenuItem *toDelete = items;
    uint32_t i;
    for(i = 0; i < index; ++i)
        toDelete = toDelete->next;

    /* If this is the last element */    
    if(ssize == 1) {
        if(toDelete->action != NULL)
            delete toDelete->action;
            
        delete toDelete;
        items = NULL;
        selectedItem  = NULL;
        selectedIndex = NULL;
        ssize = 0;
        return;
    }
    
    toDelete->previous->next = toDelete->next;
    toDelete->next->previous = toDelete->previous;
    --ssize;
}

uint32_t Menu::size(void) {
    return ssize;
}
       
void Menu::display(void) {
    MenuItem *cursor = items;
    
    uint32_t maxSize = screen->getCharLines();
    if(maxSize > ssize)
        maxSize = ssize;
        screen->display();
    
    int shift = 0;
    
    this->lastDisplayedItem = screen->getCharLines();
    
    while(lastDisplayedItem - 1 < selectedIndex) {
        cursor = cursor->next;
        lastDisplayedItem++;
        ++shift;
    }
    
    uint32_t i;
    for(i = 0; i < maxSize; ++i) { 
        if(selectedIndex == i + shift)
            screen->setHighlight(true);
            
        screen->printf(cursor->label);
        
        screen->setHighlight(false);
        if(screen->getTextCursorX() -  screen->charWidth() < 
           screen->getCharLineWidth() * screen->charWidth())
            screen->printf("\n");
        
        cursor = cursor->next;
    }
    
    screen->printHeader(title);
    screen->display();
}
        
void Menu::scrollUp(void) {
    
}
void Menu::scrollDown(void) {

}