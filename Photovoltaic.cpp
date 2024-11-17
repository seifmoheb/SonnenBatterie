#include "Photovoltaic.h"


Photovoltaic::Photovoltaic(double voltage, double current) :
powerProduced(powerProduced),voltage(voltage),current(current){
	
	powerProduced = voltage * current; // Power in Watts

}

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
