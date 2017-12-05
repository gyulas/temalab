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

	//ucontroller = true;
	if (!(iISR % 80))
	{
		//usend = true;
		uk=(181==uk)?(157):(181);

	}

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
	//uk=uk_1+(Ap*Ts/(2*Ti)*(ek-ek_1))+Ap*(ek-ek_1);
	//uk=uk_1-0.18*ek+0.1636*ek_1;
	uk=uk_1-0.033815*ek+0.029175*ek_1;

	//saturation limits, mapping
	uk_sat=(uk>800)?(800):((uk<-800)?(-800):(uk));
	//with good mapping possibly a unit transmission can be achieved
	uk_out=map(uk_sat,0,800,50,230);

	ek_1=ek;
	uk_1=uk_sat;
	rk_1=rk;

	//writePlantInput();
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

	Timer1.initialize(25000);
	delay(100);
	Timer1.attachInterrupt(timingISR);


	//sensor
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
	LightRanger.setScaling(2);

	analogWrite(4,240);
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
		analogWrite(4,uk_out);
	}

	if(uwrite)
	{
		uwrite = false;
		analogWrite(4,uk);

	}
	if(usend)
	{
		usend = false;
		//Serial.print(millis());
		//Serial.print("\t");
		//Serial.print(rk);
		//Serial.print("\t");
		Serial.print(uk);
		Serial.print("\t");
		//Serial.print(uk_out);
		//Serial.print("\t");
		Serial.println(yk);
	}
}
