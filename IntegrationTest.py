# -*- coding: utf-8 -*-
"""
Created on Sun Nov 17 08:53:21 2024

@author: seif
"""

import subprocess
import json
import os

# Test cases
test_cases = [
    {
        "test_name": "Scenario 1: Surplus energy from PV",
        "input": {
            "pv_power": 1000,
            "house_consumption": 600,
            "bms_configs": [
                {"temp": 25, "volt": 230, "max_power": 500},
                {"temp": 25, "volt": 230, "max_power": 500},
                {"temp": 25, "volt": 230, "max_power": 500},
            ],
            "inverter_config": {"max_power": 1500, "volt": 230, "current": 5, "freq": 50},
            "grid_config": {"sold": 0, "bought": 0, "volt": 230, "freq": 50},
        },
        "expected": {
            "bms_powers": [333.33, 333.33, 333.33],  # Example: Distributed surplus
            "grid_sold": 0,
        },
    }
]

# Paths
cpp_file = "SonnenBatterie.cpp"
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
    if not compile_cpp():
        return

    results = []
    for test_case in test_cases:
        result = run_test_case(test_case)
        result["test_name"] = test_case["test_name"]
        results.append(result)

    generate_report(results)

if __name__ == "__main__":
    main()
