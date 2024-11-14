#include "Photovoltaic.h"
#include "Storage.h"
#include "Grid.h"
#include "BMS.h"
#include "House.h"
class EM_Controller
{
private:
	Photovoltaic pv;
	Grid grid;
	Storage storage;
	House house;
public:
	EM_Controller(Photovoltaic pv, Grid grid, Storage storage, House house);


};

