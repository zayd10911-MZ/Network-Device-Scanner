#include <WiFi.h>
#include <ESP32Ping.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// =======================
// CHANGE THESE
// =======================
const char* ssid = "wifi_name";
const char* password = "Wifi_passwrd";

// =======================

IPAddress localIP;
IPAddress foundDevices[254];   // Stores detected IP addresses
int devicesFound = 0;

void showOLED(String line1, String line2)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,10);
  display.println(line1);

  display.setCursor(0,30);
  display.println(line2);

  display.display();
}
void scanNetwork()
{
  devicesFound = 0;
  localIP = WiFi.localIP();

  Serial.println();
  Serial.println("================================");
  Serial.println("Scanning Local Network...");
  Serial.println("================================");

  // Scan all IPs
  for (int i = 1; i <= 254; i++)
  {
    IPAddress testIP(localIP[0], localIP[1], localIP[2], i);

    // Show scanning progress
    int progress = (i * 100) / 254;

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0,0);
    display.println("Network Scanner");

    display.setCursor(0,12);
    display.print("Scanning ");
    display.print(progress);
    display.println("%");

    display.drawRect(5, 35, 118, 10, SSD1306_WHITE);
    display.fillRect(7, 37, progress, 6, SSD1306_WHITE);

    display.display();

    Serial.print("Checking: ");
    Serial.println(testIP);

    if (Ping.ping(testIP, 1))
    {
      foundDevices[devicesFound] = testIP;
      devicesFound++;

      Serial.print("Device Found -> ");
      Serial.println(testIP);
    }

    delay(2);
  }

  Serial.println();
  Serial.println("==============================");
  Serial.print("Total Devices Found: ");
  Serial.println(devicesFound);
  Serial.println("==============================");

  // Show scan complete
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Scan Complete");

  display.setCursor(0,15);
  display.print("Devices: ");
  display.println(devicesFound);

  display.display();

  delay(3000);

  // Show each IP address
  for (int i = 0; i < devicesFound; i++)
  {
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,0);
    display.println("Detected Device");

    display.setCursor(0,15);
    display.print(i + 1);
    display.print(" of ");
    display.println(devicesFound);

    display.setCursor(0,35);
    display.println(foundDevices[i]);

    display.display();

    delay(10000);
  }

  // Final screen
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("Network Scanner");

  display.setCursor(0,18);
  display.print("Devices Found:");

  display.setCursor(0,40);
  display.setTextSize(2);
  display.println(devicesFound);

  display.display();
}
void setup()
{
  Serial.begin(115200);

  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED Failed");
    while (1);
  }

  // Startup Screen
display.clearDisplay();
display.setTextColor(SSD1306_WHITE);

display.setTextSize(2);
display.setCursor(10,8);
display.println("ESP32");

display.setTextSize(1);
display.setCursor(5,35);
display.println("Network Device");

display.setCursor(28,48);
display.println("Scanner");

display.display();

delay(3000);

// Connecting Screen
display.clearDisplay();
display.setTextSize(1);
display.setCursor(10,25);
display.println("Connecting WiFi...");
display.display();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  showOLED("WiFi Connected", WiFi.localIP().toString());

  delay(2000);

  scanNetwork();
}

void loop()
{
  // Scan every 60 seconds
  delay(60000);
  scanNetwork();
}