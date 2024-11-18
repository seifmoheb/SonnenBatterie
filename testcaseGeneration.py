import subprocess
import json
import os

# Define test cases with configurations
test_cases = [
    {
        "name": "Scenario 1: Surplus energy from PV, charge all batteries",
        "photovoltaic": {"voltage": 666.6, "current": 1.5},
        "batteries": [
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
        ],
        "inverter": {"volt": 230, "current": 10, "freq": 50, "grid_volt": 230},
        "grid": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        "house": {"consumed": 600, "volt": 230, "freq": 50, "current": 2.6},
        "expected": {
            "battery_1_power": 233.3,
            "battery_2_power": 233.3,
            "battery_3_power": 233.3,
            "grid_sold": 0,
            "grid_bought": 0,
        },
    },
    {
        "name": "Scenario 2: Surplus energy from PV, charge all batteries, then sell to grid",
        "photovoltaic": {"voltage": 1000.6, "current": 1.5},
        "batteries": [
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
        ],
        "inverter": {"volt": 230, "current": 10, "freq": 50, "grid_volt": 230},
        "grid": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        "house": {"consumed": 20, "volt": 230, "freq": 50, "current": 2.6},
        "expected": {
            "battery_1_power": 500,
            "battery_2_power": 500,
            "battery_3_power": 500,
            "grid_sold": 280,
            "grid_bought": 0,
        },
    },
    {
        "name": "Scenario 3: Deficit energy from PV, discharge all batteries",
        "photovoltaic": {"voltage": 10.6, "current": 1.5},
        "batteries": [
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
        ],
        "inverter": {"volt": 230, "current": 10, "freq": 50, "grid_volt": 230},
        "grid": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        "house": {"consumed": 250, "volt": 230, "freq": 50, "current": 2.6},
        "expected": {
            "battery_1_power": 21.9,
            "battery_2_power": 21.9,
            "battery_3_power": 21.9,
            "grid_sold": 0,
            "grid_bought": 0,
        },
    },
    {
        "name": "Scenario 4: Deficit energy from PV, discharge all batteries, buy from grid",
        "photovoltaic": {"voltage": 10.6, "current": 1.5},
        "batteries": [
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":100},
        ],
        "inverter": {"volt": 230, "current": 10, "freq": 50, "grid_volt": 230},
        "grid": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        "house": {"consumed": 500, "volt": 230, "freq": 50, "current": 2.6},
        "expected": {
            "battery_1_power": 0,
            "battery_2_power": 0,
            "battery_3_power": 0,
            "grid_sold": 0,
            "grid_bought": 184,
        },
    }
    ,
    {
        "name": "Scenario 5: Surplus energy from PV, full batteries, sell all to grid",
        "photovoltaic": {"voltage": 666.6, "current": 1.5},
        "batteries": [
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":500},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":500},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":500},
        ],
        "inverter": {"volt": 230, "current": 10, "freq": 50, "grid_volt": 230},
        "grid": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        "house": {"consumed": 600, "volt": 230, "freq": 50, "current": 2.6},
        "expected": {
            "battery_1_power": 500,
            "battery_2_power": 500,
            "battery_3_power": 500,
            "grid_sold": 399,
            "grid_bought": 0,
        },
    },
    {
        "name": "Scenario 5: 2 Batteries Basic, Surplus energy from PV, full batteries, sell all to grid",
        "photovoltaic": {"voltage": 666.6, "current": 1.5},
        "batteries": [
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":500},
            {"temp": 25, "volt": 230, "max_power": 500, "current_power":500},
            
        ],
        "inverter": {"volt": 230, "current": 10, "freq": 50, "grid_volt": 230},
        "grid": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        "house": {"consumed": 600, "volt": 230, "freq": 50, "current": 2.6},
        "expected": {
            "battery_1_power": 500,
            "battery_2_power": 500,
            "grid_sold": 399,
            "grid_bought": 0,
        },
    }
]

# Template for C++ code
cpp_template = """
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

int main() {{
    // Initialize components for {test_name}
    Photovoltaic pv({pv_voltage}, {pv_current}); // PV Panel
    {bms_definitions}
    Inverter inverter({inv_voltage}, {inv_current}, {inv_freq}, {inv_grid_voltage}); // Inverter
    Grid grid({grid_sold}, {grid_bought}, {grid_voltage}, {grid_freq}); // Grid
    House house({house_consumed}, {house_voltage}, {house_freq}, {house_current}); // House
    std::vector<BMS> batteryModules = {{ {bms_instances} }};
    Storage storage(inverter, batteryModules);
    EM_Controller controller(pv, grid, storage, house);

    // Manage energy
    controller.manageEnergy();

    // Output results
    std::cout << "Battery Modules Power:" << std::endl;
    for (size_t i = 0; i < storage.getBatteryModules().size(); i++) {{
        std::cout << "Battery " << (i + 1) << ": " << storage.getBatteryModules().at(i).getCurrentPower() << " W" << std::endl;
    }}
    std::cout << "Grid Power Sold: " << grid.getPowerSold() << " W" << std::endl;
    std::cout << "Grid Power Bought: " << grid.getPowerBought() << " W" << std::endl;

    return 0;
}}
"""

# Generate C++ code for each test case
def generate_cpp_code(test_case):
    bms_definitions = "\n    ".join(
        [
            f'BMS battery_{i + 1}({b["temp"]}, {b["volt"]}, {b["max_power"]},{b["current_power"]});'
            for i, b in enumerate(test_case["batteries"])
        ]
    )
    bms_instances = ", ".join([f"battery_{i + 1}" for i in range(len(test_case["batteries"]))])

    cpp_code = cpp_template.format(
        test_name=test_case["name"],
        pv_voltage=test_case["photovoltaic"]["voltage"],
        pv_current=test_case["photovoltaic"]["current"],
        bms_definitions=bms_definitions,
        inv_voltage=test_case["inverter"]["volt"],
        inv_current=test_case["inverter"]["current"],
        inv_freq=test_case["inverter"]["freq"],
        inv_grid_voltage=test_case["inverter"]["grid_volt"],
        grid_sold=test_case["grid"]["sold"],
        grid_bought=test_case["grid"]["bought"],
        grid_voltage=test_case["grid"]["volt"],
        grid_freq=test_case["grid"]["freq"],
        house_consumed=test_case["house"]["consumed"],
        house_voltage=test_case["house"]["volt"],
        house_freq=test_case["house"]["freq"],
        house_current=test_case["house"]["current"],
        bms_instances=bms_instances,
    )
    return cpp_code

# Write each test case to a separate C++ file
def write_test_files(test_case):
    
        cpp_code = generate_cpp_code(test_case)
        file_name = f"SonnenBatterie.cpp"
        with open(file_name, "w") as file:
            file.write(cpp_code)
        print(f"Generated {file_name}")

# Paths
executable = "SonnenBatterie"

def compile_cpp(cpp_file):
    print(f"Compiling {cpp_file}...")
    result = subprocess.run(["g++", cpp_file, "-o", executable], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        print(f"Compilation failed:\n{result.stderr.decode()}")
        return False
    return True

def run_test_case(test_case, cpp_file):
    """Runs a single test case."""
    print(f"Running test case: {test_case['name']}")

    if not compile_cpp(cpp_file):
        return {"status": "failed", "error": "Compilation failed"}

    # Execute the compiled program
    result = subprocess.run([f"./{executable}"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        print(f"Execution failed:\n{result.stderr.decode()}")
        return {"status": "failed", "error": result.stderr.decode()}

    # Parse the output
    output = result.stdout.decode()
    print("Program output:")
    print(output)
    return compare_output(output, test_case["expected"])

def compare_output(output, expected):
    """Compares actual and expected output."""
    actual = parse_output(output)
    results = {}
    passed = True

    for key, expected_value in expected.items():
        actual_value = actual.get(key)
        results[key] = {
            "expected": expected_value,
            "actual": actual_value,
            "status": "passed" if actual_value == expected_value else "failed",
        }
        if results[key]["status"] == "failed":
            passed = False

    return {"status": "passed" if passed else "failed", "results": results}

def parse_output(output):
    """Parses output from the C++ program."""
    parsed = {}
    lines = output.splitlines()
    for line in lines:
        if "Battery" in line:
            parts = line.split(":")
            battery_id = parts[0].strip().split()[-1]
            power = float(parts[1].strip().split()[0])
            parsed[f"battery_{battery_id}_power"] = power
        elif "Grid Power Sold" in line:
            parsed["grid_sold"] = float(line.split(":")[1].strip().split()[0])
        elif "Grid Power Bought" in line:
            parsed["grid_bought"] = float(line.split(":")[1].strip().split()[0])
    return parsed

def generate_report(results):
    """Generates a report."""
    print("\nTest Results:")
    for result in results:
        print(f"Test Case: {result['name']}")
        print(f"Status: {result['status']}")
        for key, details in result.get("results", {}).items():
            print(f"  {key}: Expected={details['expected']}, Actual={details['actual']}, Status={details['status']}")
        print("\n")

def main():
    results = []

    for i, test_case in enumerate(test_cases):
        cpp_file = f"SonnenBatterie_{i + 1}.cpp"
        write_test_files(test_case)
        val = input("Type any key generate next testcase\n")
            
        #result = run_test_case(test_case, cpp_file)
        #result["name"] = test_case["name"]
        #results.append(result)

    #generate_report(results)

if __name__ == "__main__":
    main()
