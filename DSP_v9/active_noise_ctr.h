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

#define ORDER_OF_ADAPTIVE_FILTER				100		/*����x�˲��㷨������Ӧ�˲�������*/
#define ORDER_PRIMARY_PATH_FILTER				40		/*�����ŵ��˲���ģ�ͽ���,������4�ı���*/
#define ORDER_FORWARD_PATH_FILTER				40		/*ǰ���ŵ��˲���ģ�ͽ�����ͨ���趨���������ŵ��˲���ģ�ͽ���*/
#define WHITE_NOISE_SAMPLE_NUM					65536	/*����ǰ���ŵ�ģ��ʱ�������͵ľ��ȷֲ��������źŵ�����*/

#define TRUE									1
#define FALSE									0
#define WAIT_TIME_FOR_FORWARD_PATH_OUTPUT		5		/* 5 seconds�� ʶ��ǰ���ŵ�ģ�͵ĵȴ�ʱ��*/

#define SYS_ID_LMS_MU							0.00001	/*�ŵ�ģ��ʶ��LMS�㷨�Ĳ�������*/

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
