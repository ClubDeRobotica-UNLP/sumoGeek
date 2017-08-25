/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Germán Sc.
 *  Date:    25-08-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca de funciones asociadas al movimiento del robot.
 * ------------------------------------------------------------------------- */
#include <Arduino.h>
#include <motorLib.h>
#include <config.h>

#include "motionCore.h"

/* -------------------------------------------------------------------------
 *  Función de Inicializacion del módulo de movimiento.
 * ------------------------------------------------------------------------- */
 void motionInit(void)
 {
	 /* Inicializo los bloques de control de los motores. */
	 motorL = motorInit(MOTOR_L_PIN_E, MOTOR_L_PIN_A, MOTOR_L_PIN_B);
	 motorR = motorInit(MOTOR_R_PIN_E, MOTOR_R_PIN_A, MOTOR_R_PIN_B);

	 /* Habilitos los motores con 0 velocidad. */
	 motorSetSpeed(motorL, 0);
	 motorSetSpeed(motorR, 0);

	 motorStart(motorL);
	 motorStart(motorR);
 }

 /* -------------------------------------------------------------------------
  *  Función de movimiento al no detectar la direccion del objetivo.
  * ------------------------------------------------------------------------- */
void motionCruise(void)
{
	/* Avanzo a velocidad de crucero. */
	motorSetSpeed(motorL, MOTOR_CRUISE_SPEED);
	motorSetSpeed(motorR, MOTOR_CRUISE_SPEED * MOTOR_LR_OFFSET);
}

/* -------------------------------------------------------------------------
 *  Función de embestida cuando el objetivo está en frente.
 * ------------------------------------------------------------------------- */
void motionFullOn(void)
{
	/* Embisto a toda velocidad. */
	motorSetSpeed(motorL, MOTOR_ATTACK_SPEED);
	motorSetSpeed(motorR, MOTOR_ATTACK_SPEED * MOTOR_LR_OFFSET);
}

/* -------------------------------------------------------------------------
 *  Función de giro.
 * ------------------------------------------------------------------------- */
void motionTurn(motionDirection direction, motionAngle angle)
{
	/* Variables. */
	int tempSpeed;

	/* Calculo la velocidad y la aplico a los motores. */
	tempSpeed = MOTOR_TURN_SPEED * direction;

	motorSetSpeed(motorL, tempSpeed);
	motorSetSpeed(motorR, -(tempSpeed * MOTOR_LR_OFFSET));

	/* Espero el tiempo especificado. */
	delay( angle * MOTOR_TURN_TIME);

	/* Dejo de girar. */
	motorSetSpeed(motorL, 0);
	motorSetSpeed(motorR, 0);
}


/* -------------------------------------------------------------------------
 *  Función de Testeo.
 * ------------------------------------------------------------------------- */
void motionTest(void)
{
	/* Inicio de función de prueba. */
	delay(1500);
	Serial.println("Prueba de movimiento en marcha.\n");

	/* Avanzo a paso crucero y hace un cuadrado girando a la izquierda. */
	Serial.println("Avanzando despacio.");
	motionCruise();
	delay(1000);

	Serial.println("Giro de 90º a la izquierda.");
	motionTurn(MOTION_LEFT, MOTION_90);

	Serial.println("Avanzando despacio.");
	motionCruise();
	delay(1000);

	Serial.println("Giro de 90º a la izquierda.");
	motionTurn(MOTION_LEFT, MOTION_90);

	Serial.println("Avanzando despacio.");
	motionCruise();
	delay(1000);

	Serial.println("Giro de 90º a la izquierda.");
	motionTurn(MOTION_LEFT, MOTION_90);

	Serial.println("Avanzando despacio.");
	motionCruise();
	delay(1000);

	Serial.println("Giro de 90º a la izquierda.");
	motionTurn(MOTION_LEFT, MOTION_90);

	/* Prueba del modo embestida, mitad de tiempo. */
	Serial.println("Avanzando fuerte.");
	motionFullOn();
	delay(500);

	/* Giro de 180 grados a la derecha, y vuelvo a la posición inicial. */
	Serial.println("Giro de 180º a la derecha.");
	motionTurn(MOTION_RIGHT, MOTION_180);

	Serial.println("Vuelta al punto inicial.");
	motionCruise();
	delay(1000);

	/* Fin de la prueba, freno los motores y cuelgo el programa. */
	motorSetSpeed(motorL, 0);
	motorSetSpeed(motorR, 0);

	Serial.println("Fin de la prueba.");
	while(1);
}
