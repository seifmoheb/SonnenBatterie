
#include <iostream>
#include <vector>
#include "Photovoltaic.h"
#include "Grid.h"
#include "Storage.h"
#include "BMS.h"
#include "Inverter.h"
#include "House.h"
#include "EM_Controller.h"

using namespace std;

int main() {
    // Initialize components for Scenario 2: Surplus energy from PV, charge all batteries, then sell to grid
    Photovoltaic pv(1000.6, 1.5); // PV Panel
    BMS battery_1(25, 230, 500,100);
    BMS battery_2(25, 230, 500,100);
    BMS battery_3(25, 230, 500,100);
    Inverter inverter(5000, 230, 10, 50, 230); // Inverter
    Grid grid(0, 0, 230, 50); // Grid
    House house(20, 230, 50, 2.6); // House
    std::vector<BMS> batteryModules = { battery_1, battery_2, battery_3 };
    Storage storage(inverter, batteryModules);
    EM_Controller controller(pv, grid, storage, house);

    // Manage energy
    controller.manageEnergy();

    // Output results
    std::cout << "Battery Modules Power:" << std::endl;
    for (size_t i = 0; i < storage.getBatteryModules().size(); i++) {
        std::cout << "Battery " << (i + 1) << ": " << storage.getBatteryModules().at(i).getCurrentPower() << " W" << std::endl;
    }
    std::cout << "Grid Power Sold: " << grid.getPowerSold() << " W" << std::endl;
    std::cout << "Grid Power Bought: " << grid.getPowerBought() << " W" << std::endl;

    return 0;
}
