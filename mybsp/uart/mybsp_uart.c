#include "mybsp_uart.h"
#include "mybsp_sysinit.h"

void uart1_init(void)
{
	/* 设置管脚 */
	IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
	IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
	
	/* 设置UCR1寄存器，关闭UART1 */
	UART1->UCR1 = 0;
	
	/* 重启UART1 */
	UART1->UCR2 = 0;
	while(!(UART1->UCR2 & 1<<0));
	
	/* 设置UCR2寄存器
	 * bit[14] 	1 	不使用RTS管脚
	 * bit[13] 	1	不使用CTS管脚
	 * bit[8] 	0	不使用奇偶校验
	 * bit[6]	0	1位停止位
	 * bit[5]	1	wordsize8位
	 * bit[2:1]	11	使能收发
	 * bit[0]	1	不重启
	*/
	//UART1->UCR2 = 0x6027;
	UART1->UCR2 = 1<<14 | 1<<13 | 1<<5 | 1<<2 | 1<<1 | 1<<0;
	
	/* 设置UCR3寄存器，芯片手册要求第二位置1 */
	UART1->UCR3 = 1<<2;
	
	/* 设置波特率 */
	/* 设置分频系数
	 * UFCR[9:7] 1 分频系数为5
	 * 默认时钟为80MHz
	 * 分频后为16MHz
	*/
	UART1->UFCR = 1<<7;
	/* 设置UBIR寄存器及UBMIR寄存器
	 * 使波特率为115200
	*/
	UART1->UBIR = 0x47;
	UART1->UBMR = 0x270;

	/* 设置UCR4寄存器，使能RDR中断*/
	UART1->UCR4 = 1;
	
	/* 注册中断服务函数 */
	SystemInstallIrqHandler(UART1_IRQn, uart1_irqhandler, NULL);
	
	/* 使能GIC相应UART1中断*/
	GIC_EnableIRQ(UART1_IRQn);
	
	/* 设置UCR1寄存器，使能UART1*/
	UART1->UCR1 = 1 << 0;
	
	UART1_WriteByte('\r');
	UART1_WriteByte('\n');
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

void uart1_irqhandler(uint32_t intnum, void *param)
{
	/* 读取URXD寄存器 */
	uint8_t data;
	data = UART1->URXD & 0xff;
	
	/* 回显 */
	if(data == 0xd)
		UART1_WriteByte(0xa);
	UART1_WriteByte(data);
}

void UART1_WriteNum(const uint32_t data)
{
	/* 从高到低取出每四位进行处理，共进行8次 */
	uint8_t ByteData;
	for(int i=0; i<8; i++){
		ByteData = ((data >> (28-i*4)) & 0xf);	/* 取出每4位 */
		switch(ByteData){
			case 0x0:{
				UART1_WriteByte('0');
				break;
			}
			case 0x1:{
				UART1_WriteByte('1');
				break;
			}
			case 0x2:{
				UART1_WriteByte('2');
				break;
			}
			case 0x3:{
				UART1_WriteByte('3');
				break;
			}
			case 0x4:{
				UART1_WriteByte('4');
				break;
			}
			case 0x5:{
				UART1_WriteByte('5');
				break;
			}
			case 0x6:{
				UART1_WriteByte('6');
				break;
			}
			case 0x7:{
				UART1_WriteByte('7');
				break;
			}
			case 0x8:{
				UART1_WriteByte('8');
				break;
			}case 0x9:{
				UART1_WriteByte('9');
				break;
			}
			case 0xa:{
				UART1_WriteByte('A');
				break;
			}
			case 0xb:{
				UART1_WriteByte('B');
				break;
			}
			case 0xc:{
				UART1_WriteByte('C');
				break;
			}
			case 0xd:{
				UART1_WriteByte('D');
				break;
			}
			case 0xe:{
				UART1_WriteByte('E');
				break;
			}
			case 0xf:{
				UART1_WriteByte('F');
				break;
			}
		}
	}
}