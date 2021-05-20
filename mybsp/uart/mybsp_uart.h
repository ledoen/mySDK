#ifndef __MYBSP_UART_H
#define __MYBSP_UART_H

#include "commen_headers.h"

extern uint32_t strindex;		/*用于读取一行数据*/
extern uint16_t rotorPulse;		/*用于保存读取到的舵机控制角度*/

/* 初始化UART 
 * 参数		无
 * 返回值	无
 */
void uart1_init(void);

/* 发送字符 */
static inline void UART1_WriteByte(uint8_t data)
{
	UART1->UTXD = data & 0xFF;
}

/* 发送字符串 */
void UART1_WriteBlocking(const uint8_t *data, size_t length);

/* 发送数字 */
void UART1_WriteNum(const uint32_t data);

/* 中断服务函数 */
void uart1_irqhandler(uint32_t intnum, void *param);

void DataProcess(const uint8_t *strdata);

#endif