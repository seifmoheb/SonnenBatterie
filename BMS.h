#ifndef BMS_HEADER
#define BMS_HEADER
class BMS {
private:
    double temperature;
    double voltage;
    double maxPower;
    double currentPower;  // Current charge/discharge power in Watts

public:
    BMS(double temp = 0.0, double volt = 0.0, double maxPower = 0.0, double currentPower = 0.0);
    double getTemperature();
    double getVoltage();
    double getMaxChargeDischargePower();
    double getCurrentPower();
    double charge_dischargeBattery(double power);   // Charge/discharge the battery based on +/-
    
};
#endif
