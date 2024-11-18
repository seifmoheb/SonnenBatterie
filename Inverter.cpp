#include "Inverter.h"
#include "BMS.h"
#include <vector>
Inverter::Inverter(double volt, double curr, double gridFreq, double gridVolt)
    : batteryVoltage(volt), batteryCurrent(curr),
    gridFrequency(gridFreq), gridVoltage(gridVolt), power(0) {
}
void Inverter::setMaxPower(std::vector<BMS> modules) {
    maxPower = modules.size() * modules[0].getMaxChargeDischargePower();
}
void Inverter::setActualCapacity()
{
    actualCapacity = maxPower - power;
}
double Inverter::getActualCapacity()
{
    return actualCapacity;
}
double Inverter::getGridVoltage() {
    return gridVoltage;
}
void Inverter::setPower(std::vector<BMS> modules)
{
    power = 0;
    for (auto& battery : modules) 
    {
        power += battery.getCurrentPower();
    }
    setActualCapacity();
}

void Inverter::setBatteryVoltage(double volt) { batteryVoltage = volt; }
void Inverter::setGridVoltage(double volt) { gridVoltage = volt; }
double Inverter::getGridFrequency() { return gridFrequency; }
double Inverter::getMaxPower()  { return maxPower; }
double Inverter::getBatteryVoltage()  { return batteryVoltage; }
double Inverter::getBatteryCurrent()  { return batteryCurrent; }
double Inverter::getPower()  { return power; }
