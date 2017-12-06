#include "Arduino.h"
#include "sensor.h"
#include "controller.h"
#include "interrupts.h"

void timingISR(void)
{
	//to perform in every cycle:
	iISR++;
	uread = true;
	usend = true;
	uwrite = true;
	ucontroller = true;

	if (!(iISR % 2048))
	{
		//special events can be inserted
	}
}

void controllerUpdate()
{
	//readPlantOutput();

	ek=rk-yk;
	uk=uk_1+(Ap*Ts/(2*Ti)*(ek-ek_1))+Ap*(ek-ek_1);

	uk_sat=(uk>200)?(200):((uk<-200)?(-200):(uk));
	uk_out=map(uk_sat,+200,-200,0,255);
	analogWrite(MotorEnPin,uk_out);

	ek_1=ek;
	uk_1=uk;
	rk_1=rk;

	//writePlantInput();
}

//int input=0; to COM port use

void changeReference()
{
	if(Serial.available())
		{
			rk=Serial.read();
		}

	/* MANUAL ON SERIAL PORT
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
	*/
}

void writeData ()
{
	//reference signal on 3 digit
	if(rk>99)
		{
			Serial.print(int(rk));
		}
		else
		{
			Serial.print(0);
			Serial.print(int(rk));
		}
	Serial.print(",");

	//control signal on 3 digit
	if(uk_out>99)
		{
			Serial.print(int(uk_out));
		}
		else
		{
			Serial.print(0);
			Serial.print(uk_out);
		}
	Serial.print(",");

	//output signal on 3 digit
	if(yk>99)
	{
		Serial.print(int(yk));
	}
	else
	{
		Serial.print(0);
		Serial.print(int(yk));
	}
	Serial.print(";");

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

	Timer1.initialize(period);
	delay(100);
	Timer1.attachInterrupt(timingISR);

	//sensor
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
	LightRanger.setScaling(2);

}


void loop()
{
	if(uread)
	{
		uread = false;
		yk=LightRanger.readRangeSingleMillimeters(); // maybe 10..25ms of delay
	}
	if(ucontroller)
	{
		ucontroller = false;
		controllerUpdate();
	}
	if(usend)
	{
		if(Serial.available()){
			changeReference(); //receive from LabVIEW
		}
		usend = false;
		writeData(); //send data to LabVIEW on serial
	}
}
