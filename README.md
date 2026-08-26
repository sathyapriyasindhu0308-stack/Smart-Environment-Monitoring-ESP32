# Smart Environment Monitoring and Alert System using ESP32

## 📌 Project Overview

The Smart Environment Monitoring and Alert System is an ESP32-based embedded system designed to monitor environmental conditions in real time.

The system uses a DHT11 sensor to measure temperature and humidity and an LDR (Light Dependent Resistor) to monitor the surrounding light level.

The sensor readings are displayed on an I2C OLED display and are also printed to the Serial Monitor.

Based on predefined temperature and humidity thresholds, the system identifies three environmental conditions:

- 🟢 NORMAL
- 🟡 WARNING
- 🔴 CRITICAL

Three LEDs provide visual status indication, while a buzzer provides an audio alert during a critical condition.

---

## 🎯 Objectives

- To interface multiple sensors with an ESP32.
- To measure temperature and humidity using a DHT11 sensor.
- To monitor light levels using an LDR.
- To display real-time sensor readings using an OLED display.
- To classify environmental conditions using predefined thresholds.
- To provide visual alerts using LEDs.
- To provide an audio alert using a buzzer.
- To monitor sensor readings through the Serial Monitor.
- To develop and test a complete embedded-system prototype.

---

## 🧰 Components Used

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 Development Board | 1 | Main microcontroller |
| DHT11 Sensor | 1 | Temperature and humidity measurement |
| LDR | 1 | Light-level measurement |
| I2C OLED Display | 1 | Display sensor readings and status |
| Green LED | 1 | Normal status |
| Yellow LED | 1 | Warning status |
| Red LED | 1 | Critical status |
| 3-Pin Buzzer | 1 | Audio alert |
| Resistors | As required | Circuit protection |
| Breadboard | 1 | Circuit prototyping |
| Jumper Wires | As required | Electrical connections |
| USB Cable | 1 | Programming and power |

---

## 🔌 Pin Connections

| Component | ESP32 GPIO |
|---|---:|
| DHT11 DATA | GPIO 4 |
| LDR | GPIO 34 |
| Green LED | GPIO 25 |
| Yellow LED | GPIO 26 |
| Red LED | GPIO 27 |
| Buzzer Signal | GPIO 18 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

### Power Connections

- DHT11 VCC → ESP32 3.3V
- OLED VCC → ESP32 3.3V
- Sensor and OLED GND → ESP32 GND
- LEDs are connected through appropriate resistors.

---

## ⚙️ How the System Works

When the ESP32 is powered ON, it initializes the DHT11 sensor, LDR, OLED display, LEDs, and buzzer.

The system then continuously reads:

- Temperature
- Humidity
- Light level

The readings are displayed on the OLED and printed to the Serial Monitor.

The temperature and humidity values are compared with predefined thresholds to determine the environmental status.

---

## 🚦 Environmental Status

### 🟢 NORMAL

The environment is within the normal operating range.

**Output:**

- Green LED → ON
- Yellow LED → OFF
- Red LED → OFF
- Buzzer → OFF

---

### 🟡 WARNING

The warning condition occurs when temperature or humidity reaches the warning threshold.

Current thresholds:

- Temperature ≥ 30 °C
- Humidity ≥ 70 %

provided the critical threshold has not been reached.

**Output:**

- Green LED → OFF
- Yellow LED → ON
- Red LED → OFF
- Buzzer → OFF

---

### 🔴 CRITICAL

The critical condition occurs when temperature or humidity reaches the critical threshold.

Current thresholds:

- Temperature ≥ 35 °C
- Humidity ≥ 80 %

**Output:**

- Green LED → OFF
- Yellow LED → OFF
- Red LED → ON
- Buzzer → ON according to the programmed alert pattern

---

## 🔊 Buzzer Alert

The buzzer is connected to GPIO 18.

During a critical condition, the buzzer produces an intermittent audio alert.

The programmed pattern is approximately:

- Buzzer ON → 1 second
- Buzzer OFF → 4 seconds

---

## 💡 LDR Light Monitoring

The LDR is connected to GPIO 34, which is used as an analog input.

The ESP32 reads the analog value from the LDR and displays the value on the OLED and Serial Monitor.

The reading changes depending on the amount of light reaching the sensor.

---

## 🖥️ OLED Display

The OLED display uses I2C communication.

Connections:

- SDA → GPIO 21
- SCL → GPIO 22

The OLED displays information such as:

```text
Temp : 29.0 C
Hum  : 60.0 %
Light: 4095
Status: NORMAL
