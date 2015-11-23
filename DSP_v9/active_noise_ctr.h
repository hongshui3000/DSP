/* active_noise_ctr.h
 *
 * Created on: 2015-8-29
 * Author: Administrator
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <dsplib.h>

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>


#ifndef ACTIVE_NOISE_CTR_H_
#define ACTIVE_NOISE_CTR_H_

#define ORDER_OF_ADAPTIVE_FILTER				100		/*基于x滤波算法的自适应滤波器阶数*/
#define ORDER_PRIMARY_PATH_FILTER				40		/*主声信道滤波器模型阶数,必须是4的倍数*/
#define ORDER_FORWARD_PATH_FILTER				40		/*前向信道滤波器模型阶数，通常设定等于主声信道滤波器模型阶数*/
#define WHITE_NOISE_SAMPLE_NUM					65536	/*构建前向信道模型时，所发送的均匀分布白噪声信号的数量*/

#define TRUE									1
#define FALSE									0
#define WAIT_TIME_FOR_FORWARD_PATH_OUTPUT		5		/* 5 seconds； 识别前向信道模型的等待时间*/

#define SYS_ID_LMS_MU							0.00001	/*信道模型识别LMS算法的步长参数*/

#define NOISE_LEVEL 8000							/* noise level*/




typedef struct BITVAL    // used in function prbs()
{
	unsigned	int b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1;
	unsigned	int b7:1, b8:1, b9:1, b10:1, b11:1, b12:1,b13:1;
	unsigned	int dweebie:2; //Fills the 2 bit hole - bits 14-15
} bitval;

typedef union SHIFT_REG
{
	unsigned int	regval;
	bitval			bt;
} shift_reg;




float uniform_white_noise_gen(float a, float b, unsigned int i);
void filter_coe_init(int N, float *pCoe);
void	system_path_id(float *pBufADC1, float *pBufADC2, float *pBufDAC);
//void	inverse_pri_path_id(float *pBufADC1);
//void	forward_path_id(float *pBufADC2);
int	active_noise_ctr(float *pBufADC1, float *pBufADC2, float *pBufDAC);
void task_ATC(float *pBufADC1, float *pBufADC2, float *pBufDAC);
void Send_white_unit_noise_to_speaker(void);

#endif /* ACTIVE_NOISE_CTR_H_ */
