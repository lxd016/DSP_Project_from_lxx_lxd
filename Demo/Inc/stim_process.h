/*
 * stim_process.h
 *
 *  Created on: 2014-12-10
 *      Author: FES
 */

#ifndef STIM_PROCESS_H_
#define STIM_PROCESS_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_type.h"
#include "stdio.h"
#include "string.h"
#include "main.h"
#include "app_usart.h"

/* Macro Def -----------------------------------------------------------------*/
#define STRING_LENGTH      20
#define CURSOR_PULSE       0x98
#define CURSOR_AMP         0xD8
#define CURSOR_INTERVAL    4
#define SEG_LENGTH         (CURSOR_INTERVAL - 1)

#define    INIT_DATA   2000  //2000
#define    MAX_DATA    3800000
#define    RANGE       (MAX_DATA-INIT_DATA)

#define    MAX_AMP     255
#define    MAX_WIDTH   300

extern void Delay(u32 nCount);

void Stim_Delay(u16 nTime);
u16 stim_search(void);

float stim_pres_cal(u32 iSampleData);
u8 stim_amp_gen(float Pressure);
u16 stim_pul_gen(float Pressure);

u16 stim_send_init_parameter(u8* sti_amp, u16* pulse_width);
u16 stim_send_parameter(u8* sti_amp, u16* pulse_width,u8 mode);
u16 stim_start(void);
u16 stim_stop(void);

#endif /* STIM_PROCESS_H_ */
