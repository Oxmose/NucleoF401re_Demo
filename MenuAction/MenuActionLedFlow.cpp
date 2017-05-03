#include "MenuActionLedFlow.h"
#include <string>
#include <vector>

MenuActionLedFlow::MenuActionLedFlow(std::vector<DigitalOut*> &ledsIO, 
                                     FLOW_MODE_E flowMode,
                                     DigitalIn* canceler, 
                                     string message/* = "" */) {
    this->ledsIO = ledsIO;
    for(uint32_t i = 0; i < ledsIO.size(); ++i) {
        states.push_back(false);
    }
    this->flowMode = flowMode;
    this->message  = message;
    this->canceler = canceler;
}

void MenuActionLedFlow::execute(void) {   
    switch(flowMode) {
        case LED_FLOW_LINEAR:
            linearMode();
            break;
        case LED_FLOW_LINEAR_ONCE:
            linearOnceMode();
            break;
        case LED_FLOW_BLINK_EVEN:
            blinkEvenMode();
            break;
        case LED_FLOW_MORSE:
            morseMode();
            break;
        default:
            defaultMode();
    }
}

void MenuActionLedFlow::execute(void * arg) {
    execute();
}

void MenuActionLedFlow::defaultMode(void) {
    /* Unbound */
    while(canceler != NULL && *canceler == true);
    
    while(ledsIO.size() == 0) {
        wait(0.1);
        if(canceler != NULL && *canceler == true) {
            /* Unbound */
            while(canceler != NULL && *canceler == true);
            return;
        }
    }
    
    bool running = true;
    while(running) {
        for(uint32_t i = 0; i < ledsIO.size(); ++i) {
            states[i] = !states[i];
            *(ledsIO[i]) = states[i];
        }
        for(uint32_t i = 0; i < 5; ++i) {
            wait(0.1);
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
        }
    }
    for(uint32_t i = 0; i < ledsIO.size(); ++i) {
        states[i] = false;
        *(ledsIO[i]) = false;
    }
}

void MenuActionLedFlow::linearMode(void) {
    /* Unbound */
    while(canceler != NULL && *canceler == true);
    
    while(ledsIO.size() == 0) {
        wait(0.1);
        if(canceler != NULL && *canceler == true) {
            /* Unbound */
            while(canceler != NULL && *canceler == true);
            return;
        }
    }
    
    bool running = true;
    uint32_t ioSize = ledsIO.size();
    uint32_t lastOn = ioSize - 1;
    while(running) {
        lastOn = (lastOn + 1) % ioSize;
        states[lastOn] = !states[lastOn];
        *(ledsIO[lastOn]) = states[lastOn];
        
        for(uint32_t i = 0; i < 2; ++i) {
            wait(0.1);
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
        }
    }
    for(uint32_t i = 0; i < ledsIO.size(); ++i) {
        states[i] = false;
        *(ledsIO[i]) = false;
    }
}
void MenuActionLedFlow::linearOnceMode(void) {
    /* Unbound */
    while(canceler != NULL && *canceler == true);
    
    while(ledsIO.size() == 0) {
        wait(0.1);
        if(canceler != NULL && *canceler == true) {
            /* Unbound */
            while(canceler != NULL && *canceler == true);
            return;
        }
    }
    
    bool running = true;
    uint32_t ioSize = ledsIO.size();
    uint32_t lastOn = ioSize - 1;
    
    states[lastOn] = true;
    *(ledsIO[lastOn]) = true;
    
    while(running) {
        lastOn = (lastOn + 1) % ioSize;
        states[lastOn] = !states[lastOn];
        *(ledsIO[lastOn]) = states[lastOn];
        
        uint32_t prev = lastOn - 1;
        if(lastOn == 0)
            prev = ioSize - 1;
        
        states[prev] = !states[prev];
        *(ledsIO[prev]) = states[prev];
        
        for(uint32_t i = 0; i < 2; ++i) {
            wait(0.1);
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
        }
    }
    for(uint32_t i = 0; i < ledsIO.size(); ++i) {
        states[i] = false;
        *(ledsIO[i]) = false;
    }
}

void MenuActionLedFlow::blinkEvenMode(void) {
    /* Unbound */
    while(canceler != NULL && *canceler == true);
    
    while(ledsIO.size() == 0) {
        wait(0.1);
        if(canceler != NULL && *canceler == true) {
            /* Unbound */
            while(canceler != NULL && *canceler == true);
            return;
        }
    }
    
    bool running = true;
    uint32_t even = 0;
    for(uint32_t i = even; i < ledsIO.size(); i += 2) {
        states[i] = !states[i];
        *(ledsIO[i]) = states[i];
    }
    while(running) {
        for(uint32_t i = even; i < ledsIO.size(); i += 2) {
            states[i] = !states[i];
            *(ledsIO[i]) = states[i];
        }
        for(uint32_t i = (even + 1) % 2; i < ledsIO.size(); i += 2) {
            states[i] = !states[i];
            *(ledsIO[i]) = states[i];
        }
        for(uint32_t i = 0; i < 5; ++i) {
            wait(0.1);
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
        }
        even = (even + 1) % 2;
    }
    for(uint32_t i = 0; i < ledsIO.size(); ++i) {
        states[i] = false;
        *(ledsIO[i]) = false;
    }
    
}
void MenuActionLedFlow::morseMode(void) {
    /* Unbound */
    while(canceler != NULL && *canceler == true);
    
    while(ledsIO.size() == 0) {
        wait(0.1);
        if(canceler != NULL && *canceler == true) {
            /* Unbound */
            while(canceler != NULL && *canceler == true);
            return;
        }
    }
    
    bool running = true;
    while(running) {
        
        /* S */
        for(uint32_t s = 0; s < 3; ++s) {
            for(uint32_t i = 0; i < ledsIO.size(); ++i) {
                states[i] = !states[i];
                *(ledsIO[i]) = states[i];
            }
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
            wait(0.3);
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
            for(uint32_t i = 0; i < ledsIO.size(); ++i) {
                states[i] = !states[i];
                *(ledsIO[i]) = states[i];
            }
            wait(0.1);
        }
        if(!running)
            break;
        wait(0.1);
        /* O */
        for(uint32_t o = 0; o < 3; ++o) {
            for(uint32_t i = 0; i < ledsIO.size(); ++i) {
                states[i] = !states[i];
                *(ledsIO[i]) = states[i];
            }
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
            wait(0.7);
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
            for(uint32_t i = 0; i < ledsIO.size(); ++i) {
                states[i] = !states[i];
                *(ledsIO[i]) = states[i];
            }
            wait(0.1);
        }
        if(!running)
            break;
        wait(0.1);
        /* S */
        for(uint32_t s = 0; s < 3; ++s) {
            for(uint32_t i = 0; i < ledsIO.size(); ++i) {
                states[i] = !states[i];
                *(ledsIO[i]) = states[i];
            }
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
            wait(0.3);
            if(canceler != NULL && *canceler == true) {
                /* Unbound */
                while(canceler != NULL && *canceler == true);
                running = false;
                break;
            }
            for(uint32_t i = 0; i < ledsIO.size(); ++i) {
                states[i] = !states[i];
                *(ledsIO[i]) = states[i];
            }
            wait(0.1);
        }
        
        for(uint32_t i = 0; i < ledsIO.size(); ++i) {
            states[i] = false;
            *(ledsIO[i]) = false;
        }
        
        if(!running)
            break;
            
        wait(0.5);
        
        if(canceler != NULL && *canceler == true) {
            /* Unbound */
            while(canceler != NULL && *canceler == true);
            running = false;
        }
    }
    
    for(uint32_t i = 0; i < ledsIO.size(); ++i) {
        states[i] = false;
        *(ledsIO[i]) = false;
    }
}