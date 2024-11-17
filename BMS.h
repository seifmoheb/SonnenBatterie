#ifndef AAA_HEADER
#define AAA_HEADER
class BMS {
private:
    double temperature;
    double voltage;
    double maxPower;
    double currentPower = 500;  // Current charge/discharge power in Watts

public:
    BMS(double temp = 0.0, double volt = 0.0, double maxPower = 0.0);
    double getTemperature();
    double getVoltage();
    double getMaxChargeDischargePower();
    double getCurrentPower();
    void setCurrentPower(double);
    double charge_dischargeBattery(double power);   // Charge/discharge the battery based on +/-
    
};
#endif
