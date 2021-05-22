#ifndef __MYBSP_PID_H
#define __MYBSP_PID_H

#include "commen_headers.h"
/*声明数据*/
extern uint16_t Kp, Kd;
extern float Ki;
extern uint32_t targetTime;
int16_t Pp, Ii, Dd, PID;
int16_t error, error_old;
uint16_t Dt;

/*数据赋初值*/
void PID_init(void);
/*PID计算*/
void PID_control(void);

#endif