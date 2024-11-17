#include "Storage.h"
#include <iostream>
#include <cmath> // For abs
using namespace std;

Storage::Storage(Inverter inv, std::vector<BMS> modules)
    : inverter(inv), batteryModules(modules), powerCommand(0.0) {
    
}

void Storage::charge(double power) {
    if (power < 0) return; // Invalid power command

    double remainingPower = power;
    double totalAvailableCapacity = 0.0;

    // Calculate total available capacity across all batteries
    for (auto& battery : batteryModules) {
        totalAvailableCapacity += battery.getMaxChargeDischargePower() - battery.getCurrentPower();
    }
    double remainingReturned = 0.0;
    // Distribute power proportionally to each battery
    for (auto& battery : batteryModules) {
        if (remainingPower <= 0) break;

        double availableCapacity = battery.getMaxChargeDischargePower() - battery.getCurrentPower();
        if (availableCapacity <= 0) continue;

        double proportionalPower = (availableCapacity / totalAvailableCapacity) * power;

        if (proportionalPower > remainingPower) proportionalPower = remainingPower;
        remainingReturned += battery.charge_dischargeBattery(proportionalPower);

        remainingPower -= proportionalPower;
    }

    // Update the inverter with the actual power charged
    inverter.setPower(power - remainingPower + remainingReturned);
}

void Storage::discharge(double power) {
    if (power < 0) return; // Invalid power command
    double remainingReturned = 0.0;

    double remainingPower = power;
    double totalAvailableEnergy = 0.0;

    // Calculate total available energy across all batteries
    for (auto& battery : batteryModules) {
        totalAvailableEnergy += battery.getCurrentPower();
    }

    // Distribute power proportionally to each battery
    for (auto& battery : batteryModules) {
        if (remainingPower <= 0) break;

        double availableEnergy = battery.getCurrentPower();
        if (availableEnergy <= 0) continue;

        double proportionalPower = (availableEnergy / totalAvailableEnergy) * power;

        if (proportionalPower > remainingPower) proportionalPower = remainingPower;
        remainingReturned += battery.charge_dischargeBattery(-proportionalPower);

        remainingPower -= proportionalPower;
    }

    // Update the inverter with the actual power discharged
    inverter.setPower(power -  remainingReturned);

    
}

Inverter Storage::getInverter() { return inverter; }
std::vector<BMS>& Storage::getBatteryModules() { return batteryModules; }
