#include "Arduino.h"
#include "sensor.h"
#include "controller.h"
#include "interrupts.h"

#define LabVIEW

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

int aw=0;
void controllerUpdate()
{
	//readPlantOutput();

	aw=(uk_sat==500||uk_sat==-500)?(0):(1);	//antiwindup
	ek=rk-yk;  //12-nal 280--> negativ uk, 10>poz-abb uk++
	uk=uk_1+(Ap*Ts*aw/(2*Ti)*(ek+ek_1))+Ap*(ek-ek_1);

	uk_sat=(uk>500)?(500):((uk<-500)?(-500):(uk));
	uk_out=map(uk_sat,+500,-500,0,255);
	analogWrite(MotorEnPin,uk_out);

	ek_1=ek;
	uk_1=uk_sat;
	rk_1=rk;

	//writePlantInput();
}

int input=0; //to COM port use

void changeReference()
{
#ifdef LabVIEW
	if(Serial.available())
		{
			rk=Serial.read();
		}
#endif


#ifndef LabVIEW

	//MANUAL ON SERIAL PORT
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
#endif
}

void writeData ()
{
#ifndef LabVIEW
	Serial.print("rk:\t");
	Serial.print(rk);
	Serial.print("\tuk:\t");
	Serial.print(uk);
	Serial.print("\tuk_out:\t");
	Serial.print(uk_out);
	Serial.print("\tyk:\t");
	Serial.println(yk);
#endif

#ifdef LabVIEW
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
#endif
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
