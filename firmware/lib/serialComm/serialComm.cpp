/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    18-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca de funciones asociadas a la comunicación por puerto Serie.
 * ------------------------------------------------------------------------- */
#include <Arduino.h>
#include <config.h>
#include <SoftwareSerial.h>

#include "serialComm.h"

SoftwareSerial BT(COMMS_BT_RX, COMMS_BT_TX);

/* -------------------------------------------------------------------------
 *  Función de Inicializacion de funciones de puerto Serie.
 * ------------------------------------------------------------------------- */
void serialInit(void)
{
	/* Inicializo el puerto Serie para debug. */
	Serial.begin(9600);
	Serial.println("> Serial Comms Online");

	/* Inicializo el puerto del módulo BT. */
	BT.begin(9600);
	BT.print("AT+NAMEGeek-Xxxx");
}

/* -------------------------------------------------------------------------
 *  Función para determinar si hay datos en el buffer del BT.
 * ------------------------------------------------------------------------- */
sysResponse serialBTAvailable(void)
{
	/* Si BT recibió datos, retorno satisfactorio. */
	if(BT.available())
	{
		return SYS_SUCCESS;
	} else {
		return SYS_FAIL;
  	}
}

/* -------------------------------------------------------------------------
 *  Función para devolver un caracter leido por el canal BT.
 * ------------------------------------------------------------------------- */
sysResponse serialBTGetChar(char* data)
{
	/* Si BT recibió datos, devuelvo el dato. */
	if(BT.available())
	{
		*data =  BT.read();
		return SYS_SUCCESS;
	} else {
		return SYS_FAIL;
  	}
}

/* -------------------------------------------------------------------------
 *  Función de intercambio de data entre los puertos serie.
 * ------------------------------------------------------------------------- */
void serialLoopBack(void)
{
	/* Si BT recibió datos, los escribo en el puerto Serie. */
	if(BT.available())
	{
		Serial.write(BT.read());
	}

	/* Lo que llegue al serie lo mando a BT. */
	if(Serial.available())
	{
	   BT.write(Serial.read());
	}
}

/* -------------------------------------------------------------------------
 *  Función para enviar un string por el puerto de BT. Util para la
 *  configuración del mismo o debug del programa.
 * ------------------------------------------------------------------------- */
void sendBT(char* string)
{
	/*	Imprimo la cadena indicada por el canal BT.	*/
	BT.println(string);
}
