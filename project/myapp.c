#include "commen_headers.h"
#include "mybsp_sysinit.h"
#include "mybsp_gpit.h"
#include "mybsp_gpio.h"
int main(void)
{
	system_Init();
	gpio_init();
	epit1_init(66, 2000000);
	//led_control(true);
	while(1)
	{
		
	}
	
}