# AuraMix — Smart Office Mocktail Dispensing System

![Board: ESP32-S3](https://img.shields.io/badge/Board-ESP32--S3-blue?style=flat-square)
![Framework: PlatformIO / Arduino](https://img.shields.io/badge/Framework-PlatformIO%20%7C%20Arduino-orange?style=flat-square)
![RTOS: FreeRTOS](https://img.shields.io/badge/RTOS-FreeRTOS-green?style=flat-square)
![Module: IN1901](https://img.shields.io/badge/Module-IN1901-purple?style=flat-square)

**AuraMix** is an automated mocktail dispensing system developed as a hardware-oriented embedded systems project. The system integrates an ESP32-S3 microcontroller, infrared cup detection, weight measurement, liquid dispensing, automated cleaning, and a web-based monitoring interface.

The project aims to improve dispensing accuracy, verify cup placement, and coordinate multiple hardware components through embedded control software.

## 1. Academic Information

| Field | Details |
|---|---|
| Project Name | AuraMix — Smart Office Mocktail Dispensing System |
| Course Module | Microcontroller Based Hardware Project |
| Module Code | IN1901 |
| Degree Programme | BSc (Hons) in Information Technology |
| Faculty | Faculty of Information Technology, University of Moratuwa |
| Main Controller | ESP32-S3 |
| Firmware Framework | Arduino / PlatformIO |
| RTOS | FreeRTOS |

## 2. Project Overview

AuraMix is designed around a stationary mixing chamber and a coordinated dispensing mechanism.

The main subsystems are:

### 2.1 Liquid Dispensing System

Multiple peristaltic pumps deliver measured quantities of mocktail ingredients into a central mixing chamber.

### 2.2 Cup Detection System

Three KY-005 infrared transmitters and three KY-022 infrared receivers are arranged as three detection pairs.

The system evaluates the validated signals from these pairs to help determine whether a cup is present and whether its height or placement is suitable for dispensing.

Because KY-022 modules are demodulating IR receivers, their behavior must be validated with modulated transmissions before the system is treated as a conventional beam-break detector.


### 2.3 Mixing System

A motor-driven mixing mechanism combines the selected ingredients before serving.

### 2.5 Automated Cleaning System

A cleaning cycle flushes the mixing chamber after dispensing. Waste liquid is routed to a designated waste reservoir.

### 2.6 Control and Monitoring Interface

A web interface provides access to system status, dispensing information, and administrative functions.

## 3. Hardware Components

The intended hardware includes:

- ESP32-S3 development board.
- Three KY-005 infrared transmitter modules.
- Three KY-022 infrared receiver modules.
- Peristaltic pumps and suitable driver circuits.
- Mixing motor and driver.
- Solenoid valves and suitable driver circuits.
- Temperature sensors, if required by the final design.
- Authentication peripherals, if implemented.
- Power supplies and voltage regulators.
- Emergency-stop hardware.
- Connecting wires, mounting brackets, and mechanical enclosure.

The final component list and GPIO assignments must be verified against the physical hardware before integration.

## 4. Three-Pair IR Ladder Cup Detection

### 4.1 Sensor Arrangement

The IR ladder uses three transmitter-receiver pairs:

| Pair | Transmitter | Receiver | Purpose |
|---|---|---|---|
| Pair 1 | KY-005 #1 | KY-022 #1 | Lower detection level |
| Pair 2 | KY-005 #2 | KY-022 #2 | Middle detection level |
| Pair 3 | KY-005 #3 | KY-022 #3 | Upper detection level |

The three pairs are mounted at different heights around the cup area.

Each transmitter should face its corresponding receiver.

### 4.2 Detection Principle

The ESP32-S3 generates modulated IR signals for the transmitters. The receiver outputs are monitored to determine whether the expected signals can be detected.

When a cup interrupts the optical path, reception may change. The software must identify that change reliably and distinguish it from:

- Temporary signal loss.
- Electrical noise.
- Interference from other IR transmitters.
- Misalignment between modules.
- Differences in cup geometry and material.

The KY-022 is designed for demodulating modulated IR signals, commonly around 38 kHz. Consequently, a simple continuous HIGH output from the KY-005 is not a suitable assumption for the complete detection design.

### 4.3 Detection Development Stages

The implementation follows these stages:

1. Test the ESP32-S3 board.
2. Verify KY-005 transmitter operation.
3. Verify KY-022 receiver operation using a compatible modulated IR signal.
4. Test one transmitter-receiver pair.
5. Test all three pairs and evaluate interference.
6. Implement the three-level detection logic.
7. Validate cup detection with different cup sizes and positions.
8. Integrate the validated driver into the main firmware.

### 4.4 Dispensing Safety

The dispensing system must not rely on a single unverified sensor reading.

Before dispensing, the control system should verify the required cup-detection state and weight measurement. Uncertain or invalid sensor states must prevent dispensing.

The final safety behavior must be validated on the physical machine.

## 5. Repository Structure

```text
Automated-Mocktail-Despesing-Machine/
├── README.md
├── LICENSE
├── .gitignore
│
├── ESP32_Testings/
│   ├── README.md
│   ├── 01_ESP32_Board_Test/
│   ├── 02_KY005_Transmitter_Test/
│   ├── 03_KY022_Receiver_Test/
│   ├── 04_Single_IR_Pair_Test/
│   ├── 05_Three_IR_Pairs_Test/
│   └── 06_IR_Ladder_Cup_Detection/
│
├── firmware/
│   ├── platformio.ini
│   ├── include/
│   ├── lib/
│   │   ├── IRLadder/
│   │   ├── DispenserEngine/
│   │   └── CleaningSystem/
│   ├── src/
│   │   ├── main.cpp
│   │   ├── tasks/
│   │   └── modules/
│   └── data/
│
├── hardware/
│   ├── schematics/
│   ├── cad/
│   └── bom/
│
├── docs/
│   ├── project_proposal/
│   ├── circuit_diagrams/
│   └── testing_results/
│
└── scripts/
```

## 6. ESP32 Testing Environment

Standalone hardware tests are maintained under `ESP32_Testings/`.

Each test should contain:

- An Arduino `.ino` sketch.
- Wiring instructions.
- Required libraries.
- Expected Serial Monitor output.
- Actual observations.
- Test status and known limitations.

The tests must be completed before integrating the sensor driver into the main firmware.

## 7. Main Firmware Architecture

The main firmware is developed using PlatformIO and the Arduino framework.

### Core Components

**IRLadder**

Responsible for interpreting the three validated IR receiver channels and reporting the detection state.

**DispenserEngine**

Responsible for coordinating pump operation, dispensing sequences, and mixing.

**CleaningSystem**

Responsible for the cleaning cycle and waste-routing sequence.

**WebServerManager**

Responsible for the web interface and system telemetry.

### FreeRTOS Tasks

The intended task structure includes:

- `Task_Dispense`: Coordinates dispensing and mixing.
- `Task_Safety`: Monitors cup detection, weight measurements, and safety conditions.
- `Task_Auth`: Handles authentication inputs, if implemented.
- `Task_Web`: Handles network communication and dashboard updates.

Task priorities, core assignments, and execution periods must be validated during integration. Safety-critical operations must not depend on web-server availability.

## 8. Development Workflow

### Step 1 — Clone the Repository

```bash
git clone https://github.com/archanadev-05/Automated-Mocktail-Despesing-Machine.git

cd Automated-Mocktail-Despesing-Machine
```

### Step 2 — Test the ESP32

Open the appropriate sketch in `ESP32_Testings/` using Arduino IDE.

Select the correct ESP32-S3 board and serial port before uploading.

### Step 3 — Validate the IR Sensors

Run the individual transmitter and receiver tests before attempting the complete three-pair ladder.

Record the observed receiver behavior when the IR path is clear and when an opaque object interrupts it.

### Step 4 — Develop the IR Ladder

Implement the detection logic using the validated signal behavior.

Test different cup heights, positions, and orientations before integrating dispensing control.

### Step 5 — Build the Main Firmware

Open the `firmware/` directory as a PlatformIO project.

Build using:

```bash
pio run
```

Upload the firmware using:

```bash
pio run --target upload
```

Open the serial monitor using:

```bash
pio device monitor
```

Web filesystem upload commands should be configured according to the filesystem plugin and partition layout selected for the actual project.

## 9. Safety Considerations

- Do not activate dispensing pumps unless the required cup-presence conditions have been satisfied.
- Validate IR readings before using them as safety interlocks.
- Stop dispensing if cup detection becomes invalid during operation.
- Use appropriate driver circuits for pumps, motors, and solenoid valves.
- Provide suitable protection against inductive voltage spikes.
- Separate low-voltage logic from higher-current actuator circuits as required by the electrical design.
- Implement a physical emergency stop that safely interrupts actuator power.
- Ensure cleaning and serving modes cannot route liquid incorrectly.
- Test the complete system with water before using ingredients.

## 10. Project Status

The project is developed incrementally, beginning with independent component testing and progressing toward integrated operation.

Implementation status should be updated as hardware tests are completed.

| Subsystem | Status |
|---|---|
| ESP32-S3 board test | To be verified |
| KY-005 transmitter test | To be verified |
| KY-022 receiver test | To be verified |
| Single IR pair | To be verified |
| Three-pair IR ladder | To be verified |
| Pump control | To be verified |
| Mixing system | To be verified |
| Cleaning system | To be verified |
| Web interface | To be verified |

## 11. Academic Context

AuraMix is developed for the **Microcontroller Based Hardware Project (IN1901)** module in the Faculty of Information Technology at the University of Moratuwa.

The project focuses on embedded programming, microcontroller interfacing, hardware integration, sensing, actuator control, and system-level testing.

## 12. License

This repository uses the MIT License if the included `LICENSE` file specifies that license.

Project hardware, software, and implementation details should be documented as development progresses.
