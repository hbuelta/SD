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
// USING HARDWARE TIMER1 FOR SCHEDULER ADVANCES


#include "Arduino.h"


// Include application, user and local libraries

#include "OneWire.h"
#include "DallasTemperature.h"
#include "Scheduler.h"
#include "TimerOne.h"

//local constants and macros

/**
	Onewire bus on Arduino pin 5 // NEED CORRECT ASSIGN IN ACTUAL BOARD
 */
#define ONE_WIRE_BUS 5
/**
	Timer1 set to 10ms (100Hz)
 */
#define HZ100 10000

// local functions declaration

void printAddress(DeviceAddress deviceAddress);
void timerCallbackScheduler(void);
void checkTemperature(void);

// Define variables and constants


/**
	Hardware Timer1 wrapper object
 */
TimerOne schedulerTimer;


/**
	Scheduler object that will advance 1 step every overflow of schedulerTimer
 */
Scheduler scheduler;


/**
	Temperature sensor unque address // Always will access sensors by its DeviceAddress
 */
DeviceAddress sensor1Address;

/**
	OneWire object // sensors Object
 */
OneWire oneWire(ONE_WIRE_BUS);

/**
    Dallas temperature sensor object
 */
DallasTemperature sensors(&oneWire);


/**
	Sketch setup code
	@param  none
 */
void setup()
 {
     // start serial port
     Serial.begin(9600);
     Serial.println("Dallas Temperature Sensor Test");
     Serial.print("\n");
     
     //Scheduler timer init
     schedulerTimer.initialize(HZ100);
     schedulerTimer.attachInterrupt(timerCallbackScheduler);
     
     //Scheduler init
     scheduler.createSchedule(100, -1, FALSE, checkTemperature);
     
     
     // Start up the sensor library
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
     scheduler.serviceScheduledEvents();
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
	Callback attached to schedulerTimer. Serve to advance scheduler
	@param  none
 */
void timerCallbackScheduler()
{
    // Calling this function will push the Scheduler forward by one tick.
   scheduler.advanceScheduler();
}
void checkTemperature()
{
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print("\r");
}
