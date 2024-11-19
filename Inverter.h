#ifndef Inverter_HEADER
#define Inverter_HEADER
#include <vector>
#include "BMS.h"
class Inverter {
private:
    double maxPower;
    double batteryVoltage;
    double batteryCurrent;
    double power;
    double actualCapacity;
    double gridFrequency;
    double gridVoltage;

public:
    Inverter(double volt, double curr, double gridFreq, double gridVolt);

    void setPower(std::vector<BMS> modules);
    void setBatteryVoltage(double volt);
    void setGridVoltage(double volt);
    double getMaxPower();
    double getActualCapacity();
    void setActualCapacity();
    void setMaxPower(std::vector<BMS> modules);
    double getGridFrequency();
    double getGridVoltage();
    double getBatteryVoltage();
    double getBatteryCurrent();
    double getPower();
};
#endif
