/*
 * dsp_notify_fpga.h
 *
 *  Created on: 2015-11-2
 *      Author: Administrator
 */
#ifndef DSP_NOTIFY_FPGA_H_
#define DSP_NOTIFY_FPGA_H_

#include "utils.h"

#define START                            1
#define STOP                             0
#define RECEIVED                      1
#define NOT_RECEIVED              0
#define RECEIVE_FINISHED         1
#define RECEIVE_UNFINISHED    0
#define IF_RECEIVED                  0
#define IF_RECEIVE_FINISHED     1

//i2c0的sda配置成GPIO
#define PINMUX4_GPIO1_4_ENABLE    (SYSCFG_PINMUX4_PINMUX4_15_12_GPIO1_4    << \
                                    SYSCFG_PINMUX4_PINMUX4_15_12_SHIFT)

//i2c0的scl配置成GPIO
#define PINMUX4_GPIO1_5_ENABLE    (SYSCFG_PINMUX4_PINMUX4_11_8_GPIO1_5    << \
                                    SYSCFG_PINMUX4_PINMUX4_11_8_SHIFT)

void DspFpgaNotifySend(unsigned int message);
void DspFpgaNotifyInit();

#endif /* DSP_NOTIFY_FPGA_H_ */
