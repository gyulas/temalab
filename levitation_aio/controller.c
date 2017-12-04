/*
 * controller.c
 *
 *  Created on: 2017. dec. 4.
 *      Author: László
 */

//#include "controller.h"


/*
 * Considerations:
 *
 * 	- I/O commands performed outside this loop
 * 	- mapping, saturating should be modified when tuning
 *
 */
//
//void controllerUpdate()
//{
//	//readPlantOutput();
//
//	ek=rk-yk;
//	uk=uk_1+(Ap*Ts/(2*Ti)*(ek-ek_1))+Ap*(ek-ek_1);
//
//	//saturation limits, mapping
//	uk_sat=(uk>1000)?(1000):((uk<-1000)?(-1000):(uk));
//	//with good mapping possibly a unit transmission can be achieved
//	uk_out=map(uk_sat,+500,-500,0,255);
//
//	ek_1=ek;
//	uk_1=uk;
//	rk_1=rk;
//
//	//writePlantInput();
//}


