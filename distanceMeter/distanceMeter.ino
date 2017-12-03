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

//reference
uint8_t rk=0;
uint8_t rk_1=0;
//controller output PWM %
double uk=0;
uint8_t uk_1=0;
//plant output, mm
uint8_t yk=0;
uint8_t yk_1=0;
//hibajel
uint8_t ek=0;
uint8_t ek_1=0;

//50ms sample
//error computing
//uk computing
//shift in discrete time domain
//for the values r,e and u

double Ap=1;
double Ti=0.1;
double Ts=0.050; //Ts=50ms

long int count1_us=0;
long int count2_us=0;
double pwmScale=0; //0..1

bool controller=false;
bool pwmUpdate=false;
bool pwmState=false;
double pwmVal=0;

int i=0;

void controllerRun(void)
{
	controller=true;
}

inline void pwmBinary()
{
	//pwmUpdate=true;
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
	Serial.begin(9600);
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
	Timer3.initialize(50000);

	Timer1.attachInterrupt(pwmBinary);
	Timer3.attachInterrupt(controllerRun);

	analogWrite(MotorEnPin,250);

	/*Serial.print("millis");
	Serial.print(";");
	Serial.print("pwm fill factor");
	Serial.print(";");
	Serial.println("sensor distance in mm");*/

	LightRanger.setScaling(3);
/*
	//LightRanger.
	Serial.print("threshold high and low");
	Serial.print("\t");
	Serial.println("mm:");
	Serial.println(LightRanger.readRangeSingleMillimeters());
	//delay(1450);
*/
}


// The loop function is called in an endless loop
void loop()
{
	//LightRanger.readRangeContinuousMillimeters()
	//count1_us=micros();
	mm=LightRanger.readRangeSingleMillimeters();
	//count2_us=micros();

	Serial.print("distance: \t");
	Serial.println(mm);
	Serial.print("\t time [us]: \t");
	Serial.println(count2_us-count1_us);

	//Serial.println(reference);
	//linearPWM(130,2000,100);
	//steppedPWM(120, 160, 5, 180);

	if(controller)
	{
		yk=LightRanger.readRangeSingleMillimeters();
		ek=rk-yk;
		uk=uk_1+(Ap*Ts/(2*Ti)*(ek-ek_1))+Ap*(ek-ek_1);
		analogWrite(MotorEnPin,uk);
		ek_1=ek;
		uk_1=uk;
		rk_1=rk;
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
