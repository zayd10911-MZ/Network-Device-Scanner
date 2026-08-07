# 🌐 ESP32 Network Device Scanner

An IoT-based Network Device Scanner developed using the **ESP32** and a **0.96" SSD1306 OLED Display**. This project scans the local Wi-Fi network, detects active devices using ICMP Ping, and displays the detected IP addresses on the OLED display while also printing detailed results to the Serial Monitor.

---

## 📖 Overview

This project demonstrates basic network discovery using an ESP32 microcontroller. Once powered on, the device connects to a Wi-Fi network, scans every IP address within the local subnet, identifies active hosts that respond to Ping requests, and displays the results on an OLED display.

---

## ✨ Features

- 📶 Connects to a Wi-Fi network
- 🔍 Scans the local subnet (1–254 IP addresses)
- 📡 Detects active devices using ICMP Ping
- 📺 Displays scan progress on OLED
- 📋 Shows detected IP addresses
- 💻 Prints results to the Serial Monitor
- 🔄 Automatically rescans the network

---

## 🛠 Hardware Requirements

- ESP32 Development Board
- 0.96" OLED Display (SSD1306 I2C)
- USB Cable
- Jumper Wires
- Breadboard (Optional)

---

## 📦 Software Requirements

- Arduino IDE
- ESP32 Board Package
- ESP32Ping Library
- Adafruit GFX Library
- Adafruit SSD1306 Library

---

## 🔌 Circuit Connections

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---



## 🚀 Installation

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/ESP32-Network-Device-Scanner.git
```

### 2. Open the Project

Open the `.ino` file using **Arduino IDE**.

### 3. Install Required Libraries

- ESP32Ping
- Adafruit GFX
- Adafruit SSD1306

### 4. Configure Wi-Fi

Replace:

```cpp
const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWRD";
```

with your Wi-Fi credentials.

### 5. Upload the Code

- Board: **ESP32 Dev Module**
- Select the correct COM Port
- Click **Upload**

---

## ⚙️ How It Works

1. ESP32 powers on.
2. Startup screen appears on the OLED.
3. Connects to the configured Wi-Fi network.
4. Scans all IP addresses on the local subnet.
5. Sends Ping requests to each IP.
6. Saves all responsive IP addresses.
7. Displays scan progress.
8. Shows detected IP addresses.
9. Automatically repeats the scan.

---

## 📺 OLED Display

### Startup

```text
ESP32

Network Device
Scanner
```

### Connecting

```text
Connecting WiFi...
```

### Scanning

```text
Network Scanner

Scanning...
```

### Scan Complete

```text
Scan Complete

Devices: 3
```

### Detected Device

```text
Detected Device

192.168.1.5
```

---

## 💻 Serial Monitor Output

```text
================================
Scanning Local Network...
================================

Checking: 192.168.1.1
Device Found -> 192.168.1.1

Checking: 192.168.1.2

Checking: 192.168.1.3

Checking: 192.168.1.4
Device Found -> 192.168.1.4

==============================
Total Devices Found: 2
==============================

