#ifndef PV_HEADER
#define PV_HEADER
class Photovoltaic{

private:
	double powerProduced;
	double voltage;
	double current;
public:
	Photovoltaic(double voltage, double current);
	double getPowerProduced();
	double getVoltage();
	double getCurrent();

};
#endif
