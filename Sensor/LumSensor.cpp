#include "mbed.h"
#include "LumSensor.h"
#include <sstream>

LumSensor::LumSensor(PinName sensorIn, string name) {
    this->sensorIn = new AnalogIn(sensorIn);
    this->name = name;
    this->value = "Uninit";
    this->unit = "lm";
}
LumSensor::~LumSensor(void) {
    delete sensorIn;
}

void LumSensor::update(void) {
    stringstream newVal;
    uint16_t readValue = sensorIn->read_u16();
    
    newVal << readValue;
    
    value = newVal.str();
} 

string LumSensor::getName(void) {
    return name;
}

string LumSensor::getValue(void) {
    return value;
}

string LumSensor::getUnit(void) {
    return unit;    
}

string LumSensor::toString(void) {
    return name + ": " + value + unit;
}
