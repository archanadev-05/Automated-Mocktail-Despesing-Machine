# AuraMix - Smart Office Mocktail Dispensing System

[![Board: ESP32-S3](https://img.shields.io/badge/Board-ESP32--S3%20(N16R8)-blue?style=flat-square&logo=expressif)](https://www.espressif.com/)
[![Framework: PlatformIO / C++](https://img.shields.io/badge/Framework-PlatformIO%20%7C%20Arduino-orange?style=flat-square&logo=platformio)](https://platformio.org/)
[![RTOS: FreeRTOS](https://img.shields.io/badge/RTOS-FreeRTOS%20Dual--Core-green?style=flat-square)](https://www.freertos.org/)
[![Web: AsyncWebSocket](https://img.shields.io/badge/Web-ESPAsyncWebServer%20%2B%20WebSocket-purple?style=flat-square)](https://github.com/me-no-dev/ESPAsyncWebServer)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](LICENSE)

**AuraMix** is an automated, access-controlled, IoT-enabled mocktail dispensing mechatronics system engineered for modern office environments. Powered by a single **ESP32-S3 microcontroller (16MB Flash / 8MB PSRAM)** running FreeRTOS, the system features a stationary central mixing chamber with clean-in-place (CIP) automated rinsing, dual biometric and PIN authentication, dynamic cup-size validation via a 6-sensor IR ladder, thermally managed ice dispensing, and a real-time web administration dashboard.

---

## 📐 Project Overview & Mechanical Architecture

AuraMix replaces traditional moving-tray/rail mechanisms with a **stationary central mixing chamber architecture**:
1. **Central Mixing Chamber**: Six independent 12V peristaltic pumps deliver precise volumetric doses into a food-grade mixing funnel. An integrated 12V DC paddle motor blends the ingredients thoroughly prior to serving.
2. **Automated Clean-In-Place (CIP)**: After every drink, an automated multi-stage rinse cycle flushes the chamber with clean water from an internal reservoir and diverts waste directly to a drain tank.
3. **Fail-Safe Diverter Solenoid**: A 2-way diverter valve defaults to the **WASTE** position on power loss or boot-up to ensure unrinsed liquid can never contaminate a glass.
4. **Dual Cup Verification**: Combines a **5kg load cell** (tare/weight monitoring) with a **6-sensor IR break-beam ladder** (cup height & profile validation) to prevent spills, detect missing cups, and dynamically scale recipe volumes.

---

## 📂 Repository Directory Structure

```text
AuraMix-Smart-Dispenser/
├── README.md                           # Master Project Documentation
├── LICENSE                             # MIT License
├── .gitignore                          # Git ignore rules for PIO, CAD, & build binaries
│
├── firmware/                           # Embedded C++ Code (PlatformIO Project)
│   ├── platformio.ini                  # PlatformIO Environment & Dependency Config
│   ├── data/                           # LittleFS Filesystem (Web Assets)
│   │   ├── index.html                  # Admin Dashboard Interface (Minified)
│   │   ├── style.css                   # Dashboard Styles
│   │   ├── app.js                      # WebSocket Client & Telemetry Handler
│   │   └── recipes.json                # Recipe Database & Preset Configurations
│   │
│   ├── include/                        # Global Headers & Configurations
│   │   ├── Config.h                    # Pinouts, Hardware Constants & Constants
│   │   └── Types.h                     # Enums, Data Structures & System States
│   │
│   ├── lib/                            # Custom Peripheral Libraries
│   │   ├── IRLadder/                   # 6-Beam IR Cup Height Module
│   │   ├── DispenserEngine/            # Pump Calibration & Mixing Logic
│   │   └── CleaningSystem/             # Automated Rinse Cycle State Machine
│   │
│   └── src/                            # Application Source Code
│       ├── main.cpp                    # System Initialization & Core Task Pinning
│       ├── tasks/                      # FreeRTOS Concurrent Tasks
│       │   ├── Task_Dispense.cpp       # Core 1: Pump, Mixer & Valve Control
│       │   ├── Task_Safety.cpp         # Core 1: Load Cell, IR, & Jam Monitoring
│       │   ├── Task_Auth.cpp           # Core 1: Fingerprint & Keypad Processing
│       │   └── Task_Web.cpp            # Core 0: AsyncWebServer & Telemetry
│       └── modules/                    # Low-Level Drivers
│           ├── AuthController.cpp      # R307 Fingerprint & Matrix Keypad
│           ├── LoadCellDriver.cpp      # HX711 Interface & Tare Calibration
│           └── WebServerManager.cpp    # WebSocket Events & JSON Serialization
│
├── hardware/                           # Hardware Design & Fabrication Files
│   ├── schematics/                     # Circuitry & Wiring Diagrams
│   │   ├── System_Wiring_Diagram.pdf   # Complete Interconnection Map
│   │   └── Power_Distribution.pdf      # 12V PSU / Buck / MOSFET Rail Distribution
│   ├── cad/                            # Mechanical 3D CAD Enclosure Models
│   │   ├── AuraMix_Assembly_REV_C1.step# Complete Assembly 3D STEP
│   │   └── stl/                        # 3D Printable Components (Spout, Brackets)
│   ├── dxf/                            # CNC / Laser Cut Sheet Profiles (1:1)
│   │   ├── F01_Front_Header.dxf        # Control Panel Display & Keypad Cutouts
│   │   ├── F10_F12_Cup_Bay_Panels.dxf  # Cup Bay Enclosure Acrylic Cutouts
│   │   └── N01_Shared_Outlet.dxf       # Main Dispensing Spout & Flange
│   └── bom/                            # Bill of Materials
│       └── Component_Cost_List.xlsx    # Full Hardware Component Breakdown
│
├── docs/                               # System Documentation & Reports
│   ├── Project_Proposal_Report.pdf     # Engineering & Architectural Specifications
│   ├── cad_drawings/                   # Mechanical Engineering Drawings (Sheets 1-4)
│   │   ├── Sheet_1_Front_Elevation.pdf
│   │   ├── Sheet_2_Control_Cutouts.pdf
│   │   ├── Sheet_3_Outlet_DripTray.pdf
│   │   └── Sheet_4_Part_Schedule.pdf
│   └── images/                         # Renders & Architecture Flowcharts
│       ├── AuraMix_Render.jpg
│       ├── System_Block_Diagram.png
│       └── State_Flowchart.png
│
└── scripts/                            # Helper Utilities
    ├── build_web_assets.py             # Compresses & Gzips Web Assets for LittleFS
    └── pump_calibration.py             # Calculates Flow-Rate Constants (mL/sec)
```

---

## ⚡ ESP32-S3 Pin Mapping (Hardware Reference)

| Subsystem | Peripheral Component | ESP32-S3 GPIO | Bus / Interface | Logic / Type |
| :--- | :--- | :--- | :--- | :--- |
| **Authentication** | Fingerprint (R307/AS608) | GPIO 17 (TX), 18 (RX) | UART2 | 3.3V TTL |
| | Keypad 4x3 (Rows) | GPIO 38, 39, 40, 41 | Digital Input | Matrix Scan |
| | Keypad 4x3 (Cols) | GPIO 42, 45, 46 | Output | Matrix Scan |
| **User Display** | LCD 16x2 Display | GPIO 1 (SDA), 2 (SCL) | I2C0 | 3.3V/5V I2C |
| **Cup Sensing** | 6-Sensor IR Ladder (S1..S6) | GPIO 4, 5, 6, 7, 15, 16 | Digital Input | Active-Low w/ Pullup |
| | Load Cell (HX711) | GPIO 8 (DT), 9 (SCK) | Bit-Banged 2-Wire | Digital |
| | Proximity IR Sensor | GPIO 3 | Digital Input | Active-Low |
| **Actuators** | Peristaltic Pumps (P1..P6) | GPIO 10, 11, 12, 13, 21, 47 | MOSFET Output | PWM / Digital |
| | Chamber Stir Motor | GPIO 14 | MOSFET Output | PWM Speed Control |
| | Serve Solenoid Valve | GPIO 35 | Solenoid Driver | Active-HIGH |
| | Diverter Solenoid Valve | GPIO 36 | Solenoid Driver | Active-HIGH (Default: Waste) |
| | Rinse Pump | GPIO 37 | MOSFET Output | Digital |
| | Ice Auger DC Motor | GPIO 48 | MOSFET Output | Digital w/ ACS712 Jam Sense |
| **Environment** | Temperature (DS18B20 x2) | GPIO 34 | OneWire | OneWire Bus |
| **Safety System** | Emergency Stop Switch | Physical Relay Cut | Direct 12V Hardware Cut | Fail-Safe Relay |

---

## 🛠️ Software & Firmware Setup

### Prerequisites
1. **Visual Studio Code** with the **PlatformIO IDE Extension** installed.
2. **ESP32 USB Drivers** (CH340 / CP210x / Native USB depend on board).

### Build & Flash Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/YourUsername/AuraMix-Smart-Dispenser.git
   cd AuraMix-Smart-Dispenser/firmware
   ```

2. **Build Firmware**:
   Open the `firmware` directory in VS Code / PlatformIO and run:
   ```bash
   pio run
   ```

3. **Upload Web Dashboard Assets to LittleFS**:
   To upload the `data/` folder containing the Web Dashboard interface directly to the ESP32-S3 Flash:
   ```bash
   pio run --target uploadfs
   ```

4. **Flash Firmware & Open Serial Monitor**:
   ```bash
   pio run --target upload --target monitor
   ```

---

## 🔄 FreeRTOS Task Distribution

The ESP32-S3 handles real-time actuator execution, sensor polling, and network communication without timing contention by pinning FreeRTOS tasks across both Xtensa cores:

* **Core 0 (Networking & Web)**:
  * `Task_Web`: Hosts `ESPAsyncWebServer`, handles `AsyncWebSocket` live telemetry feeds (pumps, waste level, glass status), and processes incoming admin commands.
* **Core 1 (Real-Time Control & Safety)**:
  * `Task_Dispense`: Manages pump calibration timing, valve sequencing (Serve vs. Diverter), and in-chamber stirring.
  * `Task_Safety`: Polls the Load Cell (HX711), 6-sensor IR ladder, ACS712 auger current, and fluid level floats at high priority (50 Hz).
  * `Task_Auth`: Scans fingerprint sensor UART and keypad matrix for user authentication.

---

## 🔒 Safety Interlocks & Fail-Safes

* **Fail-Safe Waste Routing**: The diverter valve is physically wired to route all outflow to the **Waste Tank** when unpowered. It energizes to the **Serve** position only when active drink dispensing occurs.
* **E-Stop Hardware Override**: A mushroom-head emergency stop cuts the main 12V PSU output line directly, halting all pumps, valves, and motors instantly regardless of software state.
* **Dual Cup Verification**: Liquid will not pour unless the **IR Ladder** verifies cup height *and* the **Load Cell** confirms glass presence with an acceptable tare weight.
* **Auger Jam Auto-Reverse**: The ice hopper uses an ACS712 current sensor to detect motor stall conditions (>3.5A) and triggers a brief auto-reverse pulse sequence to clear ice jams.

---

## 📄 License & Attribution

This project is released under the [MIT License](LICENSE). 

Designed and developed for the **BSc (Hons) in Information Technology** Capstone Mechatronics Project (Academic Year 2024/2025).
