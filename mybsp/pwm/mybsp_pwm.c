#include "mybsp_pwm.h"
#include "mybsp_uart.h"

/* pwm6初始化函数
 * 参数:
 * prescaler:	分频系数
 * period:		周期
 * duty:		高电平持续时间
 */
void pwm6_init(uint32_t prescaler, uint16_t period, uint16_t duty)
{
	/*设置管脚复用
	* 将CSI_VSYNC设置为PWM6输出
	*/
	IOMUXC_SetPinMux(IOMUXC_JTAG_TDI_PWM6_OUT, 0);
	
	/*设置寄存器*/
	/* PWMCR寄存器 
	 * bit[17:16]	01			66Mhz ipg_clk
	 * bit[15:4]	prescaler-1 分频系数
	 * bit[3]					重启
	 * bit[0]					使能
	*/
	
	/*重启PWM6*/
	
	PWM6->PWMCR |= 1<<3;
	while(PWM6->PWMCR &= (1<<3));
	
	PWM6->PWMCR = (1<<16) | (prescaler - 1)<<4;
	
	/*设置高电平值*/
	pwm6_setduty(duty);
	
	/*设置周期*/
	PWM6->PWMPR = period - 2;
	
	/*使能PWM6*/
	PWM6->PWMCR |= 1<<0;
}

void pwm6_setduty(uint16_t value)
{
	/*确定FWE、CMP、ROV为0*/
	
	if((PWM6->PWMSR & (0x1<<4)) != 0)
		PWM6->PWMSR |= 0x1<<4;
	
	if((PWM6->PWMSR & (0x1<<5)) != 0)
		PWM6->PWMSR |= 0x1<<5;
	
	if((PWM6->PWMSR & (0x1<<6)) != 0)
		PWM6->PWMSR |= 0x1<<6;
	
	for(int i=0; i<3; i++){
		PWM6->PWMSAR = value;
	}
}

/*设置PWM3寄存器，用于控制舵机*/
void pwm3_init(uint32_t prescaler, uint16_t period, uint16_t duty)
{
	/*设置管脚复用
	* 将GPIO1_04设置为PWM3输出
	*/
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO04_PWM3_OUT, 0);
	
	/*设置寄存器*/
	/* PWMCR寄存器 
	 * bit[17:16]	01			66Mhz ipg_clk
	 * bit[15:4]	prescaler-1 分频系数
	 * bit[3]					重启
	 * bit[0]					使能
	*/
	
	/*重启PWM6*/
	
	PWM3->PWMCR |= 1<<3;
	while(PWM3->PWMCR &= (1<<3));
	
	PWM3->PWMCR = (1<<16) | (prescaler - 1)<<4;
	
	/*设置高电平值*/
	pwm3_setduty(duty);
	
	/*设置周期*/
	PWM3->PWMPR = period - 2;
	
	/*使能PWM6*/
	PWM3->PWMCR |= 1<<0;
}

void pwm3_setduty(uint16_t value)
{
	/*确定FWE、CMP、ROV为0*/
	
	if((PWM3->PWMSR & (0x1<<4)) != 0)
		PWM3->PWMSR |= 0x1<<4;
	
	if((PWM3->PWMSR & (0x1<<5)) != 0)
		PWM3->PWMSR |= 0x1<<5;
	
	if((PWM3->PWMSR & (0x1<<6)) != 0)
		PWM3->PWMSR |= 0x1<<6;
	
	for(int i=0; i<3; i++){
		PWM3->PWMSAR = value;
	}
}