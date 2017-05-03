#ifndef __SENSOR_H_
#define __SENSOR_H_

#include "mbed.h"
#include <string>

class Sensor {
    public:        
        virtual void update(void) = 0;
        
        virtual string getName(void)  = 0;
        virtual string getValue(void) = 0;
        virtual string getUnit(void)  = 0;
        virtual string toString(void) = 0;
};

#endif /* __SENSOR_H_ */