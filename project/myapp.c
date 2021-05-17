#include "commen_headers.h"
#include "mybsp_sysinit.h"
#include "mybsp_gpit.h"
#include "mybsp_gpio.h"
#include "mybsp_uart.h"
#include "mybsp_pwm.h"

int main(void)
{
	system_Init();
	uart1_init();
	gpio_init();
	epit1_init(66, 2000000);
	pwm7_init(66, 20000, 500);
	
	uint8_t pri[] = "hello world!";
	UART1_WriteBlocking(pri, sizeof(pri)-1);	
	while(1)
	{
		
	}
}