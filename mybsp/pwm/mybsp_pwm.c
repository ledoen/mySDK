#include "mybsp_pwm.h"

/* pwm7初始化函数
 * 参数:
 * prescaler:	分频系数
 * period:		周期
 * duty:		高电平持续时间
 */
void pwm7_init(uint32_t prescaler, uint16_t period, uint16_t duty)
{
	/*设置管脚复用
	* 将CSI_VSYNC设置为PWM7输出
	*/
	IOMUXC_SetPinMux(IOMUXC_CSI_VSYNC_PWM7_OUT, 0);
	
	/*设置寄存器*/
	/* PWMCR寄存器 
	 * bit[17:16]	01			66Mhz ipg_clk
	 * bit[15:4]	prescaler-1 分频系数
	 * bit[3]					重启
	 * bit[0]					使能
	*/
	
	/*重启PWM7*/
	PWM7->PWMCR |= 1<<3;
	while(PWM7->PWMCR &= (1<<3));
	
	PWM7->PWMCR = (1<<16) | (prescaler - 1)<<4;
	
	/*设置周期*/
	PWM7->PWMPR = period - 2;
	
	/*设置高电平值*/
	pwm7_setduty(duty);
	
	/*使能PWM7*/
	PWM7->PWMCR |= 1<<0;
}

void pwm7_setduty(uint16_t value)
{
	/*确定FWE、CMP、ROV为0*/
	if((PWM7->PWMSR & (0x1<<4)) != 0)
		PWM7->PWMSR |= 0x1<<4;
	
	if((PWM7->PWMSR & (0x1<<5)) != 0)
		PWM7->PWMSR |= 0x1<<5;
	
	if((PWM7->PWMSR & (0x1<<6)) != 0)
		PWM7->PWMSR |= 0x1<<6;
	for(int i=0; i<3; i++){
		PWM7->PWMSAR = value;
	}
}