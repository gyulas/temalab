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

uint8_t number;

//reference
double rk=0;
double rk_1=0;
//controller output PWM %
double uk=0;
double uk_1=0;
double uk_sat=0;
uint8_t uk_out=0;

//plant output, mm
double yk=0;
double yk_1=0;
//hibajel
double ek=0;
double ek_1=0;

//50ms sample
//error computing
//uk computing
//shift in discrete time domain
//for the values r,e and u

double Ap=2;
double Ti=0.05;
double Ts=0.050; //Ts=50ms

long int count1_us=0;
long int count2_us=0;
double pwmScale=0; //0..1

bool controllerUpdate=false;
bool receiveCommand=false;

int i=0;

void controllerRun(void)
{
	//runs the controller 1 step
	controllerUpdate=true;
}

inline void pwmBinary()
{
	//updates reference signal
	receiveCommand=true;
}


void linearPWM(uint8_t min, uint8_t max, uint8_t wait)
{
	//test function
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


void changeReference()
{
	//set the reference based on input
	if(Serial.available())
	{
		input=Serial.read();
		switch (input)
			{
			case 43: // '+'
				if(rk==500)
					{rk=500;}
				else {rk++;}
				break;
			case 45: //'-'
				if(rk==0)
					{rk=0;}
				else {rk--;}
				break;
			default:
				//48-57: 0..9 numeric
				if(input>47 && input<58)
				{
					pwmPercentage=(input-48);  //ASCII48= '0' --> 0%, resolution 10%
					rk=map(pwmPercentage,0,9,200,350);
				}
				break;
			}
		Serial.print("rk:\t\t");
		Serial.println(rk);
		Serial.print("uk:\t");
		Serial.println(uk);
		Serial.print("uk_out:\t");
		Serial.println(uk_out);
		Serial.print("yk:\t");
		Serial.println(yk);
	}
}

void setup()
{
	Serial.begin(115200);
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
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
	LightRanger.setScaling(3);

}

void loop()
{
//test
	//linearPWM(130,2000,100);
	//steppedPWM(120, 160, 5, 180);

	if(controllerUpdate)
	{
		yk=LightRanger.readRangeSingleMillimeters();
		ek=rk-yk;
		uk=uk_1+(Ap*Ts/(2*Ti)*(ek-ek_1))+Ap*(ek-ek_1);
		uk_sat=(uk>1000)?(1000):((uk<-1000)?(-1000):(uk));
		uk_out=map(uk_sat,+500,-500,0,255);
		analogWrite(MotorEnPin,uk_out);
		ek_1=ek;
		uk_1=uk;
		rk_1=rk;

		//referencia 200-ig mehesen le
	}

	if(receiveCommand)
	{
		if(Serial.available()){
			changeReference();
		}
	}

}
