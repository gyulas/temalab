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

bool sensorUpdate=false;
bool pwmUpdate=false;
bool pwmState=false;
double pwmVal=0;

int i=0;

void sensorValue(void)
{
	sensorUpdate=true;
}

inline void pwmBinary()
{
	pwmUpdate=true;
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

	delay(50);

	pinMode(27, OUTPUT);
	pinMode(26, OUTPUT);
	pinMode(4, OUTPUT);


	digitalWrite(27,0);
	digitalWrite(26,1);
	digitalWrite(MotorEnPin,1);

	Timer1.initialize(1000000);
	Timer3.initialize(7000);

	Timer1.attachInterrupt(pwmBinary);
	Timer3.attachInterrupt(sensorValue);

	analogWrite(MotorEnPin,250);

	Serial.print("millis");
	Serial.print(";");
	Serial.print("pwm fill factor");
	Serial.print(";");
	Serial.println("sensor distance in mm");
	delay(1450);

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

	if(sensorUpdate)
	{
		sensorUpdate=false;
		//Serial.println("sensor handled");
		Serial.print(millis());
		Serial.print(";");
		Serial.print(pwmVal);
		Serial.print(";");
		Serial.println(LightRanger.readRangeSingleMillimeters());
	}
	if(pwmUpdate)
	{
		pwmUpdate=false;
		//Serial.println("pwm handled");
				//pwmState=digitalRead(MotorEnPin);
				//digitalWrite(MotorEnPin, !pwmState);
		if(pwmState){
			analogWrite(MotorEnPin,255);

			pwmState=0;
			pwmVal=255.0/255;
		}
		else {
			analogWrite(MotorEnPin,0);
			pwmState=1;
			pwmVal=0.0/255;
		}
	}

}
