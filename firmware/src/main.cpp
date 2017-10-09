/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    18-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Main Sketch.
 * ------------------------------------------------------------------------- */
#include <Arduino.h>
#include "config.h"
#include <controlLib.h>
//#include <serialComm.h>
#include <motionCore.h>
#include <motorLib.h>
#include <sensorArray.h>




unsigned long time1, time2;
/*	Variables. */
float distL = 0.0, distR = 0.0;
volatile float lateralError = 0;

//sysResponse ctrl = SYS_FAIL;
//sensorResponse direction = SENSOR_FAIL;
//sysState status = STATE_HUNT;

Controller controlPI(10,-80.0,80.0);

void controlCallBack(void);
/* -------------------------------------------------------------------------
 *  Función de SetUp
 * ------------------------------------------------------------------------- */
void setup()
{
	/* Inicialización de módulos. */
	//serialInit();
	sensorInit();

	/* Inicializacion de Motores. */
	motionInit();

	Serial.begin(9600);
	/* Inicializaciones varias. */
	pinMode(13,OUTPUT);
	/* Finalizada Inicalización. */

	controlPI.setParameters(15.0, 15.0, 0, 8);
	controlPI.setTimer(controlCallBack);
	controlPI.startTimer();

}

/* -------------------------------------------------------------------------
 *  Main Loop
 * ------------------------------------------------------------------------- */
void loop()
{

		//time1 = micros();
		/* Evaluo los sensores. */
		 if(sensorLateralDistance(&distL, &distR) == SYS_SUCCESS){
			  lateralError= distR- distL;
		}
		//time2=micros()-time1;
		//Serial.println(time2);
	}

void controlCallBack(void){
	float control;
	uint8_t nominalSpeed =120, differentialSpeed;
	control = controlPI.compute(lateralError);
	differentialSpeed = (int) control;
	motionDifferential(nominalSpeed+differentialSpeed, nominalSpeed-differentialSpeed);
}
