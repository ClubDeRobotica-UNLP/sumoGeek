/* -------------------------------------------------------------------------
 *  Project: sumoGeek
 *  Author:  Jander
 *  Date:    07-10-17
 *  Version: 0.1
 *
 *  Description:
 *  Biblioteca de funciones asociadas al controlador
 * ------------------------------------------------------------------------- */
#ifndef SRC_LIB_CONTROLLIB_H_
#define SRC_LIB_CONTROLLIB_H_

//#define INFINITY 1.0/0.0

/* Clase controlador*/
class Controller {
	public:
		Controller(unsigned int T,float saturation_min = -INFINITY, float saturation_max = INFINITY);
    float sat_max;
    float sat_min;
		float period_ms;
		void setParameters(float Kp,float Ki, float Kd, unsigned int N=8);
		float compute(float error);
		void setTimer(void (*userFunction)());
		void startTimer(void);
		void stopTimer(void);
  private:
    float KD1;
    float KD2;
    float KI;
    float KP;
    float D0;
    float I1;
		unsigned int countTimer;
		void configure(float Kp,float Ki, float Kd, unsigned int N);
		void isrTimer(void);
  };

#endif	/* SRC_LIB_CONTROLLIB_H_ */
