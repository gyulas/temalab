#include "Arduino.h"
#include "Wire.h"
#include "VL6180X.h"
#include "math.h"

#define MotorEnPin 4
#define Motor1A1 27  //in1b
#define Motor1A2 26  //in1a




VL6180X LightRanger;
uint16_t mm;
uint8_t x;
uint8_t reference=0;
uint8_t corrected=0;
uint8_t input=0;
uint8_t pwmPercentage=0;
double pwmScale=0; //0..1

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
	//set timeout!

	pinMode(27, OUTPUT);
	pinMode(26, OUTPUT);
	pinMode(4, OUTPUT);


	digitalWrite(27,0);
	digitalWrite(26,1);
}

void identTest()
{
	int i=1;
	analogWrite(4,200);
	delay(500);
	for(i=1;i<10;i++)
	{

	}


}

void linearPWM(uint8_t min, uint8_t max, uint8_t wait)
{
	int i=0;
	for(i=min;i<max;i++)
	{
		analogWrite(4,i);

		Serial.print(i);
		Serial.print(";");
		Serial.println(LightRanger.readRangeSingleMillimeters());

		delay(wait);
	}
	delay(100);
	for(i=max;i>min;i--)
	{
		analogWrite(4,i);

		Serial.print(i);
		Serial.print(";");
		Serial.println(LightRanger.readRangeSingleMillimeters());

		delay(wait);
	}
}




// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	if(Serial.available())
	{
		input=Serial.read();
		switch (input)
			{
			case 43: // '+'
				if(reference==255)
					{reference=255;}
				else {reference++;}
				break;
			case 45: //'-'
				if(reference==0)
					{reference=0;}
				else {reference--;}
				break;
			case 32: //' ' space
				//read an uint8 for value
			default:
				//48-57: 0..9 numeric
				if(input>47 && input<58)
				{
					pwmPercentage=(input-48)*10;  //ASCII48= '0' --> 0%, resolution 10%
					//pwmScale=(input-48)/10;
					corrected=sqrt(pwmPercentage)*25.5;
					reference=map(corrected,0,255,100,200);
					//Serial.println(reference);
				}
				break;
			}
	}


	mm=LightRanger.readRangeSingleMillimeters();
	//analogWrite(4,reference);
	/*Serial.print("distance: \t");
	Serial.println(mm);*/
	Serial.println(reference);
	linearPWM(130,190,100);

}
