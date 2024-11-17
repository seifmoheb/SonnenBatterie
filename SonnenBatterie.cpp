
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
    // Initialize components for Scenario 1: Surplus energy from PV
    Photovoltaic pv(100,10); // PV Panel Current and Voltage to compute Power
    BMS battery_1(25, 230, 500);
    BMS battery_2(25, 230,500);
    BMS battery_3(25, 230,500);
    Inverter inverter(1500, 230, 5, 50, 230); // Inverter
    Grid grid(0, 0, 230, 50); // Grid
    House house(230, 50, 2.6); // House Current and Voltage to compute Power
    std::vector<BMS> batteryModules = { battery_1, battery_2, battery_3 };
    Storage storage(inverter, batteryModules);
    EM_Controller controller(pv, grid, storage, house);

    // Manage energy
    controller.manageEnergy();

    // Output results
    std::cout << "Battery Modules Power:" << std::endl;
    for (size_t i = 0; i < controller.getStorage().getBatteryModules().size(); i++) {
        std::cout << "Battery " << (i + 1) << ": " << controller.getStorage().getBatteryModules().at(i).getCurrentPower() << " W" << std::endl;
        std::cout << "Battery Voltage " << (i + 1) << ": " << controller.getStorage().getBatteryModules().at(i).getVoltage() << " W" << std::endl;

    }
    std::cout << "Grid Power Sold: " << controller.getGrid().getPowerSold() << " W" << std::endl;
    std::cout << "Grid Power Bought: " << controller.getGrid().getPowerBought() << " W" << std::endl;

    return 0;
}
