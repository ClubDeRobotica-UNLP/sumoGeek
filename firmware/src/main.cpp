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

#include "config.h"

/* -------------------------------------------------------------------------
 *  Función de SetUp
 * ------------------------------------------------------------------------- */
void setup()
{
	/* Inicialización de módulos. */
	serialInit();

	/* Inicializacion de Sensores. */

	/* Inicializacion de Motores. */

	/* Finalizada Inicalización. */
}

/* -------------------------------------------------------------------------
 *  Main Loop
 * ------------------------------------------------------------------------- */
void loop()
{
	/*	Variables. */
	sensorResponse direction;

	/* Chequeo que los CNY no me den que estoy en la linea.  */

	/* Evaluo los sensores. */
	// direction =  sensorEvaluate();
	// switch(direction)
	// {
	// 	case SENSOR_CENTER:
	// 		/* Objetivo al Centro. */
	// 		Serial.println("Centro!");
	// 		break;
	//
	// 	case SENSOR_LEFT:
	// 		/* Objetivo a la izquierda. */
	// 		Serial.println("Izquierda!");
	// 		break;
	//
	// 	case SENSOR_RIGHT:
	// 		/* Objetivo a la derecha. */
	// 		Serial.println("Derecha!");
	// 		break;
	//
	// 	case SENSOR_FAIL:
	// 	default:
	// 		/* Si no tengo nada en frente, avanzo a paso tranqui... */
	// 		Serial.println("Indeterminado!");
	// 		break;
	// }
	// delay(1000);
	serialLoop();
}
