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
	SYS_SUCCESS = 0,                /* Respuesta Exitosa.           */
	SYS_FAIL                        /* Respuesta de Falla genérica. */
} sysResponse;

/* Declaracion de Estados. */
typedef enum {
	STATE_ATTACK,
	STATE_HUNT,
	STATE_LINE
} sysState;


/* Declaración de pines y constantes de Motores. */
#define MOTOR_L_PIN_E	8          /* Enable del motor L. */
#define MOTOR_L_PIN_A	5          /*  Pin A del motor L. */
#define MOTOR_L_PIN_B	6          /*  Pin B del motor L. */

#define MOTOR_R_PIN_E	7          /* Enable del motor R. */
#define MOTOR_R_PIN_A	3          /*  Pin A del motor R. */
#define MOTOR_R_PIN_B	4          /*  Pin B del motor R. */

#define MOTOR_LR_OFFSET   1  /* Offset para igualar velocidad de motores. */

/* Velocidades de modo Autónomo. */
#define MOTOR_CRUISE_SPEED    150  /* Velocidad para movimientos.  */
#define MOTOR_ATTACK_SPEED    250  /* Velocidad de ataque.         */
#define MOTOR_TURN_SPEED      200  /* Velocidad de giro.           */

#define MOTION_TURN_TIME_90   400  /* Tiempo en ms para girar 90º. */

/* Velocidades de modo RC. */
#define MOTOR_RC_BASE_SPEED   250

/* Declaración de pines de Sensores. */
#define SENSOR_LEFT_TRIGGER    18  /*  Pin Trigger del sensor Izquierdo. */
#define SENSOR_LEFT_ECHO       19  /*  Pin Echo del sensor Izquierdo.    */

#define SENSOR_RIGHT_TRIGGER   16  /*  Pin Trigger del sensor Derecho.   */
#define SENSOR_RIGHT_ECHO      17  /*  Pin Echo del sensor Derecho.      */

#define SENSOR_CENTER_TRIGGER  14  /*  Pin Trigger del sensor Central.   */
#define SENSOR_CENTER_ECHO     15  /*  Pin Echo del sensor Central.      */

#define SENSOR_MAX_DISTANCE    50  /*  Distancia máxima a evaluar.       */

/* Declaración de pines del CNY70 */
#define SENSOR_CNY_PIN          2

#define SENSOR_CNY_BLACK        1

/* Declaracion de pines del módulo BT. */
#define COMMS_BT_RX    11
#define COMMS_BT_TX    10

#endif	/* SRC_CONFIGURATION_H_ */
