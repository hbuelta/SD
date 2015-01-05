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
	RTC object for Real Time Clock
 */
RTC_DS1307 rtc;

/**
	SD File handler
 */
File sdFile;

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
    
     //Start serial
     
     Serial.begin(9600);
     
     // Start Wire lib
     Wire.begin();
     
     // Start RTC lib
     rtc.begin();
     
     // Adjust RTC clock if its not running ( ie no batt )
     if (!rtc.isrunning()) {
         Serial.println("RTC is NOT running: adjusting...");
         // following line sets the RTC to the date & time this sketch was compiled
         rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
     }
     
     
     // CS pin ( pin 10 on most boards) MUST to be st to uotput (even when using another pin por CS)
     pinMode(chipSelectPin, OUTPUT);
    
     if(!SD.begin(chipSelectPin)){
         
         Serial.println("SD not init....exiting");
         return;
     }
     
     now=rtc.now();
     
     // Assign a name to log file : DD/MM/YYYY-HH:MM:SS ( and some needed conversion from String object to char*
     // TODO: find a suitable 8.3 log file naming scheme
     FileNameString=String(now.day())+String(now.month())+".txt";
     int str_len = FileNameString.length() + 1;
     char sdFileName[str_len];
     FileNameString.toCharArray(sdFileName, str_len);
     sdFile = SD.open(sdFileName, FILE_WRITE);
     sdFile.close(); // close it...just for testing
     if(SD.exists(sdFileName)){
         Serial.print("File:");
         Serial.print(sdFileName);
         Serial.print(" opened on SD card");
         Serial.println();
     }
}


/**
	Sketch loop
	@param  none
 */
void loop()
 {
     
      }
