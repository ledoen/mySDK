#include "mybsp_uart.h"

void uart1_init(void)
{
	/* 设置UCR1寄存器，使能UART1*/
	UART1->UCR1 = 1 << 0;
	
	/* 设置UCR2寄存器
	 * bit[14] 	1 	不使用RTS管脚
	 * bit[13] 	1	不使用CTS管脚
	 * bit[8] 	0	不使用奇偶校验
	 * bit[6]	0	1位停止位
	 * bit[5]	1	wordsize8位
	 * bit[2:1]	11	使能收发
	 * bit[0]	1	不重启
	*/
	UART1->UCR2 = 1<<14 | 1<<13 | 1<<5 | 1<<2 | 1<<1 | 1<<0;
	
	/* 设置UCR3寄存器，芯片手册要求第二位置1 */
	UART1->UCR3 = 1<<2;
	
	/* 设置波特率 */
	/* 设置分频系数
	 * UFCR[9:7] 1 分频系数为5
	 * 默认时钟为80MHz
	 * 分频后为16MHz
	*/
	UART1->UFCR |= 1 << 7;
	/* 设置UBIR寄存器及UBMIR寄存器
	 * 使波特率为115200
	*/
	UART1->UBMR = 624;
	UART1->UBIR = 71;
	
	/* 设置UCR4寄存器，使能ReceiveReady中断*/
	//UART1->UCR4 = 1;
	
	/* 注册中断服务函数 */
	/* 使能GIC相应UART1中断*/
	
	uint8_t pri[] = "hello world";
	UART1_WriteBlocking(pri,sizeof(pri)-1);	
}


void UART1_WriteBlocking(const uint8_t *data, size_t length)
{
    while (length--)
    {
        /* Wait for TX fifo valid.
         * This API can only ensure that the data is written into the data buffer but can't
         * ensure all data in the data buffer are sent into the transmit shift buffer.
         */
        while (!(UART1->USR2 & (1<<3)))
        {
        }
        UART1_WriteByte(*(data++));
    }
}