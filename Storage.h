
#ifndef AAAB_HEADER
#define AAAB_HEADER

#include "Inverter.h"
#include "BMS.h"
#include <vector>

class Storage {
private:
    double powerCommand;
    Inverter inverter;
    std::vector<BMS> batteryModules;

public:
    Storage(Inverter inv, std::vector<BMS> modules);

    void charge(double power);
    void discharge(double power);
    
    Inverter getInverter();
    std::vector<BMS>& getBatteryModules();
};

#endif
