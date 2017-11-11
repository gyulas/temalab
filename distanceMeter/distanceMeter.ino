#include "Arduino.h"
#include "Wire.h"
#include "VL6180X.h"
#include "math.h"
#include "TimerOne.h"
#include "TimerThree.h"

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

int i=0;

void sensorValue(void)
{
	//Serial.println("sensor read");

	/*Serial.print(i);
	Serial.print(";");*/
	Serial.println(LightRanger.readRangeSingleMillimeters());
}

inline void pwmBinary()
{
	//inverts output 4, working
	//Serial.println("enable inverted");
	digitalWrite(MotorEnPin, !digitalRead(MotorEnPin));
}


void linearPWM(uint8_t min, uint8_t max, uint8_t wait)
{
	//int i=min;
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


void steppedPWM(uint8_t min, uint8_t max, uint8_t ts, uint8_t burst)
{
	int i=min;
	//int burst=190;
	//int ts=20;
	for(i=min;i<max;i++)
	{
		if(i%10){
			analogWrite(4,burst);
			delay(ts/2);
		}
		else
		{
			analogWrite(4,i);
			delay(ts);
		}
		/*Serial.print(millis());
		Serial.print(";");
		Serial.print(i);
		Serial.print(";");
		Serial.println(LightRanger.readRangeSingleMillimeters());
		delay(ts);*/


	}

	for(i=max;i>min;i--)
	{

		if(i%10){
			analogWrite(4,burst);
			delay(ts/2);
		}
		else
		{
			analogWrite(4,i);
			delay(ts);
		}
		/*Serial.print(millis());
		Serial.print(";");
		Serial.print(i);
		Serial.print(";");
		Serial.println(LightRanger.readRangeSingleMillimeters());*/
		//delay(ts);

	}
}

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(115200);
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
	//set timeout!

	delay(1000);

	pinMode(27, OUTPUT);
	pinMode(26, OUTPUT);
	pinMode(4, OUTPUT);


	digitalWrite(27,0);
	digitalWrite(26,1);
	digitalWrite(MotorEnPin,1);

	Timer1.initialize(500000);
	Timer3.initialize(50000);
	/*Timer1.start();*/

	Timer1.attachInterrupt(pwmBinary);
	Timer3.attachInterrupt(sensorValue);

	Serial.print("millis");
	Serial.print(";");
	Serial.print("pwm fill factor");
	Serial.print(";");
	Serial.println("sensor distance in mm");
}


// The loop function is called in an endless loop
void loop()
{
	//mm=LightRanger.readRangeSingleMillimeters();
	/*Serial.print("distance: \t");
	Serial.println(mm);*/
	//Serial.println(reference);
	//linearPWM(130,2000,100);
	//steppedPWM(120, 160, 5, 180);

}
