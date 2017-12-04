#include "Arduino.h"
#include "controller.h"
#include "math.h"


//TODO: read the plant output  --- inline?
void readPlantOutput()
{
	yk=1; //dummy plant output
	//LightRanger.readRangeSingleMillimeters();
}

//TODO: write the actuators (controller output)  --- inline?
void writePlantInput()
{

	//analogWrite(MotorEnPin,uk_out);

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
	//TODO: configure input and output pins

	Serial.begin(9600);
	Serial.println("serial enabled");

}

void loop()
{
	//read
	//compute
	//write
	//wait
	readPlantOutput();
	controllerUpdate();
	writePlantInput();

	delay(20); //troger
}
