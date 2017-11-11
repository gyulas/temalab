#include "Arduino.h"
#include "Wire.h"
#include "VL6180X.h"

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	Serial.println('serial');
}
