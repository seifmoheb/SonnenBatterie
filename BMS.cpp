#include "BMS.h"

BMS::BMS(double temp, double volt, double maxPower, double currentPower)
    : temperature(temp), voltage(volt), maxPower(maxPower), currentPower(currentPower) {}

double BMS::getTemperature() { return temperature; }
double BMS::getVoltage() { return voltage; }
double BMS::getMaxChargeDischargePower() { return maxPower; }
double BMS::getCurrentPower() { return currentPower; }
void BMS::charge_dischargeBattery(double power) {
    if (power > 0) {
        if(currentPower + power <= maxPower)
            currentPower += power;
        else {
            currentPower = maxPower;
        }
    }
    else {
        if (currentPower + power >= 0) {
            currentPower += power;
        }
        else
        {
            currentPower = 0;
        }
    }
}

