/*
 * dsp_notify_fpga.c
 *
 *  Created on: 2015-11-2
 *      Author: jdy
 */


/* DSP通知FPGA发送数据  */

#include "dsp_fpga_notify.h"
#include "utils.h"

// DSP通知fpga发送
void DspFpgaNotifySend(unsigned int message)
{
	if (START == message)
	{
		GPIOPinWrite(SOC_GPIO_0_REGS, 143, GPIO_PIN_HIGH);
	}
	else
	{
		GPIOPinWrite(SOC_GPIO_0_REGS, 143, GPIO_PIN_LOW);
	}
}

// (DSP控制fpga配置，使用的是GPIO5[13]引脚)  现在要用到EMIIFA，GPIO5[13]被emifa占用。因此改换成I2C0_SDA,也就是GPIO1[4]
void DspFpgaNotifyInit()
{
	unsigned int savePinmux = 0;
	//配置GPIO1[4]为普通IO
	savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
				  ~(SYSCFG_PINMUX4_PINMUX4_15_12));

	HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) =
		  (PINMUX4_GPIO1_4_ENABLE | savePinmux);

	//配置GPIO1[5]为普通IO
	savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
				  ~(SYSCFG_PINMUX4_PINMUX4_11_8));

	HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) =
			(PINMUX4_GPIO1_5_ENABLE | savePinmux);

	//配置upp_chb_start为gpio  by administrator
	savePinmux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x0000F000);
	HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) = (0x00008000 | savePinmux);

	//配置GP1[4]为输出
	GPIODirModeSet(SOC_GPIO_0_REGS, 21, GPIO_DIR_OUTPUT);
	//配置GP1[5]位输入
	GPIODirModeSet(SOC_GPIO_0_REGS, 22, GPIO_DIR_OUTPUT);
	//配置GP8[14]为输出 upp_chb_start
	GPIODirModeSet(SOC_GPIO_0_REGS, 143, GPIO_DIR_OUTPUT);

	//初始化为FPGA不发送
	DspFpgaNotifySend(STOP);
}




