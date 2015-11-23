/*
 * omapl_fpga_upp.c
 *
 *  Created on: 2015-11-12
 *      Author: Administrator
 */

#include "uPP.h"
#include "utils.h"

//ȫ�ֱ���
unsigned int upp_tran_status = UPP_TRAN_UNFINISHED;   //�жϱ�־λ����ʾupp�Ƿ��Ѿ��������

/* ��ȡ�жϱ�־λ״̬ */
unsigned int UPPTranGetStatus()
{
	return upp_tran_status;
}

/* ����жϱ�־λ */
void UPPTranClearStatus()
{
	upp_tran_status = UPP_TRAN_UNFINISHED;
}

/* �жϷ����� */
static void upp_isr(UArg arg)
{
	unsigned int intr_dmai_status;

	// ȡ�� DMA �ж�״̬
	intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);

	if (intr_dmai_status & uPP_INT_EOW)
	{
		uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);
		upp_tran_status = UPP_TRAN_FINISHED;
	}

	// ֪ͨ CPU uPP �жϴ�������Ա�����¼����Բ���
	uPPEndOfInt(SOC_UPP_0_REGS);
}


/* uPPע���ж� */
static void upp_int_register(unsigned int cpuINT )
{
	// ��̬����Ӳ���ж�
	Hwi_Handle hwi;
	Hwi_Params hwiParams;
	Error_Block eb;

	Error_init(&eb);

	// ʹ��Ĭ��ֵ��ʼ������
	Hwi_Params_init(&hwiParams);
	// �ж��¼�
	hwiParams.eventId = SYS_INT_UPP_INT;
	// ���ݵ��жϷ������Ĳ���
	hwiParams.arg = 1;
	// ��������ж�����Ƕ��
	hwiParams.maskSetting = Hwi_MaskingOption_SELF;
	// ʹ���ж�
	hwiParams.enableInt = true;
	// �������ж� 5
	// �жϷ����� hwiMain
	hwi = Hwi_create(cpuINT, upp_isr, &hwiParams, &eb);

	if (hwi == NULL)
		System_abort("Hwi2 create failed");

	Hwi_enable();
	Hwi_enableInterrupt(5);
}

/* uPP����  */
void UPPReceive(uPPDMAConfig *p_upp_tran_channel)
{
	// uPP��������
	uPPDMATransfer(SOC_UPP_0_REGS, uPP_DMA_CHI, p_upp_tran_channel);
}

/* uPP buffer����  */
void UPPBufferConfig(uPPDMAConfig *p_upp_tran_channel, UPP_DATA_TYPE *p_upp_buffer)
{
	p_upp_tran_channel->WindowAddress   = (unsigned int *)((int)p_upp_buffer);
	p_upp_tran_channel->LineCount             = upp_receive_line_count;
	p_upp_tran_channel->ByteCount             = (upp_receive_byte_count*sizeof(UPP_DATA_TYPE));
	p_upp_tran_channel->LineOffsetAddress = (upp_receive_line_offset*sizeof(UPP_DATA_TYPE));
}

/* uPP ��ʼ�� */
void UPPInit()
{
	// ����ʹ��
	PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UPP, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);

	// ���Ÿ�������
	uPPPinMuxSetup(uPP_CHA_16BIT);

	//��upp_chb_start����Ϊgpio, in dsp_fpga_notify.c  init
	//uPPPinMuxSetup_chb_start();

	// uPP��λ
	uPPReset(SOC_UPP_0_REGS);

	// ���ݸ�ʽ����
	uPPDataFmtConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_DataPackingFmt_LJZE | uPP_DataPacking_FULL
							| uPP_InterfaceWidth_16BIT | uPP_DataRate_SINGLE);

	// ͨ������
	uPPChannelConfig(SOC_UPP_0_REGS, uPP_DDRDEMUX_DISABLE | uPP_SDRTXIL_DISABLE | uPP_CHN_ONE
							| uPP_ALL_RECEIVE);

	// ��������
	uPPPinConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_PIN_ENABLE | uPP_PIN_START);

	// �ж�ʹ��
	uPPIntEnable(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);

	// �ж�ӳ��
	//IntRegister(C674X_MASK_INT5, uPPIsr);
	//IntEventMap(C674X_MASK_INT5, SYS_INT_UPP_INT);
	//IntEnable(C674X_MASK_INT5);
	upp_int_register(C674X_MASK_INT5 );

	// uPPʹ��
	uPPEnable(SOC_UPP_0_REGS);
}
