SonnenBatterie Energy Management System Simulation
This project simulates the energy management system (EMS) of a SonnenBatterie (SB), a market-leading battery storage system. The EMS handles power flow between various components, including photovoltaic (PV) panels, batteries, the inverter, the grid, and the house, optimizing energy usage based on production and consumption scenarios.

Features
Photovoltaic Panel Simulation: Calculates energy generation using voltage and current inputs.
Battery Management System (BMS): Balances charging and discharging of multiple batteries while respecting temperature, voltage, and power constraints.
Inverter Control: Manages power flow to and from the batteries, ensuring optimal energy transfer and grid interaction.
Grid Interaction: Simulates buying and selling power to the grid, based on energy deficits or surpluses.
House Energy Consumption: Models energy requirements of a household with voltage, current, and power usage parameters.
Energy Management Logic: Implements priority-based power management:
Charge storage with surplus PV energy.
Sell excess energy to the grid.
Discharge storage to meet household deficits.
Use the grid as a last resort to cover energy shortfalls.

Components
Photovoltaic Module (Photovoltaic.h/.cpp)

Simulates solar panel energy generation.
Inputs: Voltage and current.
Outputs: Power in Watts.
Battery Management System (BMS.h/.cpp)

Manages individual battery modules.
Tracks temperature, voltage, and current power.
Enforces safety constraints and optimizes energy distribution.
Inverter (Inverter.h/.cpp)

Regulates power flow to and from the batteries.
Ensures compatibility with grid and storage systems.
Grid (Grid.h/.cpp)

Tracks energy transactions (buying and selling).
Models voltage and frequency interactions.
House (House.h/.cpp)

Represents household energy consumption.
Parameters: Voltage, frequency, and current.
Storage (Storage.h/.cpp)

Coordinates multiple battery modules.
Implements proportional charging and discharging logic.
Balances power distribution among batteries.
Energy Management Controller (EM_Controller.h/.cpp)

Core logic for managing energy flow.
Coordinates all components based on real-time inputs.

Integration Testing
The project includes a Python-based integration testing framework to validate functionality. Each test case simulates a real-world energy management scenario with specified input configurations and expected results.
