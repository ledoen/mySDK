#include "mybsp_gpio.h"

/**
 * gpio_init() - 初始化控制的GPIO
 * 
 * @param: 无
 * @return: 无
 */
void gpio_init(void)
{
	/* 设置GPIO1_IO09 */
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO09_GPIO1_IO09, 0);

    /**
     * 配置GPIO1_IO09引脚电气属性 
     * bit[16]: 0 关闭HYS
     * bit[15:14]: 00 默认下拉
     * bit[13]: 0 keeper
     * bit[12]: 1 pull/keeper使能
     * bit[11]: 0 禁止开路输出
     * bit[10:8]: 000 reserved
     * bit[7:6]: 10 速度为100MHz
     * bit[5:3]: 110 驱动能力为R0/6
     * bit[2:1]: 00 reserved
     * bit[0]: 0 低摆率
     */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO09_GPIO1_IO09, 0x10b0);

    /* 设置GPIO的方向为输出 */
    GPIO1->GDIR |= (1 << 9);

    /* 设置GPIO1_IO02引脚输出高电平 */
    GPIO1->DR &= ~(1 << 9);
}

/* 控制连接在GPIO1_09管脚上的led */
void led_control(bool led)
{
	if(led)
		GPIO1->DR |= (1 << 9);
	else
		GPIO1->DR &= ~(1 << 9);	
}