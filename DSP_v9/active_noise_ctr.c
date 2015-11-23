/*
 * active_noise_ctr.c
 *
 *  Created on: 2015-9-1
 *      Author: Administrator
 */

#include "active_noise_ctr.h"
#include "uartStdio.h"             // 串口标准输入输出终端函数声明

Bool	system_is_identified= TRUE;


/*主声信道滤波器的传输系数*/
//float	primaryPathCoe[ORDER_PRIMARY_PATH_FILTER +1];
float	primaryPathCoe[ORDER_PRIMARY_PATH_FILTER +1]= {0.817871571433671,
		-0.0324989142979024,
		-0.209252604846495,
		-0.908529655033969,
		0.342087844080333,
		-0.529604541850092,
		0.936465125501373,
		-0.830635698433330,
		-0.494183568979699,
		0.256756158199514,
		-0.699249140778207,
		-0.280309059322024,
		0.845639974738304,
		0.671055426667936,
		0.428556007998323,
		0.740826427815867,
		-0.930227698725754,
		-0.336932483751761,
		-0.824254415847480,
		0.756032851411045,
		0.644133665433216,
		-0.0454850639428408,
		-0.467469687325633,
		-0.763034881913585,
		-0.327260321624233,
		-0.264225538477407,
		-0.838625189773098,
		-0.773564516461252,
		0.701171835745299,
		0.595043371242957,
		0.893940480376566,
		0.457653688945646,
		-0.214449890523427,
		-0.259310027239523,
		-0.223627814661538,
		-0.512681016471554,
		-0.629843837409208,
		0.214624663449184,
		-0.803281409574338,
		-0.750650715898094,
		-0.186582099267553};

/*主声信道逆向模型的传输系数*/
float	inversePrimaryPathCoe[ORDER_PRIMARY_PATH_FILTER+1]= {0.0};

/*前向信道滤波器的传输系数*/
//float	forwardPathCoe[ORDER_FORWARD_PATH_FILTER +1]= {0.0};
float	forwardPathCoe[ORDER_FORWARD_PATH_FILTER+1]= {0.114657610242561,
		-0.949544653272976,
		-0.996987558899907,
		-0.369902430740140,
		-0.950153449527059,
		0.770973798712238,
		-0.243365043421912,
		-0.236284792067616,
		0.761499719583197,
		0.525787034782482,
		0.902693589172649,
		-0.428846775288157,
		0.372247731952112,
		0.367630919147111,
		0.772858105494109,
		-0.573820960509508,
		-0.208883283291423,
		-0.701342278952404,
		0.540317646945043,
		-0.881307794657214,
		-0.140104803787593,
		-0.741437258078455,
		0.664003475412728,
		-0.0935887382801570,
		-0.945924274598213,
		-0.149283172166573,
		0.997725396416022,
		0.770737564084464,
		-0.213760432421118,
		-0.671587701733963,
		0.625496957276714,
		0.727360949724615,
		0.755482021605355,
		-0.613662878802820,
		0.167995960995553,
		-0.491883547740003,
		0.913213133771538,
		0.373139298229078,
		-0.647814663894388,
		0.178943927017480,
		-0.489418617211943};

/*存储来自参考传声器的输入数据，用于主声信道逆向模型传输系数的识别*/
/*按序号0，1，2，...n，数据的实时性递减，即序号0对应当前时刻的数据，序号n对应最老时刻的数据*/
float	dlyAdaptPriPath[ORDER_PRIMARY_PATH_FILTER+1]= {0.0};

/*存储来自误差传声器的输入数据，用于前向信道模型传输系数的识别*/
/*按序号0，1，2，...n，数据的实时性递减，即序号0对应当前时刻的数据，序号n对应最老时刻的数据*/
float	dlyAdaptForPath[ORDER_FORWARD_PATH_FILTER+1]= {0.0};


/*存储来自参考传声器的输入数据，用于反相消声控制*/
/*按序号0，1，2，...n，数据的实时性递减，即序号0对应当前时刻的数据，序号n对应最老时刻的数据*/
float	xInput[ORDER_PRIMARY_PATH_FILTER+1]= {0.0};

/*存储来自误差传声器的输入数据，用于反相消声控制*/
/*按序号0，1，2，...n，数据的实时性递减，即序号0对应当前时刻的数据，序号n对应最老时刻的数据*/
float	eInput[ORDER_OF_ADAPTIVE_FILTER+1]= {0.0};

/*存储自适应滤波器的输入数据，它来自前向滤波器对参考传声器数据的预滤波输出*/
/*按序号0，1，2，...n，数据的实时性递减，即序号0对应当前时刻的数据，序号n对应最老时刻的数据*/
float	adaptFilterInput[ORDER_OF_ADAPTIVE_FILTER+1]= {0.0};

/*自适应滤波器的权系数*/
float	adaptFilterWeight[ORDER_OF_ADAPTIVE_FILTER+1]= {0.0};

/*前向信道的输入数据，它来自自适应滤波器的输出*/
/*按序号0，1，2，...n，数据的实时性递减，即序号0对应当前时刻的数据，序号n对应最老时刻的数据*/
float	forwardInput[ORDER_FORWARD_PATH_FILTER+1]= {0.0};

/*中间计算数据，来自于参考传声器数据经过前向滤波后的值，用于计算自适应滤波器的权系数*/
float	thetaHat[ORDER_OF_ADAPTIVE_FILTER+1]= {0.0};

float errorOutput[512]= {0.0};
unsigned int	mm= 0;
float	errSquareSum= 0;
float	oriSquareSum= 0;
float	errdB[512]= {0.0};

int		fb = 1;				/*feedback variable*/
shift_reg sreg = {0xFFFF};	/*shift register*/


int prbs(void)				//generating pseudo-random sequence {-1,1}
{
  int prnseq;
  if(sreg.bt.b0)
	prnseq = -NOISE_LEVEL;	//scaled negative noise level
  else
	prnseq = NOISE_LEVEL;			//scaled positive noise level
  fb =(sreg.bt.b0)^(sreg.bt.b1);	//XOR bits 0,1
  fb^=(sreg.bt.b11)^(sreg.bt.b13);	//with bits 11,13 -> fb
  sreg.regval<<=1;
  sreg.bt.b0=fb;					//close feedback path
  return prnseq;					//return noise sequence value
}


/**************************************************************************/
/* 函数：产生均匀分布的白噪声信号                                         */
/*      a: 均匀分布值的下限                                               */
/*      b: 均匀分布值的上限                                               */
/*		i: 生成随机种子所对应的时间										  */
/**************************************************************************/
float uniform_white_noise_gen(float a, float b, unsigned int i)
{
	float y, t;

	srand((unsigned int) time(&i));////////////////////////此处需要修改
	t= (float) rand();
	y= a + (b -a)*(t/RAND_MAX);
	return(y);
}

void filter_coe_init(int N, float *pCoe)
{
	unsigned int		i;

	for(i= 0; i< N+1; i++)
	{
		*(pCoe +i)= uniform_white_noise_gen(-1.0, 1.0, i);
	}

}


/*********************前向信道模型和主声信道逆向模型的识别函数********************************/
/* 函数名：system_path_id                                                                    */
/* 输入参数：                                                                                */
/*          pBufADC1-----来自ADC1（参考传声器）的输入数据                                    */
/*          pBufADC2-----来自ADC2（误差传声器）的输入数据                                    */
/*			mu-----------LMS算法的步长参数													 */
/* 输出数据：                                                                                */
/*          pBufDAC-----输出至DAC的数据                                                      */
/*********************************************************************************************/
void	system_path_id(float *pBufADC1, float *pBufADC2, float *pBufDAC)
{
	int		i;
	float	forwardPathOutput, inversePriPathOutput;
	float	forwardPathAdaptOutput, priPathAdaptOutput;
	float	errForwardPath, errPriPath;
	float	mu= SYS_ID_LMS_MU;

	inversePriPathOutput= *pBufADC1;	/*读取主声信道的逆向输出数据，来自参考传声器*/
	forwardPathOutput= *pBufADC2;	/*读取前向信道的输出数据，来自误差传声器*/

	/*将伪随机噪声数据分别作为两个自适应滤波器（一个识别前向信道模型，另一个识别主声信道逆向模型）的输入*/
	dlyAdaptPriPath[0]= prbs();
	dlyAdaptForPath[0]= dlyAdaptPriPath[0];

	*pBufDAC= dlyAdaptPriPath[0];	/*将伪随机噪声数据发送DAC*/

	forwardPathAdaptOutput= 0.0;
	priPathAdaptOutput= 0.0;
	/*分别计算前向信道模型和主声信道逆向模型的输出*/
	/*本消声处理程序设定前向信道模型和主声信道逆向模型的阶数相等*/
	for(i= 0; i< ORDER_FORWARD_PATH_FILTER +1; i++)
	{
		forwardPathAdaptOutput += dlyAdaptForPath[i]*forwardPathCoe[i];

		priPathAdaptOutput += 	dlyAdaptPriPath[i]*inversePrimaryPathCoe[i];
	}

	/*计算误差信号*/
	errForwardPath= forwardPathOutput- forwardPathAdaptOutput;
	errPriPath= inversePriPathOutput- priPathAdaptOutput;

	/*计算信道模型的权系数*/
	for(i= ORDER_FORWARD_PATH_FILTER; i >= 0; i--)
	{
		forwardPathCoe[i] = forwardPathCoe[i] + 2*mu*errForwardPath*dlyAdaptForPath[i];

		inversePrimaryPathCoe[i]= inversePrimaryPathCoe[i] +2*mu*errPriPath*dlyAdaptPriPath[i];
	}

	/*更新自适应滤波器的延迟线，即输入数据*/
	for(i= ORDER_FORWARD_PATH_FILTER; i > 0; i--)
	{
		dlyAdaptForPath[i]= dlyAdaptForPath[i-1];
		dlyAdaptPriPath[i]= dlyAdaptPriPath[i-1];
	}

	mm= mm +1;
	if(mm >= 50000)	/*当发送的宽带伪随机噪声超过5秒时，系统模型识别过程结束*/
	{
		system_is_identified= TRUE;
		mm= 0;
	}
}


/**********************主声信道逆向模型的识别函数*********************************************/
/* 函数名：inverse_pri_path_id                                                         */
/* 输入参数：                                                                                */
/*          pBufADC1-----来自ADC（参考传声器）的输入数据                                     */
/* 输出数据：                                                                                */
/*          pBufDAC-----输出至DAC的数据                                                      */
/*********************************************************************************************/
//void	inverse_pri_path_id(float *pBufADC1, float *pBufDAC)
//{

//}


/**************************主动消声算法处理函数***********************************************/
/* 函数名：active_noise_ctr                                                                  */
/* 输入参数：                                                                                */
/*          pBufADC1-----来自ADC（参考传声器）的输入数据                                     */
/*          pBufADC2-----来自ADC（误差传声器）的输入数据                                     */
/* 输出数据：                                                                                */
/*          pBufDAC------输出至DAC的数据                                                     */
/*********************************************************************************************/

int active_noise_ctr(float *pBufADC1, float *pBufADC2, float *pBufDAC)
{
	*pBufDAC = *pBufADC1;
	return 1;
	int				i;
	float			inputSum=0;
	float			mu;
	float			xHat=0;
	float			signalDisired= 0;
	float			yOut= 0;
	float			yHat= 0;
	float			eOutput= 0;
	char			charOutput1[50];
	char			charOutput2[50];

	for(i= ORDER_FORWARD_PATH_FILTER+1; i> 1; i--)
	{
		xInput[i-1]= xInput[i-2];	/*更新x预滤波器以及主声信道的输入*/
		inputSum += pow(xInput[i], 2);
	}
	xInput[0]= *pBufADC1;
	inputSum += pow(xInput[0], 2);

	mu= 1/inputSum;	/*计算自适应滤波器权系数的更新步长*/
	if( mu > 0.00001)
		mu= 0.00001;

	/*分别计算主声信道和x预滤波的输出*/
	for(i= 0; i < ORDER_PRIMARY_PATH_FILTER +1 ; i++)
	{
		signalDisired += xInput[i]*primaryPathCoe[i];	/*主声信道的输出即期望信号*/
		xHat += xInput[i]*forwardPathCoe[i];	/*x预滤波器的输出，它用于更新自适应滤波器的权系数*/
	}

	/*获取自适应滤波器的输入数据和用于更新自适应滤波器权系数的中间数据*/
	for(i= ORDER_OF_ADAPTIVE_FILTER; i> 0 ; i--)
	{
		/*更新自适应滤波器的输入数据*/
		adaptFilterInput[i]= adaptFilterInput[i-1];

		/*更新用于计算自适应滤波器权系数的中间数据*/
		thetaHat[i] = thetaHat[i-1];
	}
	adaptFilterInput[0]= xInput[0];
	thetaHat[0]= xHat;

	/*计算自适应滤波器的输出*/
	for(i= 0; i< ORDER_OF_ADAPTIVE_FILTER+1; i++)
		yOut += adaptFilterWeight[i]*adaptFilterInput[i];  /************需要修改？***************/

	/*更新前向信道的输入数据*/
	for(i= ORDER_FORWARD_PATH_FILTER; i> 0 ; i--)
	{
		forwardInput[i]= forwardInput[i-1];
	}
	forwardInput[0]= yOut;

	/*计算前向信道的输出，即反相消声数据*/
	for(i= 0; i< ORDER_FORWARD_PATH_FILTER+1; i++)
		yHat += forwardPathCoe[i]*forwardInput[i];	/************需要修改？***************/

	/*消声后的声压数据*/
	//eOutput= *pBufADC2;
	eOutput= signalDisired- yHat;
	//errorOutput[mm]= eOutput;
	sprintf(charOutput1,"\neOutput[%d]= %f\n", mm, eOutput);
	UARTprintf(charOutput1, -2);

	oriSquareSum += pow(signalDisired,2);
	errSquareSum += pow(eOutput,2);
	errdB[mm]= 10*log10f(oriSquareSum/errSquareSum);
	sprintf(charOutput2,"Power errdB= %f\n", errdB[mm]);
	UARTprintf(charOutput2, -2);
	mm++;

	for(i= 0; i < ORDER_OF_ADAPTIVE_FILTER+1; i++)
		adaptFilterWeight[i]= adaptFilterWeight[i] + 2*mu*eOutput*thetaHat[i];

	*pBufDAC= - yHat;	/*发送反相消声数据给DAC*/

	return 1;
}

void task_ATC(float *pBufADC1, float *pBufADC2, float *pBufDAC)
{

	if(system_is_identified == FALSE) /* identifying the model of forward path*/
	{
		system_path_id(pBufADC1, pBufADC2, pBufDAC);
	}
	else /* system_is_identified == TRUE, executing active noise process using filtered-x-LMS algorithm*/
	{

		active_noise_ctr(pBufADC1, pBufADC2, pBufDAC);

	}

}

