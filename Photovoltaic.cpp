#include "Photovoltaic.h"


Photovoltaic::Photovoltaic(double powerProduced, double voltage, double current) :
powerProduced(powerProduced),voltage(voltage),current(current){}

double Photovoltaic::getPowerProduced()
{ 
	return powerProduced;
}
double Photovoltaic::getVoltage()
{
	return voltage;
}
double Photovoltaic::getCurrent()
{ 
	return current; 
}
