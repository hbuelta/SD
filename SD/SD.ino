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
#include "EasyScheduler.h"

// local functions declaration

void printAddress(DeviceAddress deviceAddress);
void scheduledTask1Callback(void);

// Define variables and constants
//

#define LOWFREQTASK 1000

DeviceAddress sensor1Address;
Schedular scheduledTask1;

/**
	Onewire bus on Arduino pin 5 // NEED FIX IN REAL BOARD
 */
#define ONE_WIRE_BUS 5


/**
	OneWire object // sensors Object
 */
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


/**
	Sketch setuo
	@param  none
 */
void setup()
 {
     // start serial port
     Serial.begin(9600);
     Serial.println("Dallas Temperature Sensor Test");
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
     
     // start scheduling
     
     scheduledTask1.start();
 
 }



/**
	Sketch loop
	@param  none
 */
void loop()
 {
     scheduledTask1.check(scheduledTask1Callback, LOWFREQTASK);
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

/**
	Issues temp request to all sensors and Serial-display temperature for one sensor (hardcoded)
	@param  none
 */
void scheduledTask1Callback()

{
    sensors.requestTemperatures();
    Serial.print("TEMP for address:");
    printAddress(sensor1Address);
    Serial.print(": ");
    Serial.print(sensors.getTempC(sensor1Address));
    Serial.print("\n");
}






