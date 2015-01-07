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

// Define variables and constants
//


/**
	Onewire bus on Arduino pin 3 // NEED FIX IN REAL BOARD
 */
#define ONE_WIRE_BUS 3

/**
	RTC object for Real Time Clock
 */
RTC_DS1307 rtc;

/**
	OneWire object // sensors Object
 */
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/**
	String to define log file name
 */
String FileNameString;

/**
	RTC object holding date-time
 */
DateTime now;


 
/**
	Sketch setup
	@param  none
 */
void setup()
 {
     // start serial port
     Serial.begin(9600);
     Serial.println("Dallas Temperature IC Test");
     
     // Start up the library
     sensors.begin();
     }


/**
	Sketch loop
	@param  none
 */
void loop()
 {
     
      }
