/*
 * interrupts.h
 *
 *  Created on: 2017. dec. 4.
 *      Author: László
 */
#include "Arduino.h"
#include "TimerOne.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/*
 * To use libraries, must be chosen at Arduino->Add a library....
 * if the desired lib not there, search it at Arduino->Preferences->Library Manager.
 * (under Sloeber, Eclipse IDE)
 *
 */

#define period 50000 //in microseconds
#define inEachCycle 1
#define inEverySecondCycle 2
#define inEveryTenthCycle 10

/*
 * Booleans to notify the main() to handle the periodically generated interrupts:
 * (maybe Hun. Not. can be useful)
 *
 */


bool uread=false;
bool ucontroller=false;
bool uwrite=false;
bool usend=false;


/*
 * Handlers for the above: to set booleans
 */
void timingISR();


word iISR=0;



#endif /* INTERRUPTS_H_ */
