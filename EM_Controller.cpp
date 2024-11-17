
#include "EM_Controller.h"
#include <iostream>
using namespace std;
EM_Controller::EM_Controller(Photovoltaic& pv, Grid& grid, Storage& storage, House& house)
    : pv(pv), grid(grid), storage(storage), house(house) {}
Grid& EM_Controller::getGrid() {
    return grid;
}
void EM_Controller::manageEnergy() {
    double houseConsumption = house.getPowerConsumed();
    double pvProduction = pv.getPowerProduced();
    double powerDifference = pvProduction - houseConsumption;

    if (powerDifference > 0) {
        // Surplus energy: charge storage first, then sell remaining to grid
        storage.charge(powerDifference);
        double remainingPower = powerDifference - storage.getInverter().getPower();
        if (remainingPower > 0) {
            grid.sellPower(remainingPower);
        }
    }
    else {
        // Deficit energy: discharge storage first, then buy from grid
        storage.discharge(-powerDifference);
        
        double remainingDeficit = houseConsumption - pvProduction - storage.getInverter().getPower();
        if (remainingDeficit > 0) {
            grid.buyPower(remainingDeficit);
        }
    }
}
