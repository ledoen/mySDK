#ifndef __MYBSP_UART_H
#define __MYBSP_UART_H

#include "commen_headers.h"

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

#endif