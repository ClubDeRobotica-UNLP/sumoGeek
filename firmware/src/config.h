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
	STATE_ATTACK,                   /* Estado de Ataque.             */
    STATE_HUNT,                     /* Estado de búsqueda.           */
    STATE_LINE                      /* Estado de detección de línea. */
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
#define MOTOR_CRUISE_SPEED    155  /* Velocidad para movimientos.  */
#define MOTOR_ATTACK_SPEED    250  /* Velocidad de ataque.         */
#define MOTOR_TURN_SPEED      200  /* Velocidad de giro.           */

#define MOTION_TURN_TIME_90   600  /* Tiempo en ms para girar 90º.          */
#define MOTION_ATTACK_TIME   1000  /* Tiempo de ataque antes de retroceder. */

/* Velocidades de modo RC. */
#define MOTOR_RC_BASE_SPEED   250

/* Declaración de pines de Sensores. */
#define SENSOR_LEFT_TRIGGER    16  /*  Pin Trigger del sensor Izquierdo. */
#define SENSOR_LEFT_ECHO       17  /*  Pin Echo del sensor Izquierdo.    */

#define SENSOR_RIGHT_TRIGGER   18  /*  Pin Trigger del sensor Derecho.   */
#define SENSOR_RIGHT_ECHO      19  /*  Pin Echo del sensor Derecho.      */

#define SENSOR_CENTER_TRIGGER  14  /*  Pin Trigger del sensor Central.   */
#define SENSOR_CENTER_ECHO     15  /*  Pin Echo del sensor Central.      */

#define SENSOR_MAX_DISTANCE    50

/* Declaración de pines del CNY70 */
#define SENSOR_CNY_PIN          2
#define SENSOR_CNY_BLACK        1

/* Declaracion de pines del módulo BT. */
#define COMMS_BT_RX    11
#define COMMS_BT_TX    10

/* PARA EL RESOLVEDOR MODIFICAR ACA */
/* Declaraciones del maze-resolver */
#define LEFT_WALL 0
#define RIGHT_WALL 1

#define WALL_ALGHM LEFT_WALL //seguidor de pared izquierda o derecha

// Definiciones del control
#define CONTROL_PERIOD 20
#define CONTROL_DEADZONE 0.25   // histeresis
#define NOMINAL_SPEED 180
#define CONTROL_ACTION 100 // Accion de control
#define WALL_REF 7.5
#define CENTER_REF 6.0
#define CENTER_DETECT_PAUSE 300 // tiempo de detencion al detectar frente


#define CONTROL_TURN_DELAY 700
#define CONTROL_TURN_SPEED 200
#define CONTROL_TURN_SPEED_OFFSET 50


#define SENSORL_MAX_DISTANCE    20  /*  Distancia máxima a evaluar.       */
#define SENSORR_MAX_DISTANCE    20  /*  Distancia máxima a evaluar.       */
#define SENSORC_MAX_DISTANCE    7.5  /*  Distancia máxima a evaluar.       */

#if WALL_ALGHM
	#define MAZE_RESOLVER_MEASURE right_wall_funct(); // DERECHA
#else
	#define MAZE_RESOLVER_MEASURE left_wall_funct();  // IZQUIERDA
#endif

#endif	/* SRC_CONFIGURATION_H_ */
