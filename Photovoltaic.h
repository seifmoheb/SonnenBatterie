class Photovoltaic{

private:
	double powerProduced;
	double voltage;
	double current;
public:
	Photovoltaic(double powerProduced, double voltage, double current);
	double getPowerProduced();
	double getVoltage();
	double getCurrent();

};
