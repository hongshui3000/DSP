/*
 * main.c
 *
 *  Created on: 2015-11-12
 *      Author: Administrator
 */

#include "utils.h"
#include "active_noise_ctr.h"
#include "dsp_fpga_notify.h"
#include "dsp_fpga_emifa.h"
#include "uPP.h"
#include "dspcache.h"

/* 全局变量 */
// 收发数据buffer
UPP_DATA_TYPE    upp_receive_buffer_ping[upp_receive_buffer_size];
UPP_DATA_TYPE    upp_receive_buffer_pong[upp_receive_buffer_size];
EMIFA_DATA_TYPE emifa_send_buffer = 0;
float sin_value = 0.0;

/* ping pong处理 */
static void pp_process(uPPDMAConfig *p_upp_tran_channel, UPP_DATA_TYPE *p_upp_receive_buffer)
{
	float data_ad0, data_ad1, data_ad0_temp, data_ad1_temp, data_da;

	// uPP启动接收 ping
	UPPReceive(p_upp_tran_channel);

	//通知FPGA开始发送
	DspFpgaNotifySend(START);

	//关闭通知
	DspFpgaNotifySend(STOP);

	//处理pong
	data_ad0_temp = (float)p_upp_receive_buffer[0];
	data_ad1_temp = (float)p_upp_receive_buffer[1];
	data_ad0 = (data_ad0_temp / 32768.0 - 1.0) * 2.048;
	data_ad1 = (data_ad1_temp / 32768.0 - 1.0) * 2.048;
	data_ad0 = (float)(2.048 * sin(sin_value));
	//task_ATC(&data_ad0, &data_ad1, &data_da);
	//data_da = data_ad0;
	emifa_send_buffer = (EMIFA_DATA_TYPE) ((data_da / 5.0 + 1.0) * 32768.0);
	EmifaFpgaWrite(EMIFA_FPGA_WRITE_NORMAL, emifa_send_buffer);

	// 等待upp传输结束
	CacheInv ((unsigned int)p_upp_receive_buffer, sizeof(p_upp_receive_buffer));
	while (UPP_TRAN_FINISHED != UPPTranGetStatus())
	{
		//dsp_delay(10);
	}
	//清除UPP中断标志位
	UPPTranClearStatus();
}

/* 主task */
Void taskMain()
{
	long long t_start, t_stop, t_overhead;
	char put_char[50];
	uPPDMAConfig upp_tran_channel_ping, upp_tran_channel_pong;   //upp通道

	//记录时间的参数
	/*TSCL = 0;
	TSCH = 0;
	t_start = _itoll(TSCH, TSCL);
	t_stop = _itoll(TSCH, TSCL);
	t_overhead = t_stop - t_start;*/

	//uPP通道配置
	UPPBufferConfig(&upp_tran_channel_ping, upp_receive_buffer_ping);
	UPPBufferConfig(&upp_tran_channel_pong, upp_receive_buffer_pong);

	CacheWB ((unsigned int)upp_receive_buffer_ping, sizeof(upp_receive_buffer_ping));
	CacheWB ((unsigned int)upp_receive_buffer_pong, sizeof(upp_receive_buffer_pong));

	while(1)
	{
		pp_process(&upp_tran_channel_ping, upp_receive_buffer_pong);
		pp_process(&upp_tran_channel_pong, upp_receive_buffer_ping);

		//计算算法处理时间
		// 计数开始值
		//t_start = _itoll(TSCH, TSCL);

		// 计数结束值
		//t_stop = _itoll(TSCH, TSCL);
		/*sprintf(put_char,"\t time: %f ms \n",
							(float)((t_stop - t_start) - t_overhead) / 456000);
		UARTPuts(put_char, -2);*/
	}
}


/* 主函数   */
Int main()
{
	//初始化串口终端 使用串口2
	UARTStdioInit();
	UPPInit();
	DspFpgaEmifaInit();
	DspFpgaNotifyInit();

	CacheEnableMAR((unsigned int)0xC0000000, (unsigned int)0x10000000);
	CacheEnable(L1PCFG_L1PMODE_32K | L1DCFG_L1DMODE_32K | L2CFG_L2MODE_256K);

	UARTPuts("\n\n DSP program.\r\n", -2);

    // 启动 SYS/BIOS 系统
    BIOS_start();

    return(0);
}
