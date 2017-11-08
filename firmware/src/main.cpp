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
	}
}
