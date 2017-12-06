#include "Arduino.h"
#include "TimerOne.h"
#include "sensor.h"
#include "controller.h"
#include "interrupts.h"

#define MotorEnPin 4
#define Motor1A1 27  //in1b
#define Motor1A2 26  //in1a


void timingISR(void)
{
	iISR++;
	uread = true;
	usend = true;
	uwrite = true;
	ucontroller = true;


	/*if (!(iISR % 2000))
	{
		uwrite = true;
		rk=(80==rk)?(120):(80);
	}*/

	if (!(iISR % 2048))
	{
		//ritka
	}
}

void controllerUpdate()
{
	//readPlantOutput();

	ek=rk-yk;
	uk=uk_1+(Ap*Ts/(2*Ti)*(ek-ek_1))+Ap*(ek-ek_1);
	//uk=uk_1-0.18*ek+0.1636*ek_1;
	//uk=uk_1-0.033815*ek+0.029175*ek_1;

	uk_sat=(uk>1000)?(1000):((uk<-1000)?(-1000):(uk));
	uk_out=map(uk_sat,+500,-500,0,255);
	analogWrite(MotorEnPin,uk_out);

	ek_1=ek;
	uk_1=uk;
	rk_1=rk;

	//writePlantInput();
}

int input=0;

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
					rk=map(input-48,0,9,50,250);  //ASCII48= '0' --> 0%, resolution 10%
				}
				break;
			}
	}
}

void setup()
{
	pinMode(Motor1A1, OUTPUT);
	pinMode(Motor1A2, OUTPUT);
	pinMode(MotorEnPin, OUTPUT);

	digitalWrite(Motor1A1,0);
	digitalWrite(Motor1A2,1);
	digitalWrite(MotorEnPin,1);


	Serial.begin(115200);

	Timer1.initialize(50000);
	delay(100);
	Timer1.attachInterrupt(timingISR);


	//sensor
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
	LightRanger.setScaling(2);

	//analogWrite(4,240);
	delay(700);
	uk=190;
}


void loop()
{
	if(uread)
	{
		uread = false;
		yk=LightRanger.readRangeSingleMillimeters();
	}
	if(ucontroller)
	{
		ucontroller = false;
		controllerUpdate();
	}

	if(uwrite)
	{
		uwrite = false;
	}
	if(usend)
	{
		if(Serial.available()){
					changeReference();
		}
		usend = false;
		Serial.print(rk);
		Serial.print("\t");
		Serial.print(uk);
		Serial.print("\t");
		Serial.print(yk);
		Serial.print("\t");
		if(yk>99)
		{
			Serial.println(int(yk));
		}
		else
		{
			Serial.print(0);
			Serial.println(int(yk));
		}

	}
}
