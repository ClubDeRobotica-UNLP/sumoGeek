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
#include <serialComm.h>
#include <sensorArray.h>
#include <motionCore.h>
#include <motorLib.h>

#include "config.h"

/*	Variables. */
char btData = 0x00;
unsigned long lastConnTime = 0;
unsigned long attackStart = 0;

sysResponse ctrl = SYS_FAIL;
sensorResponse direction = SENSOR_FAIL;
sysState status = STATE_HUNT;

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

	/* Inicializaciones varias. */
	pinMode(13, OUTPUT);
	digitalWrite(13, 0);

	/* Finalizada Inicalización. */
}

/* -------------------------------------------------------------------------
 *  Main Loop
 * ------------------------------------------------------------------------- */
void loop()
{
	/* Si hay transmisión por BT, entro en modo RC. */
	if (serialBTAvailable() != SYS_FAIL)
	{
		/* Enciendo el LED indicador de modo. */
		digitalWrite(13, 1);

		ctrl = serialBTGetChar(&btData);
		if (ctrl != SYS_FAIL)
		{
			/* Si obtuve el dato, opero en modo RC. */
			motionRcOperation(btData);
			lastConnTime = millis();
		}

	/* Si no hay datos por BT, opero en modo autónomo. */
	} else if ((millis() - lastConnTime) > 500) {

		/* Apago el LED indicador de modo. */
		digitalWrite(13, 0);

		/* Si detecto la línea, o el estado cambió a STATE_LINE, retrocedo. */
		if ((!(PIND & 0b100)) || (status == STATE_LINE))
		{
			Serial.println("Linea!");
			motionBackwards(240);
			delay(750);
			motionTurn(MOTION_LEFT, MOTION_TURN_TIME_90 * 1.2);
		}

		/* Si no estoy atacando, reseteo el inicio de ataque. */
		if (status != STATE_ATTACK)
		{
			attackStart = 0;
		}

		/* Evaluo los sensores. */
		 direction =  sensorEvaluate();
		 switch(direction)
		 {
		 	case SENSOR_CENTER:
		 		/* Objetivo al Centro. */
		 		Serial.println("Centro!");
				status = STATE_ATTACK;
				/* Si es el primer Centro, registro el tiempo. */
				if (attackStart == 0)
				{
					attackStart = millis();
				}

				/* Embisto el objetivo como máximo tanto tiempo. */
				if ((millis() - attackStart) < MOTION_ATTACK_TIME)
				{
					motionForward(MOTOR_ATTACK_SPEED);
				} else {
					status = STATE_LINE;
				}
				break;

		 	case SENSOR_LEFT:
		 		/* Objetivo a la izquierda. */
				Serial.println("Izquierda!");
				motionTurn(MOTION_LEFT, MOTION_TURN_TIME_90);
				status = STATE_HUNT;
				break;

			case SENSOR_RIGHT:
				/* Objetivo a la derecha. */
				Serial.println("Derecha!");
				motionTurn(MOTION_RIGHT, MOTION_TURN_TIME_90);
				status = STATE_HUNT;
				break;

			case SENSOR_FAIL:
			default:
		 		/* Si no tengo nada en frente, avanzo a paso tranqui... */
				Serial.println("Indeterminado!");
				motionForward(MOTOR_CRUISE_SPEED);
				status = STATE_HUNT;
				break;
		}
	}
}
