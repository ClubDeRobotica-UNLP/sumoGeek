/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    18-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Archivo de configuración. Declaración de pines y constantes principales
 *	de funcionamiento.
 * ------------------------------------------------------------------------- */
#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

/* Declaracion de Tipos de Respuesta. */
typedef enum {
	SYS_SUCCESS = 0,                /* Respuesta Exitosa. */
	SYS_FAIL                        /* Respuesta de Falla genérica. */
} sysResponse;

/* Declaración de pines de Motores. */
#define MOTOR_L_PIN_E	0          /* Enable del motor L. */
#define MOTOR_L_PIN_A	0          /*  Pin A del motor L. */
#define MOTOR_L_PIN_B	0          /*  Pin B del motor L. */

#define MOTOR_R_PIN_E	0          /* Enable del motor R. */
#define MOTOR_R_PIN_A	0          /*  Pin A del motor R. */
#define MOTOR_R_PIN_B	0          /*  Pin B del motor R. */

/* Declaración de pines de Sensores. */
#define SENSOR_LEFT_TRIGGER     2  /*  Pin Trigger del sensor Izquierdo. */
#define SENSOR_LEFT_ECHO        3  /*  Pin Echo del sensor Izquierdo. */

#define SENSOR_RIGHT_TRIGGER	4  /*  Pin Trigger del sensor Derecho. */
#define SENSOR_RIGHT_ECHO       5  /*  Pin Echo del sensor Derecho. */

#define SENSOR_CENTER_TRIGGER   6  /*  Pin Trigger del sensor Central. */
#define SENSOR_CENTER_ECHO      7  /*  Pin Echo del sensor Central. */

#define SENSOR_MAX_DISTANCE    50  /*  Distancia máxima a evaluar. */

#endif	/* SRC_CONFIGURATION_H_ */
