/*
 * dsp_fpga_emifa.c
 *
 *  Created on: 2015-11-12
 *      Author: Administrator
 */

#include "emifa.h"
#include "dsp_fpga_emifa.h"
#include "utils.h"

/* 全局变量 */
unsigned int emifa_fpga_write_index = 1;

/* 写入FPGA中的ram */
void EmifaFpgaWrite(unsigned int mode, EMIFA_DATA_TYPE data)
{
	if (EMIFA_FPGA_WRITE_BACKWARD == mode)
	{
		if (0 == emifa_fpga_write_index)
		{
			emifa_fpga_write_index = EMIFA_FPGA_RAM_SIZE - 1;
		}
		else
		{
			emifa_fpga_write_index--;
		}
	}
	else if(EMIFA_FPGA_WRITE_FORWARD == mode)
	{
		if (emifa_fpga_write_index == EMIFA_FPGA_RAM_SIZE - 1)
		{
			emifa_fpga_write_index = 0;
		}
		else
		{
			emifa_fpga_write_index++;
		}
	}

	EMIFA_FPGA_WRITE_ADDR(emifa_fpga_write_index) = data;
	emifa_fpga_write_index  = 1;
	/*emifa_fpga_write_index += 2;
	if (emifa_fpga_write_index >= EMIFA_FPGA_RAM_SIZE)
	{
		emifa_fpga_write_index = 0;
	}*/
}

/* 引脚复用设置 */
static void emifa_pin_mux_setup()
{
	 volatile unsigned int savePinMux = 0;

	 /* Programming the PINMUX12 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX12 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(12)) & \
						 ~(SYSCFG_PINMUX12_PINMUX12_31_28 | \
						   SYSCFG_PINMUX12_PINMUX12_27_24 | \
						   SYSCFG_PINMUX12_PINMUX12_23_20 | \
						   SYSCFG_PINMUX12_PINMUX12_19_16 | \
						   SYSCFG_PINMUX12_PINMUX12_15_12 | \
						   SYSCFG_PINMUX12_PINMUX12_11_8  | \
						   SYSCFG_PINMUX12_PINMUX12_7_4   | \
						   SYSCFG_PINMUX12_PINMUX12_3_0);
	  /*
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX12  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(12)) = \
    		 (PINMUX12_EMIF_A_ENABLE | savePinMux);



	 /* Programming the PINMUX11 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX11 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(11)) & \
						 ~(SYSCFG_PINMUX11_PINMUX11_31_28 | \
						   SYSCFG_PINMUX11_PINMUX11_27_24 | \
						   SYSCFG_PINMUX11_PINMUX11_23_20 | \
						   SYSCFG_PINMUX11_PINMUX11_19_16 | \
						   SYSCFG_PINMUX11_PINMUX11_15_12 | \
						   SYSCFG_PINMUX11_PINMUX11_11_8  | \
						   SYSCFG_PINMUX11_PINMUX11_7_4   | \
						   SYSCFG_PINMUX11_PINMUX11_3_0);
	  /*
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX11  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(11)) = \
    		 (PINMUX11_EMIF_A_ENABLE | savePinMux);



	 /* Programming the PINMUX9 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX9 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(9)) & \
						 ~(SYSCFG_PINMUX9_PINMUX9_31_28 | \
						   SYSCFG_PINMUX9_PINMUX9_27_24 | \
						   SYSCFG_PINMUX9_PINMUX9_23_20 | \
						   SYSCFG_PINMUX9_PINMUX9_19_16 | \
						   SYSCFG_PINMUX9_PINMUX9_15_12 | \
						   SYSCFG_PINMUX9_PINMUX9_11_8  | \
						   SYSCFG_PINMUX9_PINMUX9_7_4   | \
						   SYSCFG_PINMUX9_PINMUX9_3_0);
	  /*
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX9  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(9)) = \
          (PINMUX9_EMIF_D_ENABLE | savePinMux);


	 /* Programming the PINMUX8 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX8 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(8)) & \
						 ~(SYSCFG_PINMUX8_PINMUX8_31_28 | \
						   SYSCFG_PINMUX8_PINMUX8_27_24 | \
						   SYSCFG_PINMUX8_PINMUX8_23_20 | \
						   SYSCFG_PINMUX8_PINMUX8_19_16 | \
						   SYSCFG_PINMUX8_PINMUX8_15_12 | \
						   SYSCFG_PINMUX8_PINMUX8_11_8  | \
						   SYSCFG_PINMUX8_PINMUX8_7_4   | \
						   SYSCFG_PINMUX8_PINMUX8_3_0);
	  /*
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX8  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(8)) = \
          (PINMUX8_EMIF_D_ENABLE | savePinMux);


	 /* Programming the PINMUX5 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX5 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
						 ~(SYSCFG_PINMUX5_PINMUX5_31_28 | \
						   SYSCFG_PINMUX5_PINMUX5_27_24);
	  /*
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX5  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
          (PINMUX5_EMIF_BA_ENABLE | savePinMux);

     /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX6 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(6)) & \
						 ~(SYSCFG_PINMUX6_PINMUX6_3_0);
	  /*
	  ** Performing the actual Pin Multiplexing to select relevant pins in
	  ** PINMUX6  register.
	  */
	  HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(6)) = \
		   (PINMUX6_EMIF_CLK_ENABLE | savePinMux);


	 /* Programming the PINMUX7 register. */
	 /*
	 ** Clearing the pins in context and retaining the other pin values
	 ** of PINMUX7 register.
	 */
	 savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(7)) & \
						 ~(SYSCFG_PINMUX7_PINMUX7_23_20 | \
						   SYSCFG_PINMUX7_PINMUX7_19_16 | \
						   SYSCFG_PINMUX7_PINMUX7_3_0);
	  /*
     ** Performing the actual Pin Multiplexing to select relevant pins in
     ** PINMUX7  register.
     */
     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(7)) = \
          (PINMUX7_EMIF_CTL_ENABLE | savePinMux);

}


/* emifa配置 */
void DspFpgaEmifaInit()
{
	//使能emifa模块
	PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_EMIFA, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);

	//配置emifa相关复用引脚
	emifa_pin_mux_setup();

	//配置数据总线16bit
	EMIFAAsyncDevDataBusWidthSelect(SOC_EMIFA_0_REGS, EMIFA_CHIP_SELECT_2, EMIFA_DATA_BUSWITTH_16BIT);

	//选着Normal模式
	EMIFAAsyncDevOpModeSelect(SOC_EMIFA_0_REGS, EMIFA_CHIP_SELECT_2, EMIFA_ASYNC_INTERFACE_NORMAL_MODE);

	//禁止WAIT引脚
	EMIFAExtendedWaitConfig(SOC_EMIFA_0_REGS, EMIFA_CHIP_SELECT_2, EMIFA_EXTENDED_WAIT_DISABLE);

	//配置W_SETUP/R_SETUP   W_STROBE/R_STROBE    W_HOLD/R_HOLD	TA等参数
	EMIFAWaitTimingConfig(SOC_EMIFA_0_REGS, EMIFA_CHIP_SELECT_2, EMIFA_ASYNC_WAITTIME_CONFIG(2, 3, 2, 2, 3, 2, 0 ));
}

