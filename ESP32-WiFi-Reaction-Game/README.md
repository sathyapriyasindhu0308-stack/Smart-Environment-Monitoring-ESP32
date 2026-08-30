## 📌 Project Overview

The **ESP32 Wi-Fi Reaction Game** is an embedded systems and IoT project developed using the ESP32 microcontroller.

The project is designed to test and measure a player's reaction time using a push button and visual indications. The ESP32 controls the game logic, detects the player's button response, calculates the reaction result, and displays the game information on an OLED display.

The project also demonstrates Wi-Fi connectivity and a browser-based web interface hosted by the ESP32. This allows the game information and device status to be accessed from another device connected to the same Wi-Fi network.

This project combines **embedded programming, GPIO control, OLED display interfacing, I²C communication, Wi-Fi connectivity, web server functionality, and real-time input processing**.

---

## ✨ Key Features

- ESP32-based reaction-time game
- Push-button player input
- LED visual indication
- OLED display for game information
- Reaction-time measurement
- Wi-Fi connectivity
- ESP32-hosted web interface
- Real-time game status
- Embedded hardware and software integration
- Breadboard-based prototype

---

## 🧰 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 Dev Module | Main microcontroller |
| OLED Display | Displays game status and results |
| Push Button | Player input |
| LED | Visual game indication |
| Breadboard | Circuit prototyping |
| Jumper Wires | Electrical connections |
| USB Cable | Programming and power |

---

## 🔌 Circuit Connections

The ESP32 is connected to the different components through its GPIO pins.

The OLED display communicates with the ESP32 using the **I²C communication protocol**.

Typical I²C connections are:

| OLED Pin | ESP32 Pin |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VDD | 3.3V |
| GND | GND |

The push button and LED are connected to GPIO pins configured in the program.

> The exact GPIO numbers for the button and LED should match the pin definitions in `ESP32_Wifi_Reaction_Game.ino`.

---

## 🖥️ OLED Display

The OLED display provides local feedback to the player.

It can be used to display information such as:

- Game title
- Game ready status
- Reaction prompt
- Reaction result
- Game status
- Player response

The OLED uses the **I²C interface**, which allows the ESP32 to communicate with the display using SDA and SCL lines.

---

## 🎮 How the Game Works

The basic operation of the reaction game is:

```text
Start Game
    ↓
ESP32 Initializes Hardware
    ↓
OLED Displays Game Information
    ↓
Waiting for Reaction Signal
    ↓
Visual Indication
    ↓
Player Presses Button
    ↓
ESP32 Detects Button Input
    ↓
Reaction Time Is Processed
    ↓
Result Displayed on OLED
    ↓
Game Status Available Through Wi-Fi
Normal State
When the game is waiting for the player:
LED → Normal/Waiting state
Button → Waiting for player input
OLED → Displays game status
ESP32 → Monitors the button input
Reaction Event
When the visual indication occurs:
The ESP32 starts the reaction measurement.
The player responds by pressing the push button.
The ESP32 detects the button press.
The reaction time is calculated.
The result is displayed on the OLED.
The game can continue with another round.
⏱️ Reaction-Time Measurement
The reaction time represents the time taken by the player to respond to the generated signal.
The ESP32 processes the timing between the visual indication and the player's button response.
Visual Signal
      ↓
Start Timing
      ↓
Player Presses Button
      ↓
Stop Timing
      ↓
Process Reaction Time
      ↓
Display Result
This demonstrates how a microcontroller can detect real-time input, process timing information, and provide immediate feedback.
📶 Wi-Fi Functionality
The ESP32 connects to a configured Wi-Fi network using the SSID and password defined in the program.
After successfully connecting, the ESP32 receives an IP address from the network.
The IP address can be entered into a browser connected to the same Wi-Fi network to access the reaction game web interface.
ESP32
  ↓
Wi-Fi Network
  ↓
ESP32 IP Address
  ↓
Web Browser
  ↓
Reaction Game Interface
🌐 Web Interface
The ESP32 hosts a lightweight web interface that allows the user to monitor the reaction game through a browser.
The interface provides information such as:
Reaction Game title
ESP32 connection status
Game status
Player response information
Reaction-time result
This demonstrates how an ESP32 can function as both an embedded controller and a Wi-Fi-enabled web server.
💻 Software and Technologies
Development Environment
Arduino IDE
ESP32 Board Package
Programming Language
C/C++
Arduino Framework
Technologies Used
ESP32 GPIO
Digital Input/Output
I²C Communication
OLED Display
Wi-Fi Networking
Embedded Web Server
Real-Time Input Processing
Serial Monitor Debugging
Libraries
The project uses libraries for:
ESP32 Wi-Fi communication
Web server functionality
OLED graphics
OLED display communication
🚀 How to Run
Connect the ESP32 to the computer using USB.
Connect the OLED display, push button, and LED according to the circuit configuration.
Open ESP32_Wifi_Reaction_Game.ino.
Enter the required Wi-Fi SSID and password in the program.
Select the appropriate ESP32 board and COM port.
Verify the hardware connections.
Upload the program to the ESP32.
Open the Serial Monitor.
Wait for the ESP32 to connect to Wi-Fi.
Note the IP address displayed by the ESP32.
Open the IP address in a browser connected to the same Wi-Fi network.
Start the reaction game.
Observe the LED, push button, OLED display, and web interface.
📁 Project Structure
ESP32-WiFi-Reaction-Game/
│
├── README.md
├── ESP32_Wifi_Reaction_Game.ino
│
├── images/
│   ├── circuit_setup
│   ├── oled_display
│   ├── reaction_game
│   └── web_interface
│
└── video/
    └── reaction_game_demo.mp4
📸 Project Images
The images folder contains photographs of the completed hardware prototype and project operation.
The images include:
Complete circuit setup
ESP32 and component connections
OLED display
LED indication
Push-button interaction
Game operation
Web interface
🎥 Project Demonstration
The demonstration video is stored in the video folder.
The video demonstrates:
ESP32 hardware setup
Push-button interaction
LED indication
OLED display feedback
Reaction-time operation
Wi-Fi connectivity
Web interface functionality
🧠 Concepts Learned
Through this project, the following concepts were practiced:
ESP32 microcontroller programming
GPIO configuration
Digital input and output
Push-button interfacing
LED control
I²C communication
OLED display interfacing
Real-time input processing
Reaction-time measurement
Wi-Fi connectivity
IP addressing
Embedded web server development
Browser-based device monitoring
Hardware-software integration
Serial Monitor debugging
🔮 Future Improvements
Possible future enhancements include:
High-score storage
Multiple game modes
Difficulty levels
Reaction-time history
Scoreboard functionality
Improved web dashboard
Mobile-friendly web interface
Multiplayer functionality
Data logging
Cloud-based result storage
🎯 Project Objective
The main objective of this project is to demonstrate how an ESP32 can integrate user input, real-time processing, visual feedback, OLED communication, Wi-Fi networking, and web-based monitoring into a single embedded IoT application.
👩‍💻 Project Information
Project Title: ESP32 Wi-Fi Reaction Game
Student: Sathyapriya
Department: Electronics and Communication Engineering
