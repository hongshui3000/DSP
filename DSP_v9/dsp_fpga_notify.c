/*
 * dsp_notify_fpga.c
 *
 *  Created on: 2015-11-2
 *      Author: jdy
 */


/* DSP֪ͨFPGA��������  */

#include "dsp_fpga_notify.h"
#include "utils.h"

// DSP֪ͨfpga����
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

// (DSP����fpga���ã�ʹ�õ���GPIO5[13]����)  ����Ҫ�õ�EMIIFA��GPIO5[13]��emifaռ�á���˸Ļ���I2C0_SDA,Ҳ����GPIO1[4]
void DspFpgaNotifyInit()
{
	unsigned int savePinmux = 0;
	//����GPIO1[4]Ϊ��ͨIO
	savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
				  ~(SYSCFG_PINMUX4_PINMUX4_15_12));

	HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) =
		  (PINMUX4_GPIO1_4_ENABLE | savePinmux);

	//����GPIO1[5]Ϊ��ͨIO
	savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
				  ~(SYSCFG_PINMUX4_PINMUX4_11_8));

	HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) =
			(PINMUX4_GPIO1_5_ENABLE | savePinmux);

	//����upp_chb_startΪgpio  by administrator
	savePinmux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x0000F000);
	HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) = (0x00008000 | savePinmux);

	//����GP1[4]Ϊ���
	GPIODirModeSet(SOC_GPIO_0_REGS, 21, GPIO_DIR_OUTPUT);
	//����GP1[5]λ����
	GPIODirModeSet(SOC_GPIO_0_REGS, 22, GPIO_DIR_OUTPUT);
	//����GP8[14]Ϊ��� upp_chb_start
	GPIODirModeSet(SOC_GPIO_0_REGS, 143, GPIO_DIR_OUTPUT);

	//��ʼ��ΪFPGA������
	DspFpgaNotifySend(STOP);
}




