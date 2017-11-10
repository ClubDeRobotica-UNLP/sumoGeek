/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    25-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca de funciones asociadas al movimiento del robot.
 * ------------------------------------------------------------------------- */
#include <Arduino.h>
#include <motorLib.h>
#include <config.h>

#include "motionCore.h"

/* -------------------------------------------------------------------------
 *  Función de Inicializacion del módulo de movimiento.
 * ------------------------------------------------------------------------- */
 void motionInit(void)
 {
	 /* Inicializo los bloques de control de los motores. */
	 motorL = motorInit(MOTOR_L_PIN_E, MOTOR_L_PIN_A, MOTOR_L_PIN_B);
	 motorR = motorInit(MOTOR_R_PIN_E, MOTOR_R_PIN_A, MOTOR_R_PIN_B);

	 /* Habilitos los motores con 0 velocidad. */
	 motorSetSpeed(motorL, 0);
	 motorSetSpeed(motorR, 0);

	 motorStart(motorL);
	 motorStart(motorR);
 }

 /* -------------------------------------------------------------------------
  *  Función de movimiento al no detectar la direccion del objetivo.
  * ------------------------------------------------------------------------- */
void motionForward(uint8_t speed)
{
	/* Avanzo a velocidad de crucero. */
	motorSetSpeed(motorL, speed);
	motorSetSpeed(motorR, speed * MOTOR_LR_OFFSET);
}

/* -------------------------------------------------------------------------
 *  Función de embestida cuando el objetivo está en frente.
 * ------------------------------------------------------------------------- */
void motionBackwards(uint8_t speed)
{
	/* Embisto a toda velocidad. */
	motorSetSpeed(motorL, -speed);
	motorSetSpeed(motorR, -(speed * MOTOR_LR_OFFSET));
}

/* -------------------------------------------------------------------------
 *  Función de movimiento diferencial
 * ------------------------------------------------------------------------- */
void motionDifferential(int speedL, int speedR)
{
	/* Embisto a toda velocidad. */
	motorSetSpeed(motorL, speedL);
	motorSetSpeed(motorR, (speedR * MOTOR_LR_OFFSET));
}


/* -------------------------------------------------------------------------
 *  Función de giro.
 *  Gira en la direccion indicada por [direction] definida por constantes
 *  durante [timeInMs] milisegundos, prefiriendose que se opere sobre la
 *  constante calibrada MOTION_TIME_90.
 * ------------------------------------------------------------------------- */
void motionTurn(motionDirection direction, unsigned int timeInMs)
{
	/* Variables. */
	int tempSpeed;

	/* Calculo la velocidad y la aplico a los motores. */
	tempSpeed = MOTOR_TURN_SPEED * direction;

	motorSetSpeed(motorL, tempSpeed);
	motorSetSpeed(motorR, -(tempSpeed * MOTOR_LR_OFFSET));

	/* Espero el tiempo especificado. */
	delay(timeInMs);

	/* Dejo de girar. */
	motorSetSpeed(motorL, 0);
	motorSetSpeed(motorR, 0);
}

/* -------------------------------------------------------------------------
 *  Función de movimiento del modo RC.
 * ------------------------------------------------------------------------- */
void motionRcOperation(char input)
{
	/* Respuesta del SUMO a cada entrada recibida. */
	switch (input)
	{
		case 'F':  /* Adelante */
			motorSetSpeed(motorL, MOTOR_RC_BASE_SPEED);
			motorSetSpeed(motorR, MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET);
			break;

		case 'B':  /* Atrás */
			motorSetSpeed(motorL, -MOTOR_RC_BASE_SPEED);
			motorSetSpeed(motorR, -(MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET));
			break;

		case 'L':  /* Izquierda */
			motorSetSpeed(motorL, -MOTOR_RC_BASE_SPEED);
			motorSetSpeed(motorR,  (MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET));
			break;

		case 'R':  /* Derecha */
			motorSetSpeed(motorL,  MOTOR_RC_BASE_SPEED);
			motorSetSpeed(motorR, -(MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET));
			break;

		case 'G': /* Adelante - Izquierda */
			motorSetSpeed(motorL, MOTOR_RC_BASE_SPEED * 0.5);
			motorSetSpeed(motorR, (MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET));
			break;

		case 'I': /* Adelante - Derecha */
			motorSetSpeed(motorL, MOTOR_RC_BASE_SPEED);
			motorSetSpeed(motorR, (MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET) * 0.5);
			break;

		case 'H': /* Atrás - Izquierda */
			motorSetSpeed(motorL, -MOTOR_RC_BASE_SPEED * 0.5);
			motorSetSpeed(motorR, -(MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET));
			break;

		case 'J':  /* Atrás - Derecha */
			motorSetSpeed(motorL, -MOTOR_RC_BASE_SPEED);
			motorSetSpeed(motorR, -(MOTOR_RC_BASE_SPEED * MOTOR_LR_OFFSET) * 0.5);
			break;

		case 'S':
		default:  /* No se pulsó nada. */
			motorSetSpeed(motorL, 0);
			motorSetSpeed(motorR, 0);
			break;
	}
}

/* -------------------------------------------------------------------------
 *  Función de prueba de movimientos. Bloqueante.
 * ------------------------------------------------------------------------- */
void motionTest(void)
{
	/* Inicio de función de prueba. */
	delay(1500);
	Serial.println("Prueba de movimiento en marcha.\n");

	/* Avanzo a paso crucero. */
	Serial.println("Avanzo a paso crucero.");
	motionForward(MOTOR_CRUISE_SPEED);
	delay(500);

	/* Retrocedo a paso crucero. */
	Serial.println("Retrocedo a paso crucero.");
	motionBackwards(MOTOR_CRUISE_SPEED);
	delay(500);

	/* Giro 90º a la izquierda. */
	Serial.println("Giro 90º a la izquierda.");
	motionTurn(MOTION_LEFT, MOTION_TURN_TIME_90);
	delay(500);

	/* Giro 180º a la derecha. */
	Serial.println("Giro 180º a la derecha.");
	motionTurn(MOTION_RIGHT, MOTION_TURN_TIME_90 * 2);

	/* Fin de la prueba, freno los motores y cuelgo el programa. */
	motorSetSpeed(motorL, 0);
	motorSetSpeed(motorR, 0);

	Serial.println("Fin de la prueba.");
	while(1);
}

int saturate(int speed){
	if (speed>255)
		 return 255;
	if(speed<-255)
		return -255;
	return speed;
}
