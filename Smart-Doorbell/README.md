🔔 Embedded IoT Doorbell System Using ESP32

📌 Project Overview

The Embedded IoT Doorbell System Using ESP32 is an IoT-based doorbell system that integrates physical hardware with a Wi-Fi-enabled web interface.

When the push button is pressed, the ESP32 detects the input and activates the buzzer and blue LED. The OLED display provides local status information, while the ESP32 hosts a web page that can be accessed through the device's IP address over the same Wi-Fi network.

This project demonstrates the integration of embedded systems, GPIO control, I²C communication, OLED display, Wi-Fi connectivity, and web server functionality using the ESP32.

---

✨ Key Features

- Push-button doorbell input
- Blue LED indication
- Buzzer alert
- OLED status display
- ESP32 Wi-Fi connectivity
- ESP32-based web interface
- Real-time doorbell status
- Breadboard-based hardware prototype

---

🧰 Hardware Components

Component| Purpose
ESP32 Dev Module| Main microcontroller
Push Button| Detects doorbell press
Blue LED| Visual indication
Buzzer| Audible alert
OLED Display| Displays doorbell status
Breadboard| Circuit prototyping
Jumper Wires| Electrical connections
USB Cable| Programming and power

---

🔌 Circuit Connections

Component| ESP32 Pin
Push Button| GPIO 23
Blue LED| GPIO 25
Buzzer| GPIO 18
OLED SDA| GPIO 21
OLED SCL| GPIO 22
OLED VDD| 3.3V
OLED GND| GND

Push Button Configuration

The push button is connected using the ESP32's internal pull-up resistor.

The button is connected between GPIO 23 and GND.

The input therefore normally reads:

- Button released → "HIGH"
- Button pressed → "LOW"

The internal pull-up keeps the GPIO at a stable HIGH level when the button is not pressed and prevents a floating input.

---

🖥️ OLED Display

The OLED communicates with the ESP32 using the I²C communication protocol.

The I²C connections are:

- SDA → GPIO 21
- SCL → GPIO 22
- VDD → 3.3V
- GND → GND

The OLED is used to display the current doorbell status locally.

---

⚙️ How the System Works:
Normal State

When the push button is not pressed:

- Blue LED → OFF
- Buzzer → OFF
- OLED → Doorbell ready/status
- Web page → Doorbell ready

Doorbell Pressed

When the push button is pressed:

- ESP32 detects a LOW input
- Blue LED → ON
- Buzzer → ON
- OLED → Doorbell alert
- Web page → Doorbell pressed/visitor indication

When the button is released, the system returns to its normal state.

---

📶 Wi-Fi Functionality

The ESP32 connects to a configured Wi-Fi network using the network name (SSID) and password stored in the program.

After successfully connecting, the ESP32 obtains an IP address from the network.

The IP address can then be entered into a browser connected to the same network to access the embedded IoT doorbell web interface.

Example:

ESP32 IP Address
      ↓
Web Browser
      ↓
Embedded IoT Doorbell Web Page

---

🌐 Web Interface

The ESP32 runs a lightweight web server that provides a browser-based doorbell interface.

The web page displays information such as:

- Embedded IoT Doorbell title
- Connection/device status
- Doorbell ready state
- Doorbell alert state
- ESP32 Wi-Fi information

This allows the physical doorbell system to be monitored through a web browser.

---

💻 Software

Development Environment

- Arduino IDE
- ESP32 board package

Programming Language

- C/C++ (Arduino framework)

Main Technologies

- ESP32 GPIO
- I²C
- Wi-Fi
- Embedded Web Server
- OLED display
- Digital input/output

---

🚀 How to Run

1. Connect the ESP32 to the computer using USB.
2. Open the project source file in Arduino IDE.
3. Select the correct ESP32 board.
4. Select the correct COM port.
5. Enter the Wi-Fi SSID and password in the code.
6. Upload the program to the ESP32.
7. Open the Serial Monitor.
8. Set the Serial Monitor baud rate according to the program.
9. Wait for the ESP32 to connect to Wi-Fi.
10. Note the IP address displayed by the ESP32.
11. Enter the IP address into a browser connected to the same network.
12. Press the physical doorbell button and observe the hardware and web interface response.

---

📸 Project Images

Complete Project Setup

Circuit Wiring

OLED — Ready State

OLED — Alert State

Web Interface — Ready State

Web Interface — Alert State

---

🎥 Project Demonstration

The demonstration video is available in the "video" folder.

Video: "working_prototype_smart_doorbell.mp4"

The demonstration shows the working hardware, doorbell button, LED, buzzer, OLED display, Wi-Fi connection, and web interface.

---

🧠 Concepts Learned

Through this project, the following concepts were practiced:

- ESP32 GPIO configuration
- Digital input and output
- Internal pull-up resistor
- Push-button interfacing
- LED control
- Buzzer control
- I²C communication
- OLED display interfacing
- Wi-Fi connectivity
- IP addressing
- Embedded web server
- Browser-based device monitoring
- Hardware and software integration
- Debugging using Serial Monitor

---

🛠️ Troubleshooting

Wi-Fi does not connect

Check:

- Wi-Fi SSID
- Wi-Fi password
- 2.4 GHz network availability
- ESP32 power/USB connection
- Serial Monitor output

Doorbell stays active

Check the push-button wiring and confirm that the GPIO is configured using the intended pull-up configuration.

OLED does not display correctly

Check:

- SDA connection
- SCL connection
- VDD
- GND
- OLED I²C address
- I²C library configuration

Web page cannot be opened

Check that:

- ESP32 is connected to Wi-Fi.
- The IP address is correct.
- The computer/phone is connected to the same network.
- The ESP32 web server has started successfully.

---

🔮 Future Improvements

Possible future enhancements include:

- Mobile-friendly web interface
- Doorbell event logging
- Notification system
- Camera integration
- Visitor image capture
- Bluetooth/BLE functionality
- Cloud connectivity
- Mobile application integration

---

🎯 Project Objective

The main objective of this project is to understand how an ESP32 can integrate physical inputs, electronic outputs, a display, Wi-Fi communication, and a web interface into a single embedded IoT system.

---

👩‍💻 Project Information

Project Title: Embedded IoT Doorbell System Using ESP32

Student: Sathya Priya
Department: Electronics and Communication Engineering

This project was developed as an embedded systems and IoT learning project using the ESP32.
