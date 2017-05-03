#ifndef __LUM_SENSOR_H_
#define __LUM_SENSOR_H_

#include "mbed.h"
#include "Sensor.h"

class LumSensor : public Sensor {
    public:
        LumSensor(PinName sensorIn, string name);
        virtual ~LumSensor(void);
        
        virtual void update(void);
        
        virtual string getName(void);
        virtual string getValue(void);
        virtual string getUnit(void);
        virtual string toString(void);
        
    private:
        AnalogIn *sensorIn;
        string name;
        string value;
        string unit;
};

#endif /* __LUM_SENSOR_H_ */