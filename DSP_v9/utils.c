/*
 * utils.c
 *
 *  Created on: 2015-11-2
 *      Author: Administrator
 */

#include "utils.h"

//—” ±
void dsp_delay(volatile unsigned int count)
{
    while(count--);
}

