#include "mybsp_pid.h"
#include "mybsp_gpt.h"
#include "mybsp_uart.h"

float Kp, Ki, Kd;
int16_t targetTime;

void PID_init(void)
{
	targetTime = 1000;
	Kp = 0.7;
	Ki = 0.02;
	Kd = 20;
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
	Pp = Kp * error;
	if((error > -500) && (error < 500)){
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
	
	UART1_WriteByte('e');
	UART1_WriteNum(0xffff0000+error);		/*加上0xffff0000，将int16转换为uint32*/
	UART1_WriteByte('\r');
	UART1_WriteByte('\n');
	
	uint32_t Ks = ((uint32_t)(Kp*10))<<20 | ((uint32_t)(Ki*100))<<10 | (uint32_t)(Kd*10);
	UART1_WriteByte('K');
	UART1_WriteNum(Ks);
	UART1_WriteByte('\r');
	UART1_WriteByte('\n');
}
