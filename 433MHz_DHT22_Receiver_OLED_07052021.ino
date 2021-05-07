/*
  433 MHz RF Module Receiver Demonstration 2
  RF-Rcv-Demo-2.ino
  Demonstrates 433 MHz RF Receiver Module with DHT-22 Sensor
  Use with Transmitter Demonstration 2

  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

/* Added OLED display */

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define output strings

String str_humid;
String str_temp;
String str_out;

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(2000000);

    display.begin(SSD1306_SWITCHCAPVCC,0x3C);  // Address 0x3C for 128x64
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay(); // Clear display buffer
}

void loop()
{
    
    
    // Set buffer to size of expected message
    uint8_t buf[11];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      
      // Message received with valid checksum
      // Get values from string
      
      // Convert received data into string
      str_out = String((char*)buf);
      
      // Split string into two values
      for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
      str_humid = str_out.substring(0, i);
      str_temp = str_out.substring(i+1);
      break;
      }
    }
      
      // Print values to Serial Monitor
      Serial.print("Humidity: ");
      Serial.print(str_humid);
      Serial.print("  - Temperature: ");
      Serial.println(str_temp);
      
      
      // Print Humidity to OLED display
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0,0);
      display.print("Humidity: ");
      display.print(str_humid);
      display.print(" %");
      display.println();     
      display.display();
      
    }
}
