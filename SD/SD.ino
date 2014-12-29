// 
// SD 
//
// Description of the project
// Developed with [embedXcode](http://embedXcode.weebly.com)
// 
// Author	 	Hector Buelta
// 				Hector Buelta
//
// Date			21/12/14 16:34
// Version		0.1
// 
// Copyright	© Hector Buelta, 2014
// Licence		<#license#>
//
// See			ReadMe.txt for references
//


#include "Arduino.h"


// Include application, user and local libraries

#include "OneWire.h"
#include "DallasTemperature.h"

// local functions declaration

void printAddress(DeviceAddress deviceAddress);

// Define variables and constants
//

// Always will access sensors by its DeviceAddress

DeviceAddress sensor1Address;

/**
	Onewire bus on Arduino pin 5 // NEED FIX IN REAL BOARD
 */
#define ONE_WIRE_BUS 5


/**
	OneWire object // sensors Object
 */
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//
// Brief	Setup


// Add setup code 
/**
	Sketch setuo
	@param  none
 */
void setup()
 {
     // start serial port
     Serial.begin(9600);
     Serial.println("Dallas Temperature IC Test");
     Serial.print("\n");
     
     // Start up the library
     
     sensors.begin();
     //Requesting how many sensors
     
     Serial.print("Number of sensors in bus: ");
     Serial.print(sensors.getDeviceCount(), DEC);
     Serial.print("\n");
     
     //Get address of first sensor in bus (index 0)
     
     sensors.getAddress(sensor1Address, 0);
     
     //Print address of first sensor (index 0)
     
     Serial.print("Sensor 1 HEX Address: ");
     printAddress(sensor1Address);
     Serial.print("\n");
 
 }


// Add loop code
/**
	Sketch loop
	@param  none
 */
void loop()
 {
     Serial.print("TEMP for address:");
     printAddress(sensor1Address);
     Serial.print("= ");
     Serial.print(sensors.getTempC(sensor1Address));
     delay(2000);
}

//Local functions

/**
	Print HEX representation of a OneWire object Address
	@param deviceAddress deviceAddress object to print
 */
void printAddress(DeviceAddress deviceAddress)

{
    for (uint8_t i = 0; i < 8; i++)
    {
        // zero pad the address if necessary
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
}