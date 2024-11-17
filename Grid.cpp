
#include "Grid.h"

Grid::Grid(double sold, double bought, double voltage, double frequency)
    : powerSold(sold), powerBought(bought), voltage(voltage), frequency(frequency) {
}

double Grid::getPowerSold() { return powerSold; }
double Grid::getPowerBought() { return powerBought; }
double Grid::getVoltage() { return voltage; }
double Grid::getFrequency() { return frequency; }

void Grid::sellPower(double power) {
    powerSold += power;
}

void Grid::buyPower(double power) {
    powerBought += power;
}
