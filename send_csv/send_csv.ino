/*
Sending Data to Processing via the Serial Port.
This sketch sends data read from an ADS1115 ADC over a serial connection. 
Due to limited RAM and battery power this Arduino code is extremely minimal, it simply reads data and forwards it over the serial connection.
The receiver end is responsible for timestamping, storing, and otherwise handling the data.
*/
 
#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h> // Ensure library is installed. Download at https://github.com/adafruit/Adafruit_ADS1X15

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
// multiplier to convert from raw result to votlage value. Based on gain and output range of ADC results
float multiplier = 6.144/(32768.0); /* ADS1115  @ +/- 6.144V gain (16-bit results) */

// Setup run once on startup
void setup(void)
{
  // Setup a UART connection with 9600 baud rate
  Serial.begin(9600);
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  //
  // Input range is ±5V thus default gain of ±6.144V is used.

  // Initialise the ADC
  ads.begin();
}
 
// Main loop that is continually run during operation
void loop(){
  // Single-shot differential reading
  int16_t result = ads.readADC_Differential_0_1();  
  // Send raw result of reading (0-2^16-1)
  Serial.print(result);
  Serial.print(", "); // data is comma seperated
  Serial.println(result * multiplier); // Send converted voltage value
  delay(100); // Wait 100ms between readings
}
