#include "mybsp_gpit.h"
#include "mybsp_sysinit.h"
#include "mybsp_gpio.h"

void epit1_init(uint32_t prescale, uint32_t settime)
{
	/* 设置UART3_RX_DATA为EPIT1输出管脚 */
	
	/* 设置EPIT1 CR寄存器 
	* bit[25:24] 	01 ipg66MHz
	* bit[23:22] 	01 输出管脚为翻转模式
	* bit[15:4 ] 	分频系数
	* bit[3]		1 forget and set 模式
	* bit[2]		1 使能中断
	* bit[0]		0 关闭定时器
	*/
	EPIT1->CR = 0;
	EPIT1->CR |= 1 << 24;
	EPIT1->CR |= 1 << 22;
	EPIT1->CR |= (prescale -1) << 4;
	EPIT1->CR |= 1 << 3;
	EPIT1->CR |= 1 << 2;
	
	/* 设置EPIT1 LOAD寄存器 */
	EPIT1->LR = settime;
	
	/* 设置EPIT1 CMPR寄存器 */
	EPIT1->CMPR = 0;
	
	/* 注册EPIT1中断服务函数 */
	SystemInstallIrqHandler(GPT1_IRQn, epit1_irqhadler, NULL);
	
	/* 使能EPIT1寄存器 */
	EPIT1->CR |= 1 << 0;
}

void epit1_irqhadler(uint32_t intnum, void *param)
{
	static bool ledstate;
	ledstate = ~ledstate;
	led_control(ledstate);
	
	/* 清除标志位 */
	EPIT1->SR |= 1 << 0;
}