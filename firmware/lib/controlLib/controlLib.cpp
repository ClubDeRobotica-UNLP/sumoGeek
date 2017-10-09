/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Jander.
 *  Date:    07-10-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca de funciones asociadas al controlador
 * ------------------------------------------------------------------------- */
#include "Arduino.h"
#include "controlLib.h"

unsigned int control_countTimer = 0;
unsigned int control_period_ms = 1;
void (*control_userCallBack)();


Controller::Controller(unsigned int T, float saturation_min, float saturation_max){
	period_ms = T;
	control_period_ms = period_ms;

	sat_max = saturation_max;
	sat_min = saturation_min;
}

/* -------------------------------------------------------------------------
 *  Función de cálculo del controlador
 * ------------------------------------------------------------------------- */
float Controller::compute(float error){
	float control_I, control_P, control_D, control;

	control_I = I1;
	control_P = KP*error;
	control_D = KD1*(D0 - KD2*error);

	D0 = control_D;
	I1 = KI*error + control_I;

	control = control_P + control_D + control_I;

  /* Control saturation + Anti-Windup*/
	if(control > sat_max){
		control = sat_max;
		I1 = control_I;
	} else if(control < sat_min){
		control = sat_min;
		I1 = control_I;
	}

	return control;
}

void Controller::configure(float Kp,float Ki, float Kd, unsigned int N){
	KP = Kp;
	KI= period_ms*Ki/1000.0;
	KD1 = Kd/(Kd + N*(period_ms/1000.0));
	KD2 = Kp*N;
	I1 = 0;
	D0 = 0;
}

void Controller::setParameters(float Kp,float Ki, float Kd, unsigned int N){
		configure(Kp, Ki, Kd, N);
}

void Controller::setTimer(void (*userFunction)()){
  cli();
  TCCR1A = 0;
  TCCR1B = 0;   //Modo CTC
  OCR1A = 249;           // 4us*(249+1) = 1 ms

  TCNT1=0;
	if(userFunction != NULL)
		control_userCallBack=userFunction;
	//Controller::isrTimer2=isrTimer;

  sei();
}

void Controller::startTimer(void){
 	 cli();
	 TCCR1B = (1<<CS11)|(1<<CS10)|(1<<WGM12);	 //set timer
	 TIMSK1 = (1<<OCIE1A); //set interrupt
	 sei();
}

void Controller::stopTimer(void){
	 cli();
	 TCCR1B = 0; //stop timer
	 TIMSK1 = 0; //clear interrupt
	 sei();
}

void Controller::isrTimer(void){
//countTimer++;
//if(countTimer>=period_ms){
	//userCallBack();
	//countTimer=0;
//}
}

ISR(TIMER1_COMPA_vect){
	control_countTimer++;
	if(control_countTimer>=control_period_ms){
		if(control_userCallBack != NULL)
			control_userCallBack();
		control_countTimer=0;
	}
}
