#include "mybsp_pid.h"
#include "mybsp_gpt.h"
#include "mybsp_uart.h"

float Kp, Ki, Kd;
int16_t targetTime;

void PID_init(void)
{
	targetTime = 1000;
	Kp = 1.5;
	Ki = 0.04;
	Kd = 0.5;
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
	error = (int16_t)(flightTime - targetTime);
	Pp = (int16_t)Kp * error;
	if((error > -400) && (error < 400)){
		Ii += Ki * error; 
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
	
	rotorPulse = (int16_t)(-PID / 2) + 1500 ;
	
	// UART1_WriteByte('p');
	// UART1_WriteNum((uint32_t)(Kp*10));
	// UART1_WriteByte('\r');
	// UART1_WriteByte('\n');
	UART1_WriteByte('i');
	UART1_WriteNum((uint32_t)(Ki*100));
	UART1_WriteByte('\r');
	UART1_WriteByte('\n');
	UART1_WriteByte('d');
	UART1_WriteNum((uint32_t)(Kd*10));
	UART1_WriteByte('\r');
	UART1_WriteByte('\n');
	UART1_WriteByte('D');
	UART1_WriteNum((uint32_t)(Dd));
	UART1_WriteByte('\r');
	UART1_WriteByte('\n');
}
