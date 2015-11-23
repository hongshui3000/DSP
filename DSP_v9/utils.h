/*
 * utils.h
 *
 *  Created on: 2015-11-2
 *      Author: Administrator
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <xdc/std.h>
#include <stdio.h>
#include <c6x.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/family/c64p/Cache.h>

#include "hw_types.h"				// ������
#include "hw_syscfg0_C6748.h"	    // ϵͳ����ģ��Ĵ���
#include "hw_upp.h"
#include "soc_C6748.h"			    // DSP C6748 ����Ĵ���
#include "psc.h"			        // ��Դ��˯�߿��ƺ꼰�豸����㺯������
#include "interrupt.h"             // DSP C6748 �ж����Ӧ�ó���ӿں���������ϵͳ�¼��Ŷ���
#include "uartStdio.h"             // ���ڱ�׼��������ն˺�������
#include "gpio.h"
#include "uartStdio.h"             // ���ڱ�׼��������ն˺�������
#include "rtc.h"					// ʵʱʱ�Ӻ꼰�豸����㺯������

void dsp_delay(volatile unsigned int count);

#endif /* UTILS_H_ */
