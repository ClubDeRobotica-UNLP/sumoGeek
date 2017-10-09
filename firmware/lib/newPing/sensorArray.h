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

#define US_ROUNDTRIP_CM_FLOAT 58.275

/* Declaracion de Tipos de Respuesta. */
typedef enum {
 	SENSOR_CENTER = 0,         /* Se detecta el objetivo al frente. */
 	SENSOR_LEFT,               /* Se detecta el objetivo a la izquierda. */
	SENSOR_RIGHT,              /* Se detecta el objetivo a la derecha. */
	SENSOR_FAIL                /* Ocurrió un error en la detección. */
} sensorResponse;

/* Declaración de Funciones. */
void sensorInit(void);
sensorResponse sensorEvaluate(void);
sysResponse sensorLateralDistance(float*, float*);
float sensorConvert_cm(unsigned long);

#endif	/* SRC_LIB_SENSORARRAY_H_ */
