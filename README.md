````
# Smart Walking Stick using ESP32 and Ultrasonic Sensors

An assistive smart walking stick designed to help visually impaired users detect obstacles, water, and ground-level hazards while providing audio and voice-based alerts.

## 📌 Project Overview

The Smart Walking Stick uses an ESP32 microcontroller as the main processing unit. Multiple ultrasonic sensors are used to detect obstacles in different directions, while a soil moisture sensor detects water on the ground.

The system provides alerts through a buzzer and communicates obstacle information to a mobile application using Bluetooth. The mobile application can provide voice-based assistance using text-to-speech.

An emergency button is also included. When pressed, the system obtains the user's GPS location and sends an emergency message containing a Google Maps location link through Telegram.

## ✨ Features

- Front obstacle detection
- Left-side obstacle detection
- Right-side obstacle detection
- Ground-level hole detection
- Water detection
- Distance-based buzzer alerts
- Bluetooth communication with mobile application
- Voice assistance through MIT App Inventor
- GPS-based emergency location
- Emergency button
- Telegram emergency notification
- ESP32-based real-time processing

## 🧠 System Architecture

The ESP32 acts as the central controller of the system.

It receives input from:

- Four ultrasonic sensors
- Soil moisture sensor
- Emergency button
- GPS module

It provides output through:

- Buzzer
- Bluetooth communication
- Telegram emergency notification

The overall system combines sensing, processing, alert generation, mobile communication, and emergency location sharing.

## 🔧 Hardware Components

- ESP32
- 4 × HC-SR04 Ultrasonic Sensors
- Soil Moisture Sensor
- NEO-6M GPS Module
- Passive Buzzer
- Emergency Push Button
- Battery Pack
- Buck Converter
- Connecting Wires
- Smart Walking Stick Structure

## 💻 Software and Technologies

- Arduino IDE
- Embedded C / Arduino C++
- ESP32
- Bluetooth Serial
- MIT App Inventor
- GPS
- Wi-Fi
- Telegram Bot API

### Libraries Used

```cpp
TinyGPS++
WiFi
WiFiClientSecure
UniversalTelegramBot
BluetoothSerial
````

## 📍 ESP32 Pin Configuration

| Component             | ESP32 Pin |
| --------------------- | --------: |
| Emergency Button      |    GPIO 4 |
| Soil Moisture Sensor  |   GPIO 34 |
| Buzzer                |   GPIO 27 |
| Front Ultrasonic TRIG |   GPIO 19 |
| Front Ultrasonic ECHO |   GPIO 21 |
| Left Ultrasonic TRIG  |    GPIO 5 |
| Left Ultrasonic ECHO  |   GPIO 18 |
| Right Ultrasonic TRIG |   GPIO 25 |
| Right Ultrasonic ECHO |   GPIO 26 |
| Down Ultrasonic TRIG  |   GPIO 22 |
| Down Ultrasonic ECHO  |   GPIO 23 |
| GPS RX                |   GPIO 16 |
| GPS TX                |   GPIO 17 |

## ⚙️ Working Principle

### 1. Obstacle Detection

The front, left, and right ultrasonic sensors continuously measure the distance to nearby obstacles.

When an obstacle is detected within 30 cm, the system identifies its direction and sends the information through Bluetooth to the mobile application.

The closest detected obstacle is also used to determine the buzzer alert level.

### 2. Buzzer Alert

The buzzer provides different alert patterns depending on the closest detected obstacle.

| Distance        | Alert                    |
| --------------- | ------------------------ |
| 20–30 cm        | Medium-frequency alert   |
| 10–19 cm        | High-frequency alert     |
| Less than 10 cm | Repeated emergency alert |

The buzzer also provides alerts for water and ground-level hazards.

### 3. Water Detection

The soil moisture sensor is used to detect water on the ground.

When the sensor reading crosses the configured threshold, the system reports:

```text
Water detected
```

and activates the buzzer.

### 4. Hole Detection

The downward-facing ultrasonic sensor monitors the ground area below the stick.

When the measured distance from the downward-facing ultrasonic sensor is greater than 0 cm and less than 25 cm, the system detects a ground-level hazard and reports:

```text
Hole detected   

### 5. Bluetooth and Voice Assistance

The ESP32 communicates with the mobile application using Bluetooth.

The system sends messages such as:

```text
Obstacle is detected at front
Obstacle is detected at left
Obstacle is detected at right
```

The MIT App Inventor application can use text-to-speech to provide voice assistance to the user.

### 6. Emergency Location System

When the emergency button is pressed:

1. Bluetooth communication is temporarily stopped.
2. Wi-Fi is enabled.
3. GPS data is read.
4. The current latitude and longitude are obtained when valid GPS data is available.
5. An emergency message containing a Google Maps location link is sent through Telegram.
6. Wi-Fi is disabled.
7. Bluetooth communication is started again.

Example message format:

```text
EMERGENCY
https://maps.google.com/?q=LATITUDE,LONGITUDE
```

## 📱 Mobile Application

The mobile application was developed using MIT App Inventor.

It communicates with the ESP32 through Bluetooth and provides voice-based information about detected obstacles.

The application interface is included in:

```text
Mobile-App/
```

## 📂 Project Structure

```text
Smart-Walking-Stick-ESP32/
│
├── README.md
│
├── Code/
│   └── Smart_Walking_Stick/
│       └── Smart_Walking_Stick.ino
│
├── Documentation/
│   └── Smart_Walking_Stick_Report.pdf
│
├── Images/
│
├── Diagrams/
│
└── Mobile-App/
    └── MIT App Interface
```

## 🚀 How to Run

### Step 1 — Install Arduino IDE

Install Arduino IDE and configure the ESP32 development board.

### Step 2 — Install Required Libraries

Install the required libraries used by the project:

* TinyGPS++
* UniversalTelegramBot

The Wi-Fi and Bluetooth libraries are provided through the ESP32 Arduino framework.

### Step 3 — Open the Project

Open:

```text
Code/Smart_Walking_Stick/Smart_Walking_Stick.ino
```

using Arduino IDE.

### Step 4 — Configure Credentials

Before uploading the code, replace the placeholder values with your own credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"
```

**Never commit real Wi-Fi passwords or Telegram bot tokens to GitHub.**

### Step 5 — Select ESP32 Board

Select the appropriate ESP32 board and COM port in Arduino IDE.

### Step 6 — Upload

Connect the ESP32 to the computer and upload the program.

## 🧪 Testing

The project was tested for:

* Front obstacle detection
* Left obstacle detection
* Right obstacle detection
* Ground-level hazard detection
* Water detection
* Buzzer alerts
* Bluetooth communication
* Mobile application response
* GPS location acquisition
* Emergency button operation
* Telegram emergency notification

## 📷 Project Images

The `Images` folder contains photographs and testing outputs of the completed Smart Walking Stick.

These include:

* Prototype views
* Obstacle detection outputs
* Serial Monitor results
* Water detection
* Hole detection
* GPS location testing

## 📐 System Diagrams

The `Diagrams` folder contains:

* System Architecture
* Use Case Diagram
* Class Diagram
* Data Flow Diagram
* Activity Diagram

## 📄 Documentation

The complete project report is available in:

```text
Documentation/Smart_Walking_Stick_Report.pdf
```

## 🔮 Future Enhancements

Possible future improvements include:

* Improved obstacle classification
* More advanced navigation assistance
* Better outdoor positioning
* Compact PCB-based hardware
* Improved power management
* Additional communication methods
* Improved mobile application features

## 👨‍💻 Project

**Smart Walking Stick using ESP32 and Ultrasonic Sensors**

Developed as a major project for:

**B.Tech — Computer Science and Engineering (Artificial Intelligence & Machine Learning)**

**Rajeev Gandhi Memorial College of Engineering and Technology (RGMCET), Nandyal**

Academic Year: **2025–2026**

## 📜 License

This project is provided for educational and academic purposes.

````

### 2. Save the file

After pasting:

```text
Ctrl + S
````

