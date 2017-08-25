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

typedef enum {
	MOTION_90 = 1,                /* Giro de 90 grados. */
	MOTION_180                    /* Gito de 180 grados. */
} motionAngle;

/* Declaracion de funciones. */
void motionInit(void);
void motionCruise(void);
void motionFullOn(void);
void motionTurn(motionDirection direction, motionAngle angle);

void motionTest(void);


#endif	/* SRC_LIB_SERIALPARSER_H_ */
