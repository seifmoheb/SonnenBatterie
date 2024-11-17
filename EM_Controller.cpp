
#include "EM_Controller.h"
#include <iostream>
using namespace std;
EM_Controller::EM_Controller(Photovoltaic& pv, Grid& grid, Storage& storage, House& house)
    : pv(pv), grid(grid), storage(storage), house(house) {}
Grid& EM_Controller::getGrid() {
    return grid;
}
Photovoltaic& EM_Controller::getPhotovoltaic() { return pv; }
Storage& EM_Controller::getStorage() { return storage; }
House& EM_Controller::getHouse() { return house; }
void EM_Controller::manageEnergy() {

    if (storage.getInverter().getGridFrequency() != grid.getFrequency()) {
        std::cout << "Grid and inverter frequencies mismatch! Halting flow." << std::endl;
        return;
    }
    if (storage.getBatteryModules().at(0).getVoltage() != storage.getInverter().getBatteryVoltage()) {
            std::cout << "Voltage mismatch between inverter and storage. Adjusting inverter." << std::endl;
            storage.getInverter().setBatteryVoltage(storage.getInverter().getBatteryVoltage());
    }
    
    double houseConsumption = house.getPowerConsumed();
    double pvProduction = pv.getPowerProduced();
    double powerDifference = pvProduction - houseConsumption;

    if (powerDifference > 0) {
        // Surplus energy: charge storage first, then sell remaining to grid
        storage.charge(powerDifference);
        double remainingPower = powerDifference - storage.getInverter().getPower();
        if (remainingPower > 0) {
            if (storage.getInverter().getBatteryVoltage() != grid.getVoltage()) {
                std::cout << "Grid and inverter voltage mismatch. Adjusting..." << std::endl;
                storage.getInverter().setBatteryVoltage(grid.getVoltage());
            }
            grid.sellPower(remainingPower);
        }
    }
    else {
        // Deficit energy: discharge storage first, then buy from grid
        storage.discharge(-powerDifference);
        
        double remainingDeficit = houseConsumption - pvProduction - storage.getInverter().getPower();
        if (remainingDeficit > 0) {
            if (storage.getInverter().getBatteryVoltage() != grid.getVoltage()) {
                std::cout << "Grid and inverter voltage mismatch. Adjusting..." << std::endl;
                storage.getInverter().setBatteryVoltage(grid.getVoltage());
            }
            grid.buyPower(remainingDeficit);
        }
    }
}
