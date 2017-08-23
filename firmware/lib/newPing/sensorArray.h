/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    18-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Header del módulo de lectura e interpretación de datos de los sensores.
 * ------------------------------------------------------------------------- */
#ifndef SRC_LIB_SENSORARRAY_H_
#define SRC_LIB_SENSORARRAY_H_

/* Declaracion de Tipos de Respuesta. */
typedef enum {
 	SENSOR_CENTER = 0,         /* Se detecta el objetivo al frente. */
 	SENSOR_LEFT,               /* Se detecta el objetivo a la izquierda. */
	SENSOR_RIGHT,              /* Se detecta el objetivo a la derecha. */
	SENSOR_FAIL                /* Ocurrió un error en la detección. */
} sensorResponse;

/* Declaración de Funciones. */
sensorResponse sensorEvaluate(void);

#endif	/* SRC_LIB_SENSORARRAY_H_ */
