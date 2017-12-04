#include "Arduino.h"
#include "TimerOne.h"
#include "sensor.h"
#include "controller.h"
#include "interrupts.h"


void timingISR(void)
{
	uread = true;
	ucontroller = true;
	uwrite = true;
	usend = true;

	if (!(iISR % 100))
	{
		rk=(rk)?(255):(0);
	}

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

	//saturation limits, mapping
	uk_sat=(uk>1000)?(1000):((uk<-1000)?(-1000):(uk));
	//with good mapping possibly a unit transmission can be achieved
	uk_out=map(uk_sat,+500,-500,0,255);

	ek_1=ek;
	uk_1=uk;
	rk_1=rk;

	//writePlantInput();
}

void setup()
{
	Serial.begin(115200);

	Timer1.initialize(20000);
	delay(100);
	Timer1.attachInterrupt(timingISR);


	//sensor
	Wire.begin();
	LightRanger.init();
	LightRanger.configureDefault();
	LightRanger.setScaling(3);
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
		analogWrite(4,uk);
	}
	if(usend)
	{
		usend = false;
		Serial.print(millis());
		Serial.print(";");
		Serial.println(yk);
	}
}
