
#include "Storage.h"
#include <iostream>
using namespace std;
Storage::Storage(Inverter inv, std::vector<BMS> modules)
    : inverter(inv), batteryModules(modules), powerCommand(0.0) {}

void Storage::charge(double power) {
    if (power < 0) return; // Invalid power command
    powerCommand = 0.0;
    for (auto& battery : batteryModules) {
        double totalCapacity = 0.0;
        totalCapacity += battery.getMaxChargeDischargePower() - battery.getCurrentPower();
         if (totalCapacity == 0) {
            continue;
        }
        else if (power > totalCapacity) {
             
             battery.charge_dischargeBattery(totalCapacity);
             powerCommand += totalCapacity; // Prevent overcharging
        }
        else if (power == totalCapacity) {
             
             battery.charge_dischargeBattery(power);
             powerCommand += power;
         }
        else if (power < totalCapacity) {
             battery.charge_dischargeBattery(power);
             powerCommand += power;
             break;
         } 
    }
    inverter.setPower(powerCommand);
    
}

void Storage::discharge(double power) {
    if (power < 0) return; // Invalid power command
    powerCommand = power;
    for (auto& battery : batteryModules) {
        double totalDischargeCapacity = 0.0;
        //totalDischargeCapacity = battery.getMaxChargeDischargePower() - battery.getCurrentPower();
        totalDischargeCapacity += battery.getCurrentPower();
        if (totalDischargeCapacity == 0) {   
           
            break;
        }
        if (totalDischargeCapacity == powerCommand) {
            battery.charge_dischargeBattery(-powerCommand);
            powerCommand = 0.0;
            break;
        }
        else if (totalDischargeCapacity > 0 && totalDischargeCapacity > powerCommand) {
            battery.charge_dischargeBattery(-powerCommand);
            powerCommand = 0.0;
            break;
        }
        else if (totalDischargeCapacity > 0 && totalDischargeCapacity < powerCommand) {
            
            powerCommand -= totalDischargeCapacity;
            inverter.setPower(totalDischargeCapacity);
            battery.charge_dischargeBattery(-totalDischargeCapacity);
        }   
    }
    inverter.setPower(power-powerCommand);
   
}

Inverter Storage::getInverter() { return inverter; }
std::vector<BMS>& Storage::getBatteryModules() { return batteryModules; }
