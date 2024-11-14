#include "EM_Controller.h"

EM_Controller::EM_Controller(Photovoltaic pv, Grid grid, Storage storage, House house)
	:pv(pv.getPowerProduced(), pv.getVoltage(), pv.getCurrent())
	, grid(grid.getPowerSold(),grid.getPowerBought(),grid.getVoltage(),grid.getFrequency())
	, storage(storage.getInverter(),storage.getBatteryModules())
	, house(house.getPowerConsumed(),house.getVoltage(),house.getFrequency(),house.getCurrent())
{
	if (pv.getPowerProduced() > house.getPowerConsumed()) {
		double inverterMaxPower = storage.getInverter().getMaxPower();
		double surplus = pv.getPowerProduced() - house.getPowerConsumed();
		
		if (inverterMaxPower > surplus) {
			storage.charge(surplus);
		}
		
		
	}

}

