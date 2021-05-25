#include "mybsp_gpt.h"
#include "mybsp_sysinit.h"
#include "mybsp_uart.h"
#include "mybsp_pwm.h"

uint32_t flightTime = 0;

void gpt1_init(uint16_t prescaler)
{
	/*设置管脚复用
	 * 设置UART2_TX_DATA为GPT1_CAPTURE1
	*/
	IOMUXC_SetPinMux(IOMUXC_UART2_TX_DATA_GPT1_CAPTURE1, 0);
	
	/*设置寄存器*/
	/*重启GPT1,重置各寄存器*/
	GPT1->CR = 0;
	GPT1->CR |= 1<<15;
	while(GPT1->CR & 1<<15);
	
	/*CR寄存器
	 *bit[17:16]	0x3	Capture1双边沿触发
	 *bit[9]		1	FreeRun Mode
	 *bit[8:6]		1	66MHz ipg_clk
	 *bit[0]		0	使能
	*/
	GPT1->CR = (0x3<<16) | (1<<9) | (1<<6);
	
	/*设置分频系数*/
	GPT1->PR = (prescaler - 1)<<0;
	
	/*设置IR寄存器，使能Capture1中断*/
	GPT1->IR = 1<<3;
	
	/*注册中断服务函数*/
	SystemInstallIrqHandler(GPT1_IRQn, gpt1_irqhandler, NULL);
	
	/*设置GIC寄存器，使能GIC中断*/
	GIC_EnableIRQ(GPT1_IRQn);
	
	/*使能GPT1*/
	GPT1->CR |= 1<<0;
}

void gpt1_irqhandler(uint32_t intnum, void *param)
{
	/*判断是上升沿还是下降沿*/
	static uint16_t edge_status = 0;
	edge_status++;
	static uint32_t startTime = 0;	/*用于保存起始时间*/
	uint32_t time = GPT1->ICR[0];
	
	if(edge_status%2 == 1)
		startTime = time;			/*上升沿*/
	else
		flightTime = time - startTime;	/*下降沿*/
	
	if(flightTime > 5000)
		flightTime = 10000 - flightTime;
	/*
	UART1_WriteNum(flightTime);
	UART1_WriteByte('\r');
	UART1_WriteByte('\n');

	if(flightTime <= 294){
		pwm3_setduty(500);
	}
	else if(flightTime > 294 && flightTime < 1471){
		pwm3_setduty(flightTime*2000/1177);
	}
	else if(flightTime >= 1471){
		pwm3_setduty(2500);
	}
	*/
	
	/*清空中断标志位*/
	GPT1->SR |= 1<<3;
}