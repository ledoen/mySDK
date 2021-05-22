#include "mybsp_pid.h"
#include "mybsp_gpt.h"
#include "mybsp_uart.h"

uint16_t Kp, Kd;
float Ki;
uint32_t targetTime;

void PID_init(void)
{
	targetTime = 900;
	Kp = 1;
	Ki = 1;
	Kd = 5;
	Dt = 5;
	
	Pp = 0;
	Ii = 0;
	Dd = 0;
	
	PID = 0;
	error = 0;
	error_old = 0;
	
}

void PID_control(void)
{
	error = flightTime - targetTime;
	Pp = Kp * error;
	if(error > -150 && error < 150){
		Ii += (int16_t)Ki * error; 
	}
	else{
		Ii = 0;
	}
	Dd = Kd * (error - error_old)/Dt;
	PID = Pp + Ii + Dd;
	
	error_old = error;
	
	if(PID > 2000)
		PID = 2000;
	else if(PID < -2000)
		PID = -2000;
	
	rotorPulse = -PID / 2 + 1500 ;  
}
