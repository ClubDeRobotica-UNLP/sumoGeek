/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    18-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca de funciones asociadas a la comunicación por puerto Serie.
 * ------------------------------------------------------------------------- */
#ifndef SRC_LIB_SERIALPARSER_H_
#define SRC_LIB_SERIALPARSER_H_

#include <Arduino.h>
#include <config.h>

/* Función de Inicialización. */
void serialInit(void);
void serialLoopBack(void);

sysResponse serialBTAvailable(void);

#endif	/* SRC_LIB_SERIALPARSER_H_ */
