#include "sensor.h"


void setup()
{
	Serial.begin(115200);
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
	LightRanger.setScaling(3);
}

void loop()
{
	Serial.println(LightRanger.readRangeSingleMillimeters());
	delay(100);
}
