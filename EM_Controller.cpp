
#include "EM_Controller.h"
#include <iostream>
using namespace std;
EM_Controller::EM_Controller(Photovoltaic& pv, Grid& grid, Storage& storage, House& house)
    : pv(pv), grid(grid), storage(storage), house(house) {
    storage.getInverter().setMaxPower(storage.getBatteryModules());
}
Grid& EM_Controller::getGrid() {
    return grid;
}
Photovoltaic& EM_Controller::getPhotovoltaic() { return pv; }
Storage& EM_Controller::getStorage() { return storage; }
House& EM_Controller::getHouse() { return house; }

void EM_Controller::adjustInverterToGrid() {
    if (storage.getInverter().getGridFrequency() != grid.getFrequency()) {
        std::cout << "Grid and inverter frequencies mismatch! Halting flow." << std::endl;
        return;
    }
    else if (storage.getInverter().getGridVoltage() != grid.getVoltage()) {
        std::cout << "Grid and inverter voltage mismatch. Adjusting..." << std::endl;
        storage.getInverter().setGridVoltage(grid.getVoltage());
    }
}
void EM_Controller::adjustInverterToBattery() {
    if (storage.getBatteryModules().at(0).getVoltage() != storage.getInverter().getBatteryVoltage()) {
        std::cout << "Voltage mismatch between inverter and storage. Adjusting inverter." << std::endl;
        storage.getInverter().setBatteryVoltage(storage.getInverter().getBatteryVoltage());
    }
}
void EM_Controller::manageEnergy() {
    storage.getInverter().setActualCapacity();
   
    double houseConsumption = house.getPowerConsumed();
    double pvProduction = pv.getPowerProduced();
    double powerDifference = pvProduction - houseConsumption;

    if (powerDifference > 0) {
        // Surplus energy: charge storage first, then sell remaining to grid

       if (powerDifference > storage.getInverter().getActualCapacity())
        {
           if (storage.getInverter().getActualCapacity() == 0)
           {
               grid.sellPower(powerDifference);
           }
           else
           {
               int remainingPower = powerDifference - storage.charge(powerDifference);
               if (remainingPower > 0) {
                   grid.sellPower(remainingPower);
               }
           }

        }
       else {
           storage.charge(powerDifference);
       }
    }
    else {
        // Deficit energy: discharge storage first, then buy from grid
        if (storage.getInverter().getPower() >= -powerDifference)
        {
            storage.discharge(-powerDifference);
        }
        else
        {
            int remainingDeficit = houseConsumption - pvProduction - storage.discharge(-powerDifference);
            if (remainingDeficit > 0) {
                grid.buyPower((double)remainingDeficit);
            }
        }
    }
    storage.getInverter().setPower(storage.getBatteryModules());
}
