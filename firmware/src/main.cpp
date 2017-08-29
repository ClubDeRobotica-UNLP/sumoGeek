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

sysResponse ctrl = SYS_FAIL;
sensorResponse direction = SENSOR_FAIL;

/* -------------------------------------------------------------------------
 *  Función de SetUp
 * ------------------------------------------------------------------------- */
void setup()
{
	/* Inicialización de módulos. */
	serialInit();

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
		
		/* Chequeo que los CNY no me den que estoy en la linea.  */

		/* Evaluo los sensores. */
		 direction =  sensorEvaluate();
		 switch(direction)
		 {
		 	case SENSOR_CENTER:
		 		/* Objetivo al Centro. */
		 		Serial.println("Centro!");
		 		break;

		 	case SENSOR_LEFT:
		 		/* Objetivo a la izquierda. */
				Serial.println("Izquierda!");
				break;

			case SENSOR_RIGHT:
				/* Objetivo a la derecha. */
				Serial.println("Derecha!");
				break;

			case SENSOR_FAIL:
			default:
		 		/* Si no tengo nada en frente, avanzo a paso tranqui... */
				Serial.println("Indeterminado!");
				break;
		}
		delay(500);
	}
}
