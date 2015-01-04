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

#include <SD.h>
#include <Wire.h>
#include "RTClib.h"

// Define variables and constants
//


/**
	SD card chipselect pin (10 for adafruit SD datalogger shield)
 */
#define chipSelectPin 10


/**
	SD card object
 */
SDClass SD1;

/**
	RTC object for Real Time Clock
 */
RTC_DS1307 rtc;

 
/**
	Sketch setup
	@param  none
 */
void setup()
 {
    
     //Start serial
     
     Serial.begin(9600);
     
     // Start Wire lib
     Wire.begin();
     
     // Start RTC lib
     rtc.begin();
     
     // Adjust RTC clock if its not running ( ie no batt )
     if (! rtc.isrunning()) {
         Serial.println("RTC is NOT running: adjusting...");
         // following line sets the RTC to the date & time this sketch was compiled
         rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
     }
     
     
     pinMode(chipSelectPin, OUTPUT);
    
     if(!SD1.begin(chipSelectPin)){
         
         Serial.println("SD not init");
     }

 
}


/**
	Sketch loop
	@param  none
 */
void loop()
 {
     DateTime now = rtc.now();
     
     Serial.print(now.year(), DEC);
     Serial.print('/');
     Serial.print(now.month(), DEC);
     Serial.print('/');
     Serial.print(now.day(), DEC);
     Serial.print(' ');
     Serial.print(now.hour(), DEC);
     Serial.print(':');
     Serial.print(now.minute(), DEC);
     Serial.print(':');
     Serial.print(now.second(), DEC);
     Serial.print("\r");
 }
