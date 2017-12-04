#include "Arduino.h"

  int i=0;


inline void pwmBinary()
{
  //updates reference signal
  //receiveCommand=true;
}


void linearPWM(uint8_t min, uint8_t max, uint8_t wait)
{
  //test function
  //int i=min;
  for(i=min;i<max;i++)
  {
    analogWrite(4,i);
    delay(wait);
  }

  delay(100);

  for(i=max;i>min;i--)
  {
    analogWrite(4,i);
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

int input;
int tempVar;
int dataSet=0;

void changeReference()
{
  //set the reference based on input
  if(Serial.available())
  {
    input=Serial.read();
    switch (input)
      {
      case 43: // '+'
        if(dataSet==500)
          {dataSet=500;}
        else {dataSet++;}
        break;
      case 45: //'-'
        if(dataSet==0)
          {dataSet=0;}
        else {dataSet--;}
        break;
      default:
        //48-57: 0..9 numeric
        if(input>47 && input<58)
        {
          tempVar=(input-48);  //ASCII48= '0' --> 0%, resolution 10%
          dataSet=map(tempVar,0,9,200,350);
        }
        break;
      }
  }
}

void setup()
{
	Serial.begin(115200);

	//outputs of system
}


void loop()
{
	if(Serial.available())
	{
		changeReference();
	}

	Serial.print("dataSet:\t\t");
	Serial.println(dataSet);

	delay(100);

}
