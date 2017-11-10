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
#include <serialComm.h>
#include <motionCore.h>
#include <motorLib.h>
#include <sensorArray.h>
#include <stdlib.h>




unsigned long time1, time2;
/*	Variables. */
float distC = 0.0, distR = 0.0, distL = 0.0;
volatile float Error = 0;
char buffer[4] = {0};
volatile uint8_t ffront = 0, fstop = 0, flateralcompl = 0, cstop = 0;
//sysResponse ctrl = SYS_FAIL;
//sensorResponse direction = SENSOR_FAIL;
//sysState status = STATE_HUNT;

Controller control(CONTROL_PERIOD,0.0,0.0);

void controlCallBack(void);
void right_wall_funct(void);
void left_wall_funct(void);
void turn_direct_funct(void);
void turn_inverse_funct(void);
/* -------------------------------------------------------------------------
 *  Función de SetUp
 * ------------------------------------------------------------------------- */
void setup()
{
	/* Inicialización de módulos. */
	serialInit();
	sensorInit();

	/* Inicializacion de Motores. */
	motionInit();

	Serial.begin(9600);
	/* Inicializaciones varias. */
	pinMode(13,OUTPUT);
	/* Finalizada Inicalización. */

	//control.setParameters(20,8, 0, 8);
	control.setTimer(controlCallBack);
	control.startTimer();


}

/* -------------------------------------------------------------------------
 *  Main Loop
 * ------------------------------------------------------------------------- */
void loop()
{
	if (!(PIND & 0b100)){
		  control.stopTimer();
			motionDifferential(200, 200);
			delay(1000);
			motionDifferential(0, 0);
			while(!(PIND & 0b100)){}
			control.startTimer();
	}
		//time1 = micros();
	/* Evaluo los sensores laterales */
	MAZE_RESOLVER_MEASURE

	/* Evaluo sensor central */
	if(ffront == 0) { // Solo evaluo centro, si no hay procesamiento pendiente
		if (sensorCenter(&distC) == SYS_SUCCESS) {
			if (distC < CENTER_REF) { // si detecto frente, me detengo y vuelvo a mirar
					control.stopTimer();
					motionDifferential(0, 0);
					delay(CENTER_DETECT_PAUSE); // detengo durante x ms
					if (sensorCenter(&distC) == 	SYS_SUCCESS) {
							if (distC < CENTER_REF) { // si existe doble deteccion
								ffront = 1; //Activo flag de deteccion de frente
							}
					}
					#if WALL_ALGHM
						if (sensorLeft(&distL) == 	SYS_SUCCESS)
								flateralcompl = 1;
						else flateralcompl = 0;
					#else
						if (sensorRight(&distR) == 	SYS_SUCCESS)
								flateralcompl = 1;
						else flateralcompl = 0;
					#endif

					control.startTimer(); //reactivo control
			}
		}
	}
		//time2=micros()-time1;
		//Serial.println(time2);
}

void controlCallBack(void){
	int rightSpeed, leftSpeed, controlSpeed;

	if(fstop == 1){ // Luego de girar, detiene el auto por unos segundos
		if(cstop < 20){
			cstop++;
		}	else{
			cstop = 0;
			fstop = 0;
			ffront = 0; // reinicio deteccion frente
		}
		return;
	}

	// GIRA ESQUIVANDO LA PARED> EVITA TRABARSE CUANDO CHOCA FRENTE
	if(ffront == 1 && flateralcompl == 1){
		turn_inverse_funct();
		return;
	}

	// GIRA SIGUIENDO LA PARED
	if(ffront == 1){ // si detecto frente
		turn_direct_funct();
		return;
	}
	if (ffront == 1) ffront = 0;

  // seguimiento de pared
	controlSpeed = 0;
  if (Error > CONTROL_DEADZONE)
		controlSpeed = CONTROL_ACTION;
	if (Error < -CONTROL_DEADZONE)
		controlSpeed = -CONTROL_ACTION;

  // upload motores
	rightSpeed = saturate(NOMINAL_SPEED+ controlSpeed);
	leftSpeed = saturate(NOMINAL_SPEED - controlSpeed);
	motionDifferential(leftSpeed, rightSpeed);
}

void right_wall_funct(void){
	if(sensorRight(&distR) == SYS_SUCCESS){
		 Error= WALL_REF-distR;
	} else {
		 Error = -100;  // En caso de no detectar nada, gira a la derecha
	}
}

void left_wall_funct(void){
	if(sensorLeft(&distL) == SYS_SUCCESS){
		 Error= distL-WALL_REF;
	} else {
		 Error = +100;  // En caso de no detectar nada, gira a la izquierda
	}
}

void turn_direct_funct(void){
	control.stopTimer();
#if WALL_ALGHM //SEGUIDOR PARED DERECHA
	motionDifferential(-CONTROL_TURN_SPEED-CONTROL_TURN_SPEED_OFFSET,CONTROL_TURN_SPEED);
	delay(CONTROL_TURN_DELAY);
	motionDifferential(0,0);
#else	// SEGUIDOR PARED IZQUIERDA
	motionDifferential(CONTROL_TURN_SPEED,-CONTROL_TURN_SPEED-CONTROL_TURN_SPEED_OFFSET);
	delay(CONTROL_TURN_DELAY);
	motionDifferential(0,0);
#endif
	control.startTimer();
	fstop = 1;		// activo detencion

}

void turn_inverse_funct(void){
	control.stopTimer();
#if WALL_ALGHM //SEGUIDOR PARED DERECHA
	motionDifferential(CONTROL_TURN_SPEED,-CONTROL_TURN_SPEED-CONTROL_TURN_SPEED_OFFSET);
	delay(CONTROL_TURN_DELAY/2);
	motionDifferential(0,0);
#else	// SEGUIDOR PARED IZQUIERDA
	motionDifferential(-CONTROL_TURN_SPEED-CONTROL_TURN_SPEED_OFFSET,CONTROL_TURN_SPEED);
	delay(CONTROL_TURN_DELAY/2);
	motionDifferential(0,0);
#endif
	control.startTimer();
	fstop = 1;		// activo detencion
}
