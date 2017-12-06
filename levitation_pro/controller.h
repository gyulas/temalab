/*
 * controller.h
 *
 *  Created on: 2017. dec. 4.
 *      Author: László
 */
#include "stdint.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

/*
 * I. Variables beyond are the signals of the discrete time control system.
 *
 */

	/*
	 *	a)		Units in mm
	 */
//reference
double rk=120;
double rk_1=120;

//plant output
double yk=0;
double yk_1=0;

//error
double ek=0;
double ek_1=0;

	/*
	 * 	b)	Different dimensions
	 */
//controller output PWM %
double uk=-50;
double uk_1=0;
double uk_sat=0;
uint8_t uk_out=0;

/*
 * 	II. Constants of the controller
 *  Properties:
 */

double Ap=1;
double Ti=1;
double Ts=0.050; //Ts=50ms

/*
 *  III. How it is works
 *
 *		50ms sample
 *		error computing
 *		uk computing
 *		shift in discrete time domain
 *		for the values r,e and u
 */

#define MotorEnPin 4
#define Motor1A1 27  //in1b
#define Motor1A2 26  //in1a

void controllerUpdate();

#endif /* CONTROLLER_H_ */
