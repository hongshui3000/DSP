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

#include "hw_types.h"				// 宏命令
#include "hw_syscfg0_C6748.h"	    // 系统配置模块寄存器
#include "hw_upp.h"
#include "soc_C6748.h"			    // DSP C6748 外设寄存器
#include "psc.h"			        // 电源与睡眠控制宏及设备抽象层函数声明
#include "interrupt.h"             // DSP C6748 中断相关应用程序接口函数声明及系统事件号定义
#include "uartStdio.h"             // 串口标准输入输出终端函数声明
#include "gpio.h"
#include "uartStdio.h"             // 串口标准输入输出终端函数声明
#include "rtc.h"					// 实时时钟宏及设备抽象层函数声明

void dsp_delay(volatile unsigned int count);

#endif /* UTILS_H_ */
