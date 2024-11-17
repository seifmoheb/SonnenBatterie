#include "BMS.h"
#include <iostream>
using namespace std;
#define MAX_TEMPERATURE 50
#define MAX_VOLTAGE 250
#define MIN_VOLTAGE 5

BMS::BMS(double temp, double volt, double maxPower, double currentPower)
    : temperature(temp), voltage(volt), maxPower(maxPower), currentPower(currentPower) {}

double BMS::getTemperature() { return temperature; }
double BMS::getVoltage() { return voltage; }
double BMS::getMaxChargeDischargePower() { return maxPower; }
double BMS::getCurrentPower() { return currentPower; }


double BMS::charge_dischargeBattery(double power) {
    double remaining = 0.0;
    if (temperature > MAX_TEMPERATURE) {
        std::cout << "Temperature too high! Charging/discharging stopped." << std::endl;
        return power;
    }
    if (voltage < MIN_VOLTAGE || voltage > MAX_VOLTAGE) {
        std::cout << "Voltage out of bounds! Adjusting charge/discharge." << std::endl;
        return power;
    }
    if (power > 0) { // Charging
        double requiredCurrent = power / voltage; // Calculate required current
        double maxCurrent = maxPower / voltage;   // Max allowable current
        if (requiredCurrent > maxCurrent) {
            currentPower += maxPower;            // Limit to max power
            
        }
        else {
            currentPower += power;               // Add the actual power
        }
    }
    else { // Discharging
        double requiredCurrent = -power / voltage; // Calculate required current
        double maxCurrent = maxPower / voltage;    // Max allowable current
        if (requiredCurrent > maxCurrent) {
            currentPower += maxPower;             // Limit to max power
        }
        else {
            currentPower += power;                // Subtract the actual power
        }
    }

    // Ensure current power stays within allowable bounds
    if (currentPower > maxPower) {
        remaining = maxPower - currentPower;
        currentPower = maxPower;
    }
    if (currentPower < 0) {
        remaining = -currentPower;
        currentPower = 0;
    }
    return remaining;

}

