#include "Inverter.h"

Inverter::Inverter(double maxP, double volt, double curr, double gridFreq, double gridVolt)
    : maxPower(maxP), batteryVoltage(volt), batteryCurrent(curr),
    gridFrequency(gridFreq), gridVoltage(gridVolt), power(0) {}

void Inverter::setPower(double p) { power = p; }
double Inverter::getMaxPower()  { return maxPower; }
double Inverter::getBatteryVoltage()  { return batteryVoltage; }
double Inverter::getBatteryCurrent()  { return batteryCurrent; }
double Inverter::getPower()  { return power; }
