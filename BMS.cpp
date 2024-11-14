#include "BMS.h"

#include "BMS.h"

BMS::BMS(double temp, double volt, double maxPower)
    : temperature(temp), voltage(volt), maxChargeDischargePower(maxPower) {}

double BMS::getTemperature() { return temperature; }
double BMS::getVoltage() { return voltage; }
double BMS::getMaxChargeDischargePower() { return maxChargeDischargePower; }
