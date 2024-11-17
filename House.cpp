#include "House.h"

House::House(double voltage, double frequency, double current)
    : voltage(voltage), frequency(frequency), current(current) {
    
    powerConsumed = voltage * current;
}

double House::getPowerConsumed()  { return powerConsumed; }
double House::getVoltage()  { return voltage; }
double House::getFrequency()  { return frequency; }
double House::getCurrent()  { return current; }
