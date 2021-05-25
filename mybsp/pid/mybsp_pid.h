#ifndef __MYBSP_PID_H
#define __MYBSP_PID_H

#include "commen_headers.h"
/*声明数据*/
extern float Kp, Ki, Kd;
extern int16_t targetTime;
float Pp, Ii, Dd, PID;
int16_t error, error_old;
uint16_t Dt;

/*数据赋初值*/
void PID_init(void);
/*PID计算*/
void PID_control(void);

#endif