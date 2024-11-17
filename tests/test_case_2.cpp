
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
    // Initialize components for Scenario 2: Deficit energy with grid support
    Photovoltaic pv(300, 230, 1.3); // PV Panel
    BMS battery_1(25, 230, 500);
    BMS battery_2(25, 230, 500);
    Inverter inverter(1000, 230, 4, 50, 230); // Inverter
    Grid grid(0, 0, 230, 50); // Grid
    House house(800, 230, 50, 3.5); // House
    std::vector<BMS> batteryModules = { battery_1, battery_2 };
    Storage storage(inverter, batteryModules);
    EM_Controller controller(pv, grid, storage, house);

    // Manage energy
    controller.manageEnergy();

    // Output results
    std::cout << "Battery Modules Power:" << std::endl;
    for (size_t i = 0; i < batteryModules.size(); i++) {
        std::cout << "Battery " << (i + 1) << ": " << batteryModules[i].getCurrentPower() << " W" << std::endl;
    }
    std::cout << "Grid Power Sold: " << grid.getPowerSold() << " W" << std::endl;

    return 0;
}
