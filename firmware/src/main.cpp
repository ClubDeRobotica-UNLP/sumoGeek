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
sensorResponse direction;
unsigned long currentTime = 0;
unsigned long lastConnTime = 0;
unsigned long lastConnection = 0;

/* -------------------------------------------------------------------------
 *  Función de SetUp
 * ------------------------------------------------------------------------- */
void setup()
{
	/* Inicialización de módulos. */
	serialInit();

	/* Inicializacion de Motores. */
	//motionInit();

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
		serialLoopBack();
		lastConnTime = millis();

	/* Si no hay datos por BT, opero en modo autónomo. */
	} else if ((millis() - lastConnTime) > 500) {
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
		delay(1000);
	}
}
