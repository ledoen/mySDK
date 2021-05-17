#ifndef __MYBSP_PWM_H
#define __MYBSP_PWM_H

#include "commen_headers.h"

/* pwm7初始化函数
 * 参数:
 * prescaler:	分频系数
 * period:		周期
 * duty:		高电平持续时间
 */
void pwm7_init(uint32_t prescaler, uint16_t period, uint16_t duty);

/*设置PWMSAR寄存器*/
void pwm7_setduty(uint16_t value);

#endif