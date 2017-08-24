/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    23-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca de funciones encargadas de la lectura e interpretación de
 *	los datos de los sensores.
 * ------------------------------------------------------------------------- */
 #include <Arduino.h>
 #include <config.h>
 #include <newPing.h>

 #include "sensorArray.h"

 NewPing sensorL(SENSOR_LEFT_TRIGGER, SENSOR_LEFT_ECHO, SENSOR_MAX_DISTANCE);
 NewPing sensorR(SENSOR_RIGHT_TRIGGER, SENSOR_RIGHT_ECHO, SENSOR_MAX_DISTANCE);
 NewPing sensorC(SENSOR_CENTER_TRIGGER, SENSOR_CENTER_ECHO, SENSOR_MAX_DISTANCE);

/* -------------------------------------------------------------------------
 *  Función para evaluar la direción del objetivo más cercano.
 * ------------------------------------------------------------------------- */
sensorResponse sensorEvaluate(void)
{
	unsigned long tempL = sensorL.ping_median(5, SENSOR_MAX_DISTANCE);
	unsigned long tempR = sensorR.ping_median(5, SENSOR_MAX_DISTANCE);
	unsigned long tempC = sensorC.ping_median(5, SENSOR_MAX_DISTANCE);

	if (tempL == 0)
	{
		tempL = 0xFFFF;
	}

	if (tempR == 0)
	{
		tempR = 0xFFFF;
	}

	if (tempC == 0)
	{
		tempC = 0xFFFF;
	}

	/*	Info de Debug....
	Serial.print("Left: ");
	Serial.print(tempL);
	Serial.print(" - Center: ");
	Serial.print(tempC);
	Serial.print(" - Right: ");
	Serial.println(tempR);
	*/

	/* Evaluo Left vs Right si es que ambas son válidas. */
	if (tempL < tempR)
	{
		/* Evaluo Left vs Center. */
		if (tempL < tempC)
		{
			/* El menor es Left. */
			return SENSOR_LEFT;
		} else {
			/* El menor es Center. */
			return SENSOR_CENTER;
		}

	/*	Evalúo los casos de Right solo si esa medida es válida.	*/
	} else {

		/* Evaluo Right vs Center. */
		if (tempR < tempC)
		{
			/* El menor es Right. */
			return SENSOR_RIGHT;
		} else {
			/* El menor es Center. */
			if (tempC != 0xFFFF)
			{
				return SENSOR_CENTER;
			} else {
				return SENSOR_FAIL;
			}
		}
	}

	/*	No hay medida válida. */
	return SENSOR_FAIL;
}
