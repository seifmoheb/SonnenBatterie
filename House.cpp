#include "House.h"

House::House(double powerConsumed,double voltage, double frequency, double current)
    : powerConsumed(powerConsumed), voltage(voltage), frequency(frequency), current(current) {
    
}

double House::getPowerConsumed()  { return powerConsumed; }
double House::getVoltage()  { return voltage; }
double House::getFrequency()  { return frequency; }
double House::getCurrent()  { return current; }
