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
String humid0;;
String humid1;
String humid2;
String humid3;
String temp0;
String temp1;
String temp2;
String temp3;

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
      humid0 = str_humid[0];
      humid1 = humid0 + str_humid[1];
      humid2 = humid1 + str_humid[2];
      humid3 = humid2 + str_humid[3];

      temp0 = str_temp[0];
      temp1 = temp0 + str_temp[1];
      temp2 = temp1 + str_temp[2];
      temp3 = temp2 + str_temp[3];
      
      
      // Print values to Serial Monitor
      /*Serial.print("Humidity: ");
      Serial.print(humid3);    
      Serial.print("  - Temperature: ");
      Serial.println(temp3);*/

       // Print Humidity to OLED display
      oled.clear();
      oled.print("Henk Oegema");
      oled.set2X();
      oled.setCursor(0,2);
      oled.print("Humid:");
      oled.print(humid3);
      oled.setCursor(0,5);
      oled.print("Temp:");
      oled.print(temp3);
      
    }
}
