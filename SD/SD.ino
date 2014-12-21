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

//
// Brief	Setup


// Add setup code 
void setup() {
    
    pinMode(chipSelectPin, OUTPUT);
    SD1.begin(chipSelectPin);

 
}

//
// Brief	Loop

// Add loop code
void loop() {
    
}
