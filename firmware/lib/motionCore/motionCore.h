/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    25-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Header de la biblioteca de funciones asociadas al movimiento del robot.
 * ------------------------------------------------------------------------- */
#ifndef SRC_LIB_MOTIONCORE_H_
#define SRC_LIB_MOTIONCORE_H_

typedef enum {
	MOTION_LEFT   = -1,             /* Respuesta Exitosa. */
	MOTION_RIGHT  = 1               /* Respuesta de Falla genérica. */
} motionDirection;

/* Declaracion de funciones. */
void motionInit(void);
void motionForward(uint8_t speed);
void motionBackwards(uint8_t speed);
void motionDifferential(int speedL, int speedR);
void motionTurn(motionDirection direction, unsigned int timeInMs);

void motionRcOperation(char input);
int saturate(int speed);

void motionTest(void);


#endif	/* SRC_LIB_SERIALPARSER_H_ */
