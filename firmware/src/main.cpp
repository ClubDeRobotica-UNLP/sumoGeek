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
	/* Chequeo que los CNY no me den que estoy en la linea.  */

	/* Sensor Izquierdo, si detecta giro a la izquierda 90º. */

	/* Sensor Derecho, si detecta giro a la derecha 90º. */

	/* Sensor Frente, si detecta encaro a fondo. */

	/* Si no tengo nada en frente, avanzo a paso tranqui... */
}
