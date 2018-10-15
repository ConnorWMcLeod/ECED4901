/*
Sending Data to Processing via the Serial Port
This sketch provides a basic framework to send data from Arduino to Processing over a Serial Port. This is a beginning level sketch.
 
Hardware:
* Sensors connected to Arduino input pins
* Arduino connected to computer via USB cord
 
Software:
*Arduino programmer
*Processing (download the Processing software here: https://www.processing.org/download/
 
Additional Libraries:
*Read about the Software Serial library here: http://arduino.cc/en/Reference/softwareSerial
 
Created 12 November 2014
By Elaine Laguerta
http://url/of/online/tutorial.cc
*/
 
/*To avoid overloading the Arduino memory, and to encourage portability to smaller microprocessors, this sketch
does not timestamp or transform data. In this tutorial, timestamping data is handled on the processing side.
 
Whether you process data on the Arduino side is up to you. Given memory limitations of the Arduino, even a few computations and mapping of values can
max out the memory and fail. I recommend doing as little as possible on the Arduino board.*/
 
#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
/* Be sure to update this value based on the IC and the gain settings! */
float multiplier = 6.144/(32768.0); /* ADS1115  @ +/- 6.144V gain (16-bit results) */

void setup(void)
{
  // 9600 baud rate
  Serial.begin(9600);
  
  //Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  //Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
}
 
//
void loop(){
  int16_t result = ads.readADC_Differential_0_1();  
  Serial.print(result);
  Serial.print(", ");
  Serial.println(result * multiplier);
  delay(100);
}
