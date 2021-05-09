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

#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

/*
#define I2C_ADDRESS 0x3c
#define RST_PIN -1
*/
SSD1306AsciiAvrI2c oled;

// Define output strings

String str_humid;
String str_temp;
String str_out;

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup()
{
    oled.begin(&Adafruit128x64, 0x3C);
    oled.setFont(Adafruit5x7);
    
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(2000000);
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
      oled.clear();
      oled.set1X();
      oled.print("Humidity: ");
      oled.print(str_humid);
      oled.println(" %");
      oled.print("Temperature: ");
      oled.print(str_temp);
      oled.println(" C");
    }
}
