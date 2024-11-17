# -*- coding: utf-8 -*-
"""
Created on Sun Nov 17 09:02:06 2024

@author: seif
"""


import subprocess
import json
import os
# Define test cases with configurations
test_cases = [
    {
        "name": "Scenario 1: Surplus energy from PV",
        "photovoltaic": {"power": 1000, "voltage": 230, "current": 4.53},
        "batteries": [
            {"temp": 25, "volt": 230, "max_power": 500},
            {"temp": 25, "volt": 230, "max_power": 500},
            {"temp": 25, "volt": 230, "max_power": 500},
        ],
        "inverter": {"max_power": 1500, "volt": 230, "current": 5, "freq": 50, "grid_volt": 230},
        "grid": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        "house": {"consumed": 600, "volt": 230, "freq": 50, "current": 2.6},
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
    Photovoltaic pv({pv_power}, {pv_voltage}, {pv_current}); // PV Panel
    {bms_definitions}
    Inverter inverter({inv_max_power}, {inv_voltage}, {inv_current}, {inv_freq}, {inv_grid_voltage}); // Inverter
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

    return 0;
}}
"""

# Generate C++ code for each test case
def generate_cpp_code(test_case):
    bms_definitions = "\n    ".join(
        [
            f'BMS battery_{i + 1}({b["temp"]}, {b["volt"]}, {b["max_power"]});'
            for i, b in enumerate(test_case["batteries"])
        ]
    )
    bms_instances = ", ".join([f"battery_{i + 1}" for i in range(len(test_case["batteries"]))])

    cpp_code = cpp_template.format(
        test_name=test_case["name"],
        pv_power=test_case["photovoltaic"]["power"],
        pv_voltage=test_case["photovoltaic"]["voltage"],
        pv_current=test_case["photovoltaic"]["current"],
        bms_definitions=bms_definitions,
        inv_max_power=test_case["inverter"]["max_power"],
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
def write_test_files():
    #os.makedirs("tests", exist_ok=True)
    for i, test_case in enumerate(test_cases):
        cpp_code = generate_cpp_code(test_case)
        file_name = "SonnenBatterie.cpp"
        with open(file_name, "w") as file:
            file.write(cpp_code)
        print(f"Generated {file_name}")

# Paths
cpp_file = f"SonnenBatterie.cpp"
executable = "SonnenBatterie"

def compile_cpp():
    print("Compiling C++ program...")
    result = subprocess.run(["g++", cpp_file, "-o", executable], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        print(f"Compilation failed:\n{result.stderr.decode()}")
        return False
    return True

def run_test_case(test_case):
    """Runs a single test case."""
    print(f"Running test case: {test_case['test_name']}")

    # Inject test case inputs into the C++ code
    with open("test_config.json", "w") as f:
        json.dump(test_case["input"], f)

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
            parsed[f"bms_power_{battery_id}"] = power
        elif "Grid Power Sold" in line:
            parsed["grid_sold"] = float(line.split(":")[1].strip().split()[0])
    return parsed

def generate_report(results):
    """Generates a report."""
    print("\nTest Results:")
    for result in results:
        print(f"Test Case: {result['test_name']}")
        print(f"Status: {result['status']}")
        for key, details in result.get("results", {}).items():
            print(f"  {key}: Expected={details['expected']}, Actual={details['actual']}, Status={details['status']}")
        print("\n")
def main():
    results = []

    for i in test_cases:
                
        write_test_files()
        if not compile_cpp():
            return
    
        for test_case in test_cases:
            result = run_test_case(test_case)
            result["test_name"] = test_case["test_name"]
            results.append(result)

    generate_report(results)
if __name__ == "__main__":
    main()