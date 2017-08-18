/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    18-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca para el control de los motores.
 * ------------------------------------------------------------------------- */
#ifndef SRC_LIB_MOTORLIB_H_
#define SRC_LIB_MOTORLIB_H_

typedef struct motorStruct {
	byte motorPinA;
	byte motorPinB;
	byte motorPinEnable;
	int  motorSpeed;
	bool motorRunning;
} motorControlBlock;

/* Variables Externas. */
extern motorControlBlock* motorR;
extern motorControlBlock* motorL;

/* Funciones de Incializacion de la estructura de control del Motor. */
motorControlBlock* motorInit(byte pinEnable, byte pinA, byte pinB);

/* Funciones de control de motores. */
void motorStop(motorControlBlock* motor);
void motorStart(motorControlBlock* motor);
void motorSetSpeed(motorControlBlock* motor, int pwmVal);

#endif	/* SRC_LIB_MOTORLIB_H_ */
