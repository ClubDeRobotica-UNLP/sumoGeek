/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    18-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca para el control de los motores.
 * ------------------------------------------------------------------------- */
#include <Arduino.h>

#include "motorLib.h"

/* Variables Globales. */
motorControlBlock* motorR;
motorControlBlock* motorL;

/* -------------------------------------------------------------------------
 *  Función para inicializar una nueva estructura de control de un motor.
 * ------------------------------------------------------------------------- */
motorControlBlock* motorInit(byte pinEnable, byte pinA, byte pinB)
{
	motorControlBlock* controlBlock;

	controlBlock = (motorControlBlock*) malloc(sizeof(motorControlBlock));
	if (controlBlock != NULL)
	{
		/* Configuro los pines como salidas. */
		pinMode(pinA, OUTPUT);
		pinMode(pinB, OUTPUT);
		pinMode(pinEnable, OUTPUT);

		/* Empiezo con todos en bajo. */
		digitalWrite(pinA, 0);
		digitalWrite(pinB, 0);
		digitalWrite(pinEnable, 0);

		/* Seteo la estructura de control. */
		controlBlock->motorPinA = pinA;
		controlBlock->motorPinB = pinB;
		controlBlock->motorPinEnable = pinEnable;
		controlBlock->motorSpeed = 0;
		controlBlock->motorRunning = false;
	}

	/* Devuelvo la estructura de control. */
	return controlBlock;
}


/* -------------------------------------------------------------------------
 *  Función para detener los motores, mediante la deshabilitación de las
 *  salidas del puente H.
 * ------------------------------------------------------------------------- */
void motorStop(motorControlBlock* motor)
{
	/* Deshabilito los motores. */
	motor->motorRunning = false;
	digitalWrite(motor->motorPinEnable, 0);
}


/* -------------------------------------------------------------------------
 *  Función para arrancar los motores al habilitar el puente H.
 * ------------------------------------------------------------------------- */
void motorStart(motorControlBlock* motor)
{
	/* Habilito los motores. */
	motor->motorRunning = true;
	digitalWrite(motor->motorPinEnable, 1);
}


/* -------------------------------------------------------------------------
 *  Función para configurar la velocidad de los motores, indicando además la
 *  direccion de giro de los mismos en el signo del valor a configurar.
 * ------------------------------------------------------------------------- */
void motorSetSpeed(motorControlBlock* motor, int pwmVal)
{
	if (pwmVal > 0)
	{
		digitalWrite(motor->motorPinB, 0);
		analogWrite(motor->motorPinA, pwmVal);
	} else {
		digitalWrite(motor->motorPinB, 1);
		analogWrite(motor->motorPinA, (255 + pwmVal));
	}
}
