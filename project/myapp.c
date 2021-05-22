#include "commen_headers.h"
#include "mybsp_sysinit.h"
#include "mybsp_gpit.h"
#include "mybsp_gpio.h"
#include "mybsp_uart.h"
#include "mybsp_pwm.h"
#include "mybsp_gpt.h"
#include "mybsp_pid.h"

int main(void)
{
	/*全局变量赋初值*/
	strindex = 0;
	rotorPulse = 500;
	
	system_Init();
	uart1_init();
	gpio_init();
	PID_init();
	epit1_init(66, 50000);
	pwm6_init(66, 10000, 50);
	pwm3_init(66, 20000, 1500);
	gpt1_init(66);
	
	uint8_t pri[] = "hello world!";
	UART1_WriteBlocking(pri, sizeof(pri)-1);	
	while(1)
	{
		
	}
}