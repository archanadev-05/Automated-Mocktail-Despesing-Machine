# ESP32 Hardware Testing

This directory contains independent test programs used to verify ESP32 hardware, sensors, actuators, and other electronic components before integrating them into the main system.

The purpose of these tests is to validate individual components, identify hardware or software issues, and confirm that each subsystem operates as expected.

## Project Information

- **Project:** Automated Mocktail Dispensing Machine
- **Module:** Microcontroller-Based Hardware Project
- **Module Code:** IN1901
- **Microcontroller:** NodeMCU ESP-32S
- **Development Environment:** Arduino IDE / Arduino Framework

## Testing Objectives

- Verify that the ESP32 board and its GPIO pins operate correctly.
- Test individual sensors and electronic components.
- Verify communication between the ESP32 and connected components.
- Test multiple components working together.
- Validate subsystem behaviour before integration.
- Record test results and identify hardware or software issues.
- Provide a consistent testing approach for future components.

## Directory Structure

Each test is maintained in its own subdirectory to keep its source code and related test documentation organised.

```text
ESP32_Testings/
├── README.md
│
├── 01_ESP32_Board_Test/
├── 02_KY005_Transmitter_Test/
├── 03_KY022_Receiver_Test/
├── 04_Single_IR_Pair_Test/
├── 05_Three_IR_Pairs_Test/
└── 06_IR_Ladder_Cup_Detection/
```

Each test directory should contain the relevant source code and, where necessary, a short README explaining the test setup and expected behaviour.

As additional components and subsystems are introduced, create new test directories using the same naming convention.

## Current Testing Modules

| Test ID | Test Directory | Purpose |
|---|---|---|
| ESP-001 | `01_ESP32_Board_Test/` | Verify ESP32 board operation and basic GPIO functionality. |
| IR-001 | `02_KY005_Transmitter_Test/` | Test the KY-005 infrared transmitter module. |
| IR-002 | `03_KY022_Receiver_Test/` | Test the KY-022 infrared receiver module. |
| IR-003 | `04_Single_IR_Pair_Test/` | Evaluate the operation of one IR transmitter and receiver pair. |
| IR-004 | `05_Three_IR_Pairs_Test/` | Test three IR pairs together and check their individual responses. |
| IR-005 | `06_IR_Ladder_Cup_Detection/` | Prototype a three-level IR arrangement for detecting cup presence or position. |

**Note:** The IR tests are experimental until their behaviour has been verified using the actual modules and circuit. In particular, the KY-022 is a demodulating IR receiver, so its response to a KY-005 transmitter must be validated before treating the pair as a reliable beam-break sensor.

## Testing Categories

Future tests may be organised around the following categories, depending on the components used in the project.

### 1. ESP32 Board and GPIO Testing
- Board startup and reset behaviour.
- Digital input and output.
- PWM output, where applicable.
- GPIO pin and wiring verification.

### 2. Sensor Testing
- Individual sensor operation.
- Sensor readings and output signals.
- Detection accuracy and response time.
- Behaviour under different test conditions.

### 3. Actuator Testing
- Motor and pump control.
- Relay and driver operation.
- Actuator response to control signals.
- Safe startup and shutdown behaviour.

### 4. Communication Testing
- UART communication.
- I²C or SPI communication, where applicable.
- Communication between controllers and peripheral modules.
- Handling of invalid or missing responses.

### 5. Multi-Component Testing
- Multiple sensors operating together.
- Sensor and actuator coordination.
- GPIO conflicts and signal interference.
- Combined subsystem behaviour.

### 6. Subsystem Integration Testing
- Verification of connected components as a functional unit.
- Validation of subsystem inputs and outputs.
- Testing normal operation and failure conditions.
- Confirming that a subsystem is ready for integration.

Only include categories that are relevant to the hardware being tested.

## Standard Testing Procedure

Follow these steps when creating or running a test.

1. **Identify the objective**  
   State the component or behaviour being tested.

2. **Prepare the circuit**  
   Connect the components according to the relevant circuit diagram or pin configuration.

3. **Verify the connections**  
   Check the supply voltage, ground connections, GPIO assignments, and wiring before powering the circuit.

4. **Upload the test program**  
   Select the correct ESP32 board and serial port in the development environment.

5. **Execute the test**  
   Observe the component's behaviour and collect readings or serial output.

6. **Compare the results**  
   Check the observed behaviour against the expected result.

7. **Record the outcome**  
   Document the result, problems encountered, and any changes made.

8. **Repeat when necessary**  
   Repeat the test after correcting an issue or changing the hardware or software.

## Test Documentation Template

Use the following template in a test-specific README or test report when additional documentation is needed.

```text
Test ID:
Test Name:
Test Date:
Tested By:

Objective:

Hardware Components:

Circuit / Pin Configuration:

Software Requirements:

Test Procedure:

Expected Result:

Observed Result:

Status: Not Started / In Progress / Passed / Failed / Blocked

Issues Identified:

Corrective Actions:

Additional Notes:
```

## Test Status Definitions

| Status | Meaning |
|---|---|
| Not Started | The test has not been performed. |
| In Progress | Testing is currently underway. |
| Passed | The observed behaviour satisfies the defined acceptance criteria. |
| Failed | The test did not satisfy the acceptance criteria. |
| Blocked | Testing cannot continue because of an unresolved issue. |
| Prototype | The test is experimental and has not yet been fully validated. |
| Needs Revalidation | A hardware or software change requires the test to be repeated. |
| Deprecated | The test is no longer used or has been replaced. |

## Hardware and Electrical Safety

- Verify the operating voltage of each component before connecting it to the ESP32.
- Do not apply 5 V signals directly to ESP32 GPIO pins; ESP32 GPIOs are generally not 5 V tolerant.
- Ensure that connected modules share a suitable common ground when required.
- Use appropriate driver circuits for motors, pumps, relays, and other loads that cannot be driven directly by GPIO pins.
- Disconnect power before modifying circuit connections.
- Check the module pinout and board documentation instead of relying solely on wire colours or assumed pin assignments.

## Adding a New Test

When testing a new component or subsystem:

1. Create a new directory using a descriptive name and a numerical prefix.
2. Add the test source code to that directory.
3. Document the objective, wiring, and expected behaviour when needed.
4. Follow the standard testing procedure.
5. Record the test result and any issues.
6. Update the **Current Testing Modules** table in this README.
7. Re-run the test if relevant hardware connections or software behaviour change.

### Naming Convention

Use the following format for new test directories:

```text
NN_Component_or_Subsystem_Test/
```

Examples:

```text
07_Flow_Sensor_Test/
08_Pump_Control_Test/
09_Water_Level_Sensor_Test/
10_Subsystem_Integration_Test/
```

Use the next available number and choose a name that clearly identifies the purpose of the test.

## Test Results and Evidence

When useful, keep supporting evidence with the relevant test, such as:

- Serial Monitor output.
- Photographs of the test circuit.
- Sensor readings.
- Observed failures and corrective actions.
- Test reports documenting the final result.

Record enough information for another team member to reproduce the test.

## Maintenance

This README describes the testing approach used within `ESP32_Testings/`. Update it whenever new tests are added, test names change, or testing procedures are revised.

Keep individual test programs focused on their specific objectives. Experimental test code should not automatically be treated as validated production code.