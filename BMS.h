#ifndef AAA_HEADER
#define AAA_HEADER
class BMS {
private:
    double temperature;
    double voltage;
    double maxChargeDischargePower;

public:
    BMS(double temp = 0.0, double volt = 0.0, double maxPower = 0.0);
    double getTemperature();
    double getVoltage();
    double getMaxChargeDischargePower();
};
#endif
