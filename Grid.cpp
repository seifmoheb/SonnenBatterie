#include "Grid.h"

Grid::Grid(double sold = 0.0, double bought = 0.0, double voltage = 0.0, double frequency = 0.0)
    : powerSold(sold), powerBought(bought), voltage(voltage), frequency(frequency) {}

double Grid::getPowerSold()  { return powerSold; }
double Grid::getPowerBought()  { return powerBought; }
double Grid::getVoltage()  { return voltage; }
double Grid::getFrequency()  { return frequency; }

