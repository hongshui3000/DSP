/*
 * omapl_fpga_upp.c
 *
 *  Created on: 2015-11-12
 *      Author: Administrator
 */

#include "uPP.h"
#include "utils.h"

//全局变量
unsigned int upp_tran_status = UPP_TRAN_UNFINISHED;   //中断标志位，标示upp是否已经传输完毕

/* 获取中断标志位状态 */
unsigned int UPPTranGetStatus()
{
	return upp_tran_status;
}

/* 清除中断标志位 */
void UPPTranClearStatus()
{
	upp_tran_status = UPP_TRAN_UNFINISHED;
}

/* 中断服务函数 */
static void upp_isr(UArg arg)
{
	unsigned int intr_dmai_status;

	// 取得 DMA 中断状态
	intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);

	if (intr_dmai_status & uPP_INT_EOW)
	{
		uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);
		upp_tran_status = UPP_TRAN_FINISHED;
	}

	// 通知 CPU uPP 中断处理完毕以便后续事件可以产生
	uPPEndOfInt(SOC_UPP_0_REGS);
}


/* uPP注册中断 */
static void upp_int_register(unsigned int cpuINT )
{
	// 动态创建硬件中断
	Hwi_Handle hwi;
	Hwi_Params hwiParams;
	Error_Block eb;

	Error_init(&eb);

	// 使用默认值初始化参数
	Hwi_Params_init(&hwiParams);
	// 中断事件
	hwiParams.eventId = SYS_INT_UPP_INT;
	// 传递到中断服务函数的参数
	hwiParams.arg = 1;
	// 不允许该中断自身嵌套
	hwiParams.maskSetting = Hwi_MaskingOption_SELF;
	// 使能中断
	hwiParams.enableInt = true;
	// 可屏蔽中断 5
	// 中断服务函数 hwiMain
	hwi = Hwi_create(cpuINT, upp_isr, &hwiParams, &eb);

	if (hwi == NULL)
		System_abort("Hwi2 create failed");

	Hwi_enable();
	Hwi_enableInterrupt(5);
}

/* uPP发送  */
void UPPReceive(uPPDMAConfig *p_upp_tran_channel)
{
	// uPP启动接收
	uPPDMATransfer(SOC_UPP_0_REGS, uPP_DMA_CHI, p_upp_tran_channel);
}

/* uPP buffer配置  */
void UPPBufferConfig(uPPDMAConfig *p_upp_tran_channel, UPP_DATA_TYPE *p_upp_buffer)
{
	p_upp_tran_channel->WindowAddress   = (unsigned int *)((int)p_upp_buffer);
	p_upp_tran_channel->LineCount             = upp_receive_line_count;
	p_upp_tran_channel->ByteCount             = (upp_receive_byte_count*sizeof(UPP_DATA_TYPE));
	p_upp_tran_channel->LineOffsetAddress = (upp_receive_line_offset*sizeof(UPP_DATA_TYPE));
}

/* uPP 初始化 */
void UPPInit()
{
	// 外设使能
	PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UPP, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);

	// 引脚复用配置
	uPPPinMuxSetup(uPP_CHA_16BIT);

	//将upp_chb_start配置为gpio, in dsp_fpga_notify.c  init
	//uPPPinMuxSetup_chb_start();

	// uPP复位
	uPPReset(SOC_UPP_0_REGS);

	// 数据格式配置
	uPPDataFmtConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_DataPackingFmt_LJZE | uPP_DataPacking_FULL
							| uPP_InterfaceWidth_16BIT | uPP_DataRate_SINGLE);

	// 通道配置
	uPPChannelConfig(SOC_UPP_0_REGS, uPP_DDRDEMUX_DISABLE | uPP_SDRTXIL_DISABLE | uPP_CHN_ONE
							| uPP_ALL_RECEIVE);

	// 引脚配置
	uPPPinConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_PIN_ENABLE | uPP_PIN_START);

	// 中断使能
	uPPIntEnable(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);

	// 中断映射
	//IntRegister(C674X_MASK_INT5, uPPIsr);
	//IntEventMap(C674X_MASK_INT5, SYS_INT_UPP_INT);
	//IntEnable(C674X_MASK_INT5);
	upp_int_register(C674X_MASK_INT5 );

	// uPP使能
	uPPEnable(SOC_UPP_0_REGS);
}
