Smart Environment Monitoring and Alert System using ESP32

📌 Project Overview

The Smart Environment Monitoring and Alert System is an ESP32-based embedded system designed to monitor environmental conditions in real time.

The system uses a DHT11 sensor to measure temperature and humidity and an LDR (Light Dependent Resistor) to monitor the surrounding light level.

The collected sensor readings are displayed on an I2C OLED display and are also printed to the Serial Monitor.

The system provides visual and audio indications according to the configured environmental status:

- 🟢 NORMAL — Green LED
- 🟡 WARNING — Yellow LED
- 🔴 CRITICAL — Red LED and buzzer

The project demonstrates practical embedded-system concepts such as sensor interfacing, analog and digital GPIO control, I2C communication, OLED display control, threshold-based decision making, LED indication, buzzer alerts, Serial Monitor debugging, and hardware integration.

---

🎯 Objectives

The main objectives of this project are:

- To interface multiple sensors with an ESP32.
- To measure temperature and humidity using a DHT11 sensor.
- To monitor light levels using an LDR.
- To display real-time sensor readings using an OLED display.
- To classify environmental conditions using configurable threshold values.
- To provide visual status indication using LEDs.
- To provide an audio alert during a critical condition.
- To monitor sensor values through the Serial Monitor.
- To develop, test, and demonstrate a complete embedded-system prototype.

---

🧰 Components Used

Component| Quantity| Purpose
ESP32 Development Board| 1| Main microcontroller
DHT11 Sensor| 1| Temperature and humidity measurement
LDR| 1| Light-level measurement
I2C OLED Display| 1| Display sensor readings and status
Green LED| 1| Normal status indication
Yellow LED| 1| Warning status indication
Red LED| 1| Critical status indication
3-Pin Buzzer| 1| Audio alert
Resistors| As required| LED/circuit protection
Breadboard| 1| Circuit prototyping
Jumper Wires| As required| Electrical connections
USB Cable| 1| Programming and power

---

🔌 Pin Connections

Component| ESP32 GPIO
DHT11 DATA| GPIO 4
LDR| GPIO 34
Green LED| GPIO 25
Yellow LED| GPIO 26
Red LED| GPIO 27
Buzzer Signal| GPIO 18
OLED SDA| GPIO 21
OLED SCL| GPIO 22

Power Connections

- DHT11 VCC → ESP32 3.3V
- OLED VCC → ESP32 3.3V
- Sensor and OLED GND → ESP32 GND
- LEDs are connected through appropriate resistors.

---

⚙️ How the System Works

When the ESP32 is powered ON, the system initializes the DHT11 sensor, LDR, OLED display, LEDs, and buzzer.

The ESP32 periodically reads:

- Temperature
- Humidity
- Light level

The readings are then:

1. Displayed on the OLED.
2. Printed to the Serial Monitor.
3. Compared with the configured threshold values.
4. Used to determine the current system status.
5. Used to control the corresponding LED.
6. Used to activate the buzzer during a critical condition.

The monitoring process continues continuously while the ESP32 is running.

---

🚦 Environmental Status

The system determines the environmental status by comparing the measured temperature and humidity values with threshold values defined in the Arduino code.

🟢 NORMAL

The system displays NORMAL when the measured values are within the configured normal range.

Output:

- Green LED → ON
- Yellow LED → OFF
- Red LED → OFF
- Buzzer → OFF

---

🟡 WARNING

The system displays WARNING when the configured warning condition is detected.

Output:

- Green LED → OFF
- Yellow LED → ON
- Red LED → OFF
- Buzzer → OFF

---

🔴 CRITICAL

The system displays CRITICAL when the configured critical condition is detected.

Output:

- Green LED → OFF
- Yellow LED → OFF
- Red LED → ON
- Buzzer → ON

---

🧪 Threshold Demonstration

During testing and video demonstration, the threshold values in the Arduino code were manually adjusted to demonstrate the Normal, Warning, and Critical states.

Example demonstration values used during testing included:

- Normal demonstration: Temperature 30°C and Humidity 35%
- Warning demonstration: Temperature below 25°C and Humidity below 30%
- Critical demonstration: Temperature below 25°C and Humidity below 27%

These values are demonstration/testing values, not fixed environmental safety limits.

The thresholds can be changed in the Arduino code according to the requirements of a particular application.

---

💡 LDR Light Monitoring

The LDR is connected to GPIO 34, which is used as an analog input.

The ESP32 reads the analog value from the LDR and displays the reading on the OLED and Serial Monitor.

The LDR reading changes according to the amount of light falling on the sensor.

Example:

Light Level : 4095

The actual reading depends on the lighting conditions and the LDR circuit configuration.

---

🖥️ OLED Display

The OLED communicates with the ESP32 using the I2C protocol.

I2C Connections

OLED SDA → GPIO 21
OLED SCL → GPIO 22

The display provides real-time information such as:

Temp : 29.0 C
Hum  : 60.0 %
Light: 4095
Status: NORMAL

---

🖥️ Serial Monitor

The Serial Monitor is used to observe real-time sensor readings and system status.

The program uses:

115200 baud

Example output:

----------------------------
Temperature : 29.0 C
Humidity    : 60.0 %
Light Level : 4095
Status      : NORMAL

The Serial Monitor was also useful during development for checking sensor readings and troubleshooting the hardware.

---

🔊 Buzzer Alert

The buzzer is connected to GPIO 18.

During a critical condition, the buzzer produces an intermittent audio alert.

The programmed alert pattern is approximately:

Buzzer ON  → 1 second
Buzzer OFF → 4 seconds

The buzzer was also tested independently during hardware testing to verify that it was functioning correctly.

---

🛡️ Sensor Error Detection

The program checks whether valid temperature and humidity readings are received from the DHT11 sensor.

If an invalid DHT11 reading is detected, the system enters a SENSOR ERROR state.

In this condition:

- The red LED indicates the error.
- The OLED displays a sensor-error message.
- The system does not treat the invalid DHT11 reading as a normal environmental reading.

Example OLED message:

Status: SENSOR ERR
Check DHT11!

---

🔄 System Flow

START
  |
  v
Initialize ESP32
  |
  v
Initialize DHT11, LDR, OLED,
LEDs and Buzzer
  |
  v
Read Temperature
Humidity and Light
  |
  v
Determine System Status
  |
  +---------+---------+
  |         |         |
  v         v         v
NORMAL    WARNING   CRITICAL
  |         |         |
  v         v         v
GREEN     YELLOW      RED
                      |
                      v
                    BUZZER
  |
  v
Update OLED Display
  |
  v
Print Serial Data
  |
  v
Repeat

---

🧪 Testing and Validation

The prototype was tested component-by-component and then as a complete integrated system.

DHT11 Testing

Temperature and humidity readings were checked using the OLED display and Serial Monitor.

LDR Testing

The LDR was tested under different lighting conditions to verify that its analog reading changes according to the amount of light received.

LED Testing

The green, yellow, and red LEDs were individually tested to verify the required status indications.

Buzzer Testing

The buzzer was tested independently using a tone-generation test program and was then integrated into the main system for the critical condition.

OLED Testing

The OLED was tested to verify I2C communication and real-time display of sensor readings.

Integrated System Testing

After individual components were verified, the complete system was operated together to confirm the interaction between the sensors, OLED, LEDs, Serial Monitor, and buzzer.

---

📸 Project Images

Complete Prototype

"Project Overview" (images/01_project_overview.jpeg)

Circuit Wiring

"Circuit Wiring" (images/02_circuit_wiring.jpeg)

Normal Condition

"Normal Condition" (images/03_normal_led.jpeg)

Warning Condition

"Warning Condition" (images/04_warning_led.jpeg)

Critical Condition

"Critical Condition" (images/05_critical_led.jpeg)

«If your actual image filenames are different, replace the filenames above with the exact names in your "images" folder.»

---

🎥 Working Prototype Video

The complete working demonstration video is available in the "video" folder.

"▶️ View the Working Prototype Video" (video/working_prototype_smart_environment.mp4)

«GitHub may display a large MP4 file as a binary file instead of playing it directly on the repository page. The View Raw option can be used to access the uploaded video.»

---

💻 Software and Libraries

Development Environment

- Arduino IDE
- ESP32 Board Support Package
- Embedded C/C++

Libraries Used

- Wire
- Adafruit GFX
- Adafruit SSD1306
- DHT Sensor Library

---

🧠 Embedded Concepts Demonstrated

This project demonstrates practical knowledge of:

- ESP32 microcontroller programming
- Embedded C/C++
- GPIO programming
- Analog input
- Digital input/output
- DHT11 sensor interfacing
- LDR interfacing
- I2C communication
- OLED display programming
- LED control
- Buzzer control
- Threshold-based decision making
- State-based system behavior
- Serial communication
- Hardware debugging
- Breadboard prototyping
- Embedded-system integration

---

🛠️ Challenges and Troubleshooting

During development, the components were tested individually before being integrated into the complete system.

The troubleshooting process included:

- Verifying ESP32 GPIO connections.
- Testing LEDs individually.
- Testing the buzzer independently.
- Checking OLED I2C communication.
- Verifying DHT11 readings.
- Testing LDR response under different lighting conditions.
- Checking circuit and sensor connections.
- Using the Serial Monitor to observe real-time values.
- Adjusting demonstration thresholds to verify different system states.

This step-by-step testing process helped verify the operation of the individual components and the final integrated prototype.

---

🚀 Future Improvements

Possible future improvements include:

- Wi-Fi-based remote monitoring.
- Cloud-based data logging.
- Mobile notifications.
- Real-time sensor graphs.
- Additional environmental sensors.
- Automatic fan control.
- Automatic lighting control.
- PCB implementation.
- Protective hardware enclosure.
- Improved fault detection and diagnostics.

---

📁 Repository Structure

Smart-Environment-Monitoring-ESP32/
│
├── coding/
│   └── Smart_environment_Monitoring.ino
│
├── images/
│   ├── 01_project_overview.jpeg
│   ├── 02_circuit_wiring.jpeg
│   ├── 03_normal_led.jpeg
│   ├── 04_warning_led.jpeg
│   ├── 05_critical_led.jpeg
│   └── ...
│
├── video/
│   └── working_prototype_smart_environment.mp4
│
└── README.md

---

📚 Learning Outcomes

Through this project, I gained practical experience in:

- ESP32 programming
- Embedded C/C++
- Sensor interfacing
- Analog and digital GPIO handling
- I2C communication
- OLED display control
- LED and buzzer control
- Threshold-based control systems
- Hardware debugging
- Circuit prototyping
- Embedded-system integration
- Technical documentation

This project provided hands-on experience in developing an embedded system from individual component testing through integration, debugging, documentation, and final demonstration.

---

👩‍💻 Author

Sathyapriya

Electronics and Communication Engineering (ECE)

---

⭐ Project Summary

The Smart Environment Monitoring and Alert System using ESP32 is a compact embedded prototype that combines environmental sensing, real-time display, status classification, visual indication, and audio alerting.

The project demonstrates the practical integration of sensors, a microcontroller, OLED display, LEDs, buzzer, and embedded software into a complete working system.

It showcases hands-on experience in embedded systems, ESP32 programming, sensor interfacing, hardware debugging, circuit prototyping, system integration, and technical documentation.
