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
// USING HARDWARE TIMER2 FOR SCHEDULER ADVANCES
// USING SCHEDULER.H which offer profiling and some other nice hooks

#include "Arduino.h"


// Include application, user and local libraries
#include <SD.h>
#include <Wire.h>

#include "OneWire.h"
#include "DallasTemperature.h"
#include "Scheduler.h"
#include "MsTimer2.h"
#include "RTClib.h"

//local constants and macros

/**
    SPI CS pin on adafruit SD logger shield\*/
#define chipSelectPin 10

/**
	Onewire bus on Arduino pin 5 // NEED CORRECT ASSIGN IN ACTUAL BOARD
 */
#define ONE_WIRE_BUS 5

/**
	Timer1 set to 10ms (100Hz)
 */
#define HZ100 10   // MsTimer2 works on 'millisecond' steps

// local functions declaration

void printAddress(DeviceAddress deviceAddress);
void timerCallbackScheduler(void);
void checkTemperature(void);

// Define variables and constants


/**
	Scheduler object that will advance 1 step every overflow of schedulerTimer
	SD card chipselect pin (10 for adafruit SD datalogger shield)
 */
Scheduler scheduler;


/**
	RTC object for Real Time Clock
 */
RTC_DS1307 rtc;

/**
	Temperature sensor unque address // Always will access sensors by its DeviceAddress
 */
DeviceAddress sensor1Address;

/**
	OneWire object // sensors Object
	SD File handler
 */
OneWire oneWire(ONE_WIRE_BUS);

/**
    Dallas temperature sensor object
 */
DallasTemperature sensors(&oneWire);

/**
    SD card File handler
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
     // CS pin ( pin 10 on most boards) MUST to be st to uotput (even when using another pin por CS)
     pinMode(chipSelectPin, OUTPUT);
     
     //Start serial
     
     Serial.begin(9600);
     Serial.println("Temperature Logger");
     Serial.print("\n");
     
     //Scheduler timer init
     MsTimer2::set(HZ100, timerCallbackScheduler);
     MsTimer2::start();
     
     // Start Wire lib
     Wire.begin();
     
     
     // Start up the sensor library
     sensors.begin();
     
     //Scheduler init
     scheduler.createSchedule(15000, -1, FALSE, checkTemperature);  // 5 minutes schedule
     
     // Start RTC lib
     rtc.begin();
     
     // Adjust RTC clock if its not running ( ie no batt )
     if (!rtc.isrunning()) {
         Serial.println("RTC is NOT running: adjusting...");
         // following line sets the RTC to the date & time this sketch was compiled
         rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
     }
   
         now = rtc.now();
         
         Serial.print("RTC Reporting:");
         
         Serial.print(now.day(), DEC);
         Serial.print('/');
         Serial.print(now.month(), DEC);
         Serial.print('/');
         Serial.print(now.year(), DEC);
         Serial.print(' ');
         Serial.print(now.hour(), DEC);
         Serial.print(':');
         Serial.print(now.minute(), DEC);
         Serial.print(':');
         Serial.print(now.second(), DEC);
         Serial.println();
     
     //Requesting how many sensors
     Serial.print("Number of sensors in bus: ");
     Serial.print(sensors.getDeviceCount(), DEC);
     Serial.print("\n");
     now=rtc.now();
     
     //Get address of first sensor in bus (index 0)
    
     
     sensors.getAddress(sensor1Address, 0);
     
     //Print address of first sensor (index 0)
     
     Serial.print("Sensor 1 HEX Address: ");
     printAddress(sensor1Address);
     Serial.print("\n");

    
     if(!SD.begin(chipSelectPin)){
         
         Serial.println("SD not init....exiting");
         return;
     }
     
     
 
     // Assign a name to log file in 8.3 format : DD_MM_YY.TXT ( and some needed conversion from String object to char*)
     FileNameString=String(now.day())+'_'+String(now.month())+'_'+String(now.year()-2000)+".TXT";
     int str_len = FileNameString.length() + 1;
     char sdFileName[str_len];
     FileNameString.toCharArray(sdFileName, str_len);
     sdFile = SD.open(sdFileName, FILE_WRITE);
     
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
/**
	scheduled task for requesting sensors temperature and serial displaying temp for first sensor
	@param  none
 */
void checkTemperature()

{
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print("\r");
    
    now=rtc.now();
    
    sdFile.print(now.day(), DEC);
    sdFile.print('/');
    sdFile.print(now.month(), DEC);
    sdFile.print('/');
    sdFile.print(now.year(), DEC);
    sdFile.print("\t");
    sdFile.print(now.hour(), DEC);
    sdFile.print(':');
    sdFile.print(now.minute(), DEC);
    sdFile.print("\t");
    sdFile.print(sensors.getTempCByIndex(0));
    
    sdFile.println();
    
    sdFile.flush();

}
