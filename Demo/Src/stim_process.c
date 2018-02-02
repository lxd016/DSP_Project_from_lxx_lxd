/*
 * stim_process.c
 *
 *  Created on: 2014-12-10
 *      Author: FES
 */

#include "stim_process.h"
#include "app_usart.h"
#include "main.h"


extern ReceiveDataType receiveDataFromCom1;
extern ReceiveDataType receiveDataFromCom2;
extern ReceiveDataType receiveDataFromCom3;
extern ReceiveDataType receiveDataFromCom4;
extern ReceiveDataType receiveDataFromCom5;

//-----------------------------------------------------------------------------
// \brief   time delay function
//
// \param   u8 time: time length to be delayed (time base is 1 us)
// System clock is 72Mhz, single period is (1000,000/12M) = 1/72 us
//
// \return  none
//-----------------------------------------------------------------------------

void Stim_Delay(u16 nTime)
{
	u32 i = 1;
	i = nTime * 12;
	while(i > 0)
		i--;
}

float stim_pres_cal(u32 iSampleData)
{
	float Voltage = 0, Pressure = 0;
	u32 CaliData = 0;

	if(iSampleData > INIT_DATA)
	{
		CaliData = iSampleData - INIT_DATA;
	}
	else
	{
		CaliData = 0;
	}
	Voltage = (float)(CaliData)*2.316/RANGE;
	//Voltage = (float)(CaliData)*2/RANGE;
	//Pressure = Voltage*(Voltage*(Voltage*0.69 + 0.92) + 0.38);
	Pressure = 2 * Voltage; //Just for test
	
	return Pressure;
}

u8 stim_amp_gen(float Pressure)
{
	u8 stim_amp = 0;
	int stim_amp1 =0;
  float amp_temp=(Pressure * 3 + 0.5)*10-5;
	if (amp_temp >= MAX_AMP)
	{stim_amp=MAX_AMP;}
  else if(amp_temp < 0)
	{stim_amp=0;}
  else
	{
	stim_amp1 = (int)(amp_temp);
	stim_amp = (u8)(stim_amp1);}

	return stim_amp;
}

u16 stim_pul_gen(float Pressure)
{
	u16 stim_pulse = 0;

	stim_pulse = (u16)(Pressure * 30 + 10.5);

	if(stim_pulse > MAX_WIDTH)
		stim_pulse = MAX_WIDTH;

	return stim_pulse;
}

u16 stim_send_init_parameter(u8* sti_amp, u16* pulse_width)
{
	u8 cnt_chl = 0, cnt=3;

	//for(cnt_chl = 0; cnt_chl < 5; cnt_chl++)
	{
		//cnt = 4;
		cnt = 2;
	  while(receiveDataFromCom2.channel != (cnt_chl+1) && --cnt)
		{
			UartConfig_tx(cnt_chl, sti_amp[cnt_chl], pulse_width[cnt_chl],0);
			Delay(1);
		}
		receiveDataFromCom2.channel = 0;
		receiveDataFromCom2.commandType = 0;
		Delay(5);
	}
	return cnt?0:1;
}

u16 stim_send_parameter(u8* sti_amp, u16* pulse_width,u8 mode)
{
	vu8 cnt_chl = 0, cnt = 3;
	//for(cnt_chl = 0; cnt_chl < 8; cnt_chl++)
	{
		cnt = 2;
		while(receiveDataFromCom1.channel != (cnt_chl+1) && receiveDataFromCom2.channel != (cnt_chl+1) && receiveDataFromCom3.channel != (cnt_chl+1) && receiveDataFromCom4.channel != (cnt_chl+1) && receiveDataFromCom5.channel != (cnt_chl+1) && --cnt)
		{
			if(sti_amp[cnt_chl] != 0)
			{Uart1Config_tx(cnt_chl, sti_amp[cnt_chl], pulse_width[cnt_chl],mode);
			receiveDataFromCom1.DSPDSUreceivedFlag = 0;}
			else
			{
	        Uart1ConfigNull_tx(cnt_chl); 
			}
			
			if(sti_amp[cnt_chl+1] != 0)
			{UartConfig_tx(cnt_chl, sti_amp[cnt_chl+1], pulse_width[cnt_chl+1],mode);
			receiveDataFromCom2.DSPDSUreceivedFlag = 0;}
			else
			{
	        UartConfigNull_tx(cnt_chl); 
			}
			
			if(sti_amp[cnt_chl+2] != 0)
			{Uart3Config_tx(cnt_chl, sti_amp[cnt_chl+2], pulse_width[cnt_chl+2],mode);
			receiveDataFromCom3.DSPDSUreceivedFlag = 0;}
			else
			{
	        Uart3ConfigNull_tx(cnt_chl); 
			}

			if(sti_amp[cnt_chl+3] != 0)
			{Uart4Config_tx(cnt_chl, sti_amp[cnt_chl+3], pulse_width[cnt_chl+3],mode);
	   	receiveDataFromCom4.DSPDSUreceivedFlag = 0;}
			else
			{
	        Uart4ConfigNull_tx(cnt_chl); 
			}
			
			if(sti_amp[cnt_chl+4] != 0)
			{Uart5Config_tx(cnt_chl, sti_amp[cnt_chl+4], pulse_width[cnt_chl+4],mode);
			receiveDataFromCom5.DSPDSUreceivedFlag = 0;}
			else
			{
	        Uart5ConfigNull_tx(cnt_chl); 
			}
		}
		
		//receiveDataFromCom.channel = 0;
		//receiveDataFromCom.commandType = 0;
		Stim_Delay(10000);
	}
	
	return cnt?0:1;
}

/*******************************************************************************
* Function Name  : stim_search
* Description    : send the search command to stimulator
* Input          : None
* Output         : None
* Return         : The ocnnect result.
                 : 0 -- stimulator connected
                 : 1 -- stimulator connect failed
	vu8 DSPDSUreceivedFlag;
*******************************************************************************/
u16 stim_search()
{
	u8 cnt = 1;
	UartCommand_tx(0x03);
  //Uart1Command_tx(0x03);
	Uart3Command_tx(0x03);
	//Uart3Command_tx(0x03);
	Uart4Command_tx(0x03);
	Uart5Command_tx(0x03);
	while(receiveDataFromCom2.commandType != 0x03 && --cnt)
	{
		UartCommand_tx(0x03);
		Delay(100);
  }
	receiveDataFromCom1.DSPDSUconnectedFlag = 0;
	receiveDataFromCom2.DSPDSUconnectedFlag = 0;
	receiveDataFromCom3.DSPDSUconnectedFlag = 0;
	receiveDataFromCom4.DSPDSUconnectedFlag = 0;
	receiveDataFromCom5.DSPDSUconnectedFlag = 0;
	//receiveDataFromCom.channel = 0;
	//receiveDataFromCom.commandType = 0;
	return cnt?0:1;
}
u16 stim_start()
{
	u8 cnt=3;
	UartCommand_tx(0x01);
	Uart1Command_tx(0x01);
	Uart3Command_tx(0x01);
	Uart4Command_tx(0x01);
	Uart5Command_tx(0x01);
	//while(receiveDataFromCom.commandType != 0x01 && --cnt)
	{
		Stim_Delay(1000);
	}
	receiveDataFromCom1.DSPDSUStartStimuFlag = 0;
	receiveDataFromCom2.DSPDSUStartStimuFlag = 0;
	receiveDataFromCom3.DSPDSUStartStimuFlag = 0;
	receiveDataFromCom4.DSPDSUStartStimuFlag = 0;
	receiveDataFromCom5.DSPDSUStartStimuFlag = 0;
	//receiveDataFromCom.channel = 0;
	//receiveDataFromCom.commandType = 0;
	return cnt?0:1;
}

u16 stim_stop()
{
	u8 cnt=3;
	UartCommand_tx(0x02);
	Uart1Command_tx(0x02);
	Uart3Command_tx(0x02);
	Uart4Command_tx(0x02);
	Uart5Command_tx(0x02);
	//while(receiveDataFromCom.commandType != 0x02 && --cnt)
	{
		Stim_Delay(1000);
	}
	receiveDataFromCom1.DSPDSUStopStimuFlag = 0;
	receiveDataFromCom2.DSPDSUStopStimuFlag = 0;
	receiveDataFromCom3.DSPDSUStopStimuFlag = 0;
	receiveDataFromCom4.DSPDSUStopStimuFlag = 0;
	receiveDataFromCom5.DSPDSUStopStimuFlag = 0;
	return cnt?0:1;
}

/* -----------------------------------*/
/* ---------- end of file ------------*/
/* -----------------------------------*/
