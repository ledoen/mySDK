#ifndef __MYBSP_GPT_H
#define __MYBSP_GPT_H

#include "commen_headers.h"

extern uint32_t flightTime;	/*用于保存起止时间*/

void gpt1_init(uint16_t prescaler);

void gpt1_irqhandler(uint32_t intnum, void *param);

#endif