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

#include "serialComm.h"

/* -------------------------------------------------------------------------
 *  Función de Inicializacion de funciones de puerto Serie.
 * ------------------------------------------------------------------------- */
void serialInit(void)
{
  Serial.begin(9600);
  Serial.println("> Serial Comms Online");
}
