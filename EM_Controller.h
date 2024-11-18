
#ifndef AAB_HEADER
#define AAB_HEADER

#include "Photovoltaic.h"
#include "Storage.h"
#include "Grid.h"
#include "BMS.h"
#include "House.h"

class EM_Controller
{
private:
    Photovoltaic& pv;
    Grid& grid;
    Storage& storage;
    House& house;

public:
    EM_Controller(Photovoltaic& pv, Grid& grid, Storage& storage, House& house);
    void manageEnergy();
    Grid& getGrid();
    Photovoltaic& getPhotovoltaic();
    Storage& getStorage();
    House& getHouse();
    void adjustInverterToGrid();
    void adjustInverterToBattery();


};

#endif
