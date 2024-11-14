#include "Storage.h"


 Storage::Storage(Inverter inv, std::vector<BMS> modules)
     : inverter(inv), batteryModules(modules), powerCommand(0.0) {}

 void Storage::charge(double power) {
     powerCommand = power;
     inverter.setPower(power);
 }

 void Storage::discharge(double power) {
     powerCommand = -power;
     inverter.setPower(-power);
 }
 Inverter Storage::getInverter() { return inverter; }
 std::vector<BMS>& Storage::getBatteryModules() { return batteryModules; }

