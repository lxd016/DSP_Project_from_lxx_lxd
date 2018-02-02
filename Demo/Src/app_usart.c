#include "app_usart.h"
#include "main.h"

extern ReceiveDataType receiveDataFromCom1;
extern ReceiveDataType receiveDataFromCom2;
extern ReceiveDataType receiveDataFromCom3;
extern ReceiveDataType receiveDataFromCom4;
extern ReceiveDataType receiveDataFromCom5;

commandtx txcommand = {
					0x80,			//communication header
					0x01,			//transmit command stream
					0x02,			//default command is stop, command: 01 start, 02 stop, 03 searching device, 04 end of data transmit
			};

configtx txconfig = {
					0x80,			//communication header
					0x02,			//transmit data stream
					0x01, 			//default channel is 1st channel
					0x000C, 		//length is 12
					0x003C, 		//default time width is 50us = 0x32H
					0x0032, 		//default frequeny is 100 Hz = 0x0064H
					0x0A, 			//default time delay is 10us = 0x0AH
					0x01, 			//no circulation
					0x0300,			//stimulate times is 4
					0x00,			//increment numerator is 0
					0x0001,			//increment denominator is 1
					0x01,			//default stimulate amplitude is 1mA
					0xFF,			//end flag,should be "FF FF FF"
			};

configNulltx txconfigNull = {
					0x80,			//communication header
					0x02,			//transmit data stream
					0x08, 			//default channel is 8th channel
					0x0000, 		//length is 00
					0xFF,			//end flag,should be "FF FF FF"
			};

void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;
  //u16 USART_IT

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_Clock = USART_Clock_Disable;
  USART_InitStructure.USART_CPOL = USART_CPOL_Low;
  USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_InitStructure.USART_LastBit = USART_LastBit_Disable;

  USART_Init(USART2, &USART_InitStructure);
	USART_Init(USART1, &USART_InitStructure);
  USART_Init(USART3, &USART_InitStructure);

	USART_Init(UART4, &USART_InitStructure);
  USART_Init(UART5, &USART_InitStructure);

  USART_ITConfig(USART2, USART_IT_PE, ENABLE); 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
  /* Enable USART2 */
  USART_Cmd(USART2, ENABLE);
	
	USART_ITConfig(USART1, USART_IT_PE, ENABLE); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
  /* Enable USART1 */
  USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART3, USART_IT_PE, ENABLE); 
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); 
  /* Enable USART3 */
  USART_Cmd(USART3, ENABLE);
	
	USART_ITConfig(UART4, USART_IT_PE, ENABLE); 
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); 
  /* Enable UART4 */
  USART_Cmd(UART4, ENABLE);
	
	USART_ITConfig(UART5, USART_IT_PE, ENABLE); 
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); 
  /* Enable UART5 */
  USART_Cmd(UART5, ENABLE);
		
}


 void USART2_Putc(u16 c)  
{  
    USART_SendData(USART2, c);  
   
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET ); 
}  

void USART2_Puts(char * str)  
{  
    while(*str)  
    {  
        USART_SendData(USART2, *str++);  
        /* Loop until the end of transmission */  
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);  
    }  
}  
u16 USART2_ReceiveC(void)
{
	 u16 i = 0;
	 i = USART_ReceiveData(USART2);
	 while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	 return i;
}

void USART2_ReceiveS(u16 *str,int Datalength)
{
	  int ReceiveDateLength = 0;
	  if ( ReceiveDateLength < Datalength)
	  {
		*(str + ReceiveDateLength) = USART2_ReceiveC();
		ReceiveDateLength++;
      }
}

//multichannel  lxd
//USART1
 void USART1_Putc(u16 c)  
{  
    USART_SendData(USART1, c);  
   
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET ); 
}  

void USART1_Puts(char * str)  
{  
    while(*str)  
    {  
        USART_SendData(USART1, *str++);  
        /* Loop until the end of transmission */  
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);  
    }  
}  
u16 USART1_ReceiveC(void)
{
	 u16 i = 0;
	 i = USART_ReceiveData(USART1);
	 while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	 return i;
}

void USART1_ReceiveS(u16 *str,int Datalength)
{
	  int ReceiveDateLength = 0;
	  if ( ReceiveDateLength < Datalength)
	  {
		*(str + ReceiveDateLength) = USART1_ReceiveC();
		ReceiveDateLength++;
      }
}

//USART3
 void USART3_Putc(u16 c)  
{  
    USART_SendData(USART3, c);  
   
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET ); 
}  

void USART3_Puts(char * str)  
{  
    while(*str)  
    {  
        USART_SendData(USART3, *str++);  
        /* Loop until the end of transmission */  
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);  
    }  
}  
u16 USART3_ReceiveC(void)
{
	 u16 i = 0;
	 i = USART_ReceiveData(USART3);
	 while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
	 return i;
}

void USART3_ReceiveS(u16 *str,int Datalength)
{
	  int ReceiveDateLength = 0;
	  if ( ReceiveDateLength < Datalength)
	  {
		*(str + ReceiveDateLength) = USART3_ReceiveC();
		ReceiveDateLength++;
      }
}

//UART4
 void UART4_Putc(u16 c)  
{  
    USART_SendData(UART4, c);  
   
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET ); 
}  

void UART4_Puts(char * str)  
{  
    while(*str)  
    {  
        USART_SendData(UART4, *str++);  
        /* Loop until the end of transmission */  
        while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);  
    }  
}  
u16 UART4_ReceiveC(void)
{
	 u16 i = 0;
	 i = USART_ReceiveData(UART4);
	 while(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET);
	 return i;
}

void UART4_ReceiveS(u16 *str,int Datalength)
{
	  int ReceiveDateLength = 0;
	  if ( ReceiveDateLength < Datalength)
	  {
		*(str + ReceiveDateLength) = UART4_ReceiveC();
		ReceiveDateLength++;
      }
}

//UART5
 void UART5_Putc(u16 c)  
{  
    USART_SendData(UART5, c);  
   
	while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
	while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET ); 
}  

void UART5_Puts(char * str)  
{  
    while(*str)  
    {  
        USART_SendData(UART5, *str++);  
        /* Loop until the end of transmission */  
        while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);  
    }  
}  
u16 UART5_ReceiveC(void)
{
	 u16 i = 0;
	 i = USART_ReceiveData(UART5);
	 while(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET);
	 return i;
}

void UART5_ReceiveS(u16 *str,int Datalength)
{
	  int ReceiveDateLength = 0;
	  if ( ReceiveDateLength < Datalength)
	  {
		*(str + ReceiveDateLength) = UART5_ReceiveC();
		ReceiveDateLength++;
      }
}
//end multichannnel lxd

/*******************************************************************************
* Added by Alex, for sensory pressure acquiring
*******************************************************************************/

u16 UartCommand_tx(u8 CMD)
{
	txcommand.COMMAND = CMD;
	USART2_Putc(txcommand.HEADER );
	USART2_Putc(txcommand.CONTROL);
	USART2_Putc(txcommand.COMMAND);
	return 0;
}

u16 UartConfig_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode)
{
	txconfig.CHANNEL = sti_chl + 1;
	txconfig.AMPLITUDE = sti_amp;
	if (mode==0)
	{txconfig.WIDTH = pulse_width - txconfig.FREQUENCY;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	USART2_Putc(txconfig.HEADER );
	USART2_Putc(txconfig.CONTROL);
	USART2_Putc(txconfig.CHANNEL);

	USART2_Putc((u8)(txconfig.LENGTH >> 8));
	USART2_Putc((u8)txconfig.LENGTH );

	USART2_Putc((u8)(txconfig.WIDTH >> 8));
	USART2_Putc((u8)txconfig.WIDTH );

	USART2_Putc((u8)(txconfig.FREQUENCY >> 8));
	USART2_Putc((u8)txconfig.FREQUENCY);

	USART2_Putc(txconfig.DELAY);
	USART2_Putc(txconfig.CIRCULATE);

	USART2_Putc((u8)(txconfig.TIMES >> 8));
	USART2_Putc((u8)txconfig.TIMES);

	USART2_Putc(txconfig.NUMERATOR);

	USART2_Putc((u8)(txconfig.DENOMINATOR >> 8));
	USART2_Putc((u8)txconfig.DENOMINATOR);

	USART2_Putc(txconfig.AMPLITUDE);

	USART2_Putc(txconfig.ENDFLAG);
	USART2_Putc(txconfig.ENDFLAG);
	USART2_Putc(txconfig.ENDFLAG);
	}

	if (mode==1)
	{txconfig.WIDTH = pulse_width - 0x0032;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	USART2_Putc(txconfig.HEADER );
	USART2_Putc(txconfig.CONTROL);
	USART2_Putc(txconfig.CHANNEL);

	USART2_Putc((u8)(txconfig.LENGTH >> 8));
	USART2_Putc((u8)txconfig.LENGTH );

	USART2_Putc((u8)(txconfig.WIDTH >> 8));
	USART2_Putc((u8)txconfig.WIDTH );

	USART2_Putc((u8)0x00);
	USART2_Putc((u8)0x32);

	USART2_Putc(txconfig.DELAY);
	USART2_Putc(txconfig.CIRCULATE);
											 
	USART2_Putc((u8)(txconfig.TIMES >> 8));
	USART2_Putc((u8)txconfig.TIMES);

	USART2_Putc(txconfig.NUMERATOR);

	USART2_Putc((u8)(txconfig.DENOMINATOR >> 8));
	USART2_Putc((u8)txconfig.DENOMINATOR);

	USART2_Putc(txconfig.AMPLITUDE);

	USART2_Putc(txconfig.ENDFLAG);
	USART2_Putc(txconfig.ENDFLAG);
	USART2_Putc(txconfig.ENDFLAG);
	}
	return 0;
} 

u16 UartConfigNull_tx(u8 sti_chl)
{
	txconfigNull.CHANNEL = sti_chl + 1;

	USART2_Putc(txconfigNull.HEADER );
	USART2_Putc(txconfigNull.CONTROL);
	USART2_Putc(txconfigNull.CHANNEL);

	USART2_Putc((u8)(txconfigNull.LENGTH >> 8));
	USART2_Putc((u8)txconfigNull.LENGTH );

	USART2_Putc(txconfigNull.ENDFLAG);
	USART2_Putc(txconfigNull.ENDFLAG);
	USART2_Putc(txconfigNull.ENDFLAG);

	return 0;
}

u16 Uart_confirm_command(u8 command)
{
	if (receiveDataFromCom2.commandType == command)
	{
		receiveDataFromCom3.commandType = 0;
		receiveDataFromCom3.channel = 0;
		return 0;
	}
	else
		return 1;
}

u16 Uart_confirm_channel(u8 channel)
{
	if (receiveDataFromCom2.channel == channel)
	{
		receiveDataFromCom2.commandType = 0;
		receiveDataFromCom2.channel = 0;
		return 0;
	}
	else
		return 1;
}

//multichannnel lxd
//USART1
u16 Uart1Command_tx(u8 CMD)
{
	txcommand.COMMAND = CMD;
	USART1_Putc(txcommand.HEADER );
	USART1_Putc(txcommand.CONTROL);
	USART1_Putc(txcommand.COMMAND);
	return 0;
}

u16 Uart1Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode)
{
	txconfig.CHANNEL = sti_chl + 1;
	txconfig.AMPLITUDE = sti_amp;
	if (mode==0)
	{txconfig.WIDTH = pulse_width - txconfig.FREQUENCY;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	USART1_Putc(txconfig.HEADER );
	USART1_Putc(txconfig.CONTROL);
	USART1_Putc(txconfig.CHANNEL);

	USART1_Putc((u8)(txconfig.LENGTH >> 8));
	USART1_Putc((u8)txconfig.LENGTH );

	USART1_Putc((u8)(txconfig.WIDTH >> 8));
	USART1_Putc((u8)txconfig.WIDTH );

	USART1_Putc((u8)(txconfig.FREQUENCY >> 8));
	USART1_Putc((u8)txconfig.FREQUENCY);

	USART1_Putc(txconfig.DELAY);
	USART1_Putc(txconfig.CIRCULATE);

	USART1_Putc((u8)(txconfig.TIMES >> 8));
	USART1_Putc((u8)txconfig.TIMES);

	USART1_Putc(txconfig.NUMERATOR);

	USART1_Putc((u8)(txconfig.DENOMINATOR >> 8));
	USART1_Putc((u8)txconfig.DENOMINATOR);

	USART1_Putc(txconfig.AMPLITUDE);

	USART1_Putc(txconfig.ENDFLAG);
	USART1_Putc(txconfig.ENDFLAG);
	USART1_Putc(txconfig.ENDFLAG);
	}

	if (mode==1)
	{txconfig.WIDTH = pulse_width - 0x0032;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	USART1_Putc(txconfig.HEADER );
	USART1_Putc(txconfig.CONTROL);
	USART1_Putc(txconfig.CHANNEL);

	USART1_Putc((u8)(txconfig.LENGTH >> 8));
	USART1_Putc((u8)txconfig.LENGTH );

	USART1_Putc((u8)(txconfig.WIDTH >> 8));
	USART1_Putc((u8)txconfig.WIDTH );

	USART1_Putc((u8)0x00);
	USART1_Putc((u8)0x32);

	USART1_Putc(txconfig.DELAY);
	USART1_Putc(txconfig.CIRCULATE);
											 
	USART1_Putc((u8)(txconfig.TIMES >> 8));
	USART1_Putc((u8)txconfig.TIMES);

	USART1_Putc(txconfig.NUMERATOR);

	USART1_Putc((u8)(txconfig.DENOMINATOR >> 8));
	USART1_Putc((u8)txconfig.DENOMINATOR);

	USART1_Putc(txconfig.AMPLITUDE);

	USART1_Putc(txconfig.ENDFLAG);
	USART1_Putc(txconfig.ENDFLAG);
	USART1_Putc(txconfig.ENDFLAG);
	}
	return 0;
} 

u16 Uart1ConfigNull_tx(u8 sti_chl)
{
	txconfigNull.CHANNEL = sti_chl + 1;

	USART1_Putc(txconfigNull.HEADER );
	USART1_Putc(txconfigNull.CONTROL);
	USART1_Putc(txconfigNull.CHANNEL);

	USART1_Putc((u8)(txconfigNull.LENGTH >> 8));
	USART1_Putc((u8)txconfigNull.LENGTH );

	USART1_Putc(txconfigNull.ENDFLAG);
	USART1_Putc(txconfigNull.ENDFLAG);
	USART1_Putc(txconfigNull.ENDFLAG);

	return 0;
}


//USART3
u16 Uart3Command_tx(u8 CMD)
{
	txcommand.COMMAND = CMD;
	USART3_Putc(txcommand.HEADER );
	USART3_Putc(txcommand.CONTROL);
	USART3_Putc(txcommand.COMMAND);
	return 0;
}

u16 Uart3Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode)
{
	txconfig.CHANNEL = sti_chl + 1;
	txconfig.AMPLITUDE = sti_amp;
	if (mode==0)
	{txconfig.WIDTH = pulse_width - txconfig.FREQUENCY;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	USART3_Putc(txconfig.HEADER );
	USART3_Putc(txconfig.CONTROL);
	USART3_Putc(txconfig.CHANNEL);

	USART3_Putc((u8)(txconfig.LENGTH >> 8));
	USART3_Putc((u8)txconfig.LENGTH );

	USART3_Putc((u8)(txconfig.WIDTH >> 8));
	USART3_Putc((u8)txconfig.WIDTH );

	USART3_Putc((u8)(txconfig.FREQUENCY >> 8));
	USART3_Putc((u8)txconfig.FREQUENCY);

	USART3_Putc(txconfig.DELAY);
	USART3_Putc(txconfig.CIRCULATE);

	USART3_Putc((u8)(txconfig.TIMES >> 8));
	USART3_Putc((u8)txconfig.TIMES);

	USART3_Putc(txconfig.NUMERATOR);

	USART3_Putc((u8)(txconfig.DENOMINATOR >> 8));
	USART3_Putc((u8)txconfig.DENOMINATOR);

	USART3_Putc(txconfig.AMPLITUDE);

	USART3_Putc(txconfig.ENDFLAG);
	USART3_Putc(txconfig.ENDFLAG);
	USART3_Putc(txconfig.ENDFLAG);
	}

	if (mode==1)
	{txconfig.WIDTH = pulse_width - 0x0032;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	USART3_Putc(txconfig.HEADER );
	USART3_Putc(txconfig.CONTROL);
	USART3_Putc(txconfig.CHANNEL);

	USART3_Putc((u8)(txconfig.LENGTH >> 8));
	USART3_Putc((u8)txconfig.LENGTH );

	USART3_Putc((u8)(txconfig.WIDTH >> 8));
	USART3_Putc((u8)txconfig.WIDTH );

	USART3_Putc((u8)0x00);
	USART3_Putc((u8)0x32);

	USART3_Putc(txconfig.DELAY);
	USART3_Putc(txconfig.CIRCULATE);
											 
	USART3_Putc((u8)(txconfig.TIMES >> 8));
	USART3_Putc((u8)txconfig.TIMES);

	USART3_Putc(txconfig.NUMERATOR);

	USART3_Putc((u8)(txconfig.DENOMINATOR >> 8));
	USART3_Putc((u8)txconfig.DENOMINATOR);

	USART3_Putc(txconfig.AMPLITUDE);

	USART3_Putc(txconfig.ENDFLAG);
	USART3_Putc(txconfig.ENDFLAG);
	USART3_Putc(txconfig.ENDFLAG);
	}
	return 0;
} 

u16 Uart3ConfigNull_tx(u8 sti_chl)
{
	txconfigNull.CHANNEL = sti_chl + 1;

	USART3_Putc(txconfigNull.HEADER );
	USART3_Putc(txconfigNull.CONTROL);
	USART3_Putc(txconfigNull.CHANNEL);

	USART3_Putc((u8)(txconfigNull.LENGTH >> 8));
	USART3_Putc((u8)txconfigNull.LENGTH );

	USART3_Putc(txconfigNull.ENDFLAG);
	USART3_Putc(txconfigNull.ENDFLAG);
	USART3_Putc(txconfigNull.ENDFLAG);

	return 0;
}


//UART4
u16 Uart4Command_tx(u8 CMD)
{
	txcommand.COMMAND = CMD;
	UART4_Putc(txcommand.HEADER );
	UART4_Putc(txcommand.CONTROL);
	UART4_Putc(txcommand.COMMAND);
	return 0;
}

u16 Uart4Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode)
{
	txconfig.CHANNEL = sti_chl + 1;
	txconfig.AMPLITUDE = sti_amp;
	if (mode==0)
	{txconfig.WIDTH = pulse_width - txconfig.FREQUENCY;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	UART4_Putc(txconfig.HEADER );
	UART4_Putc(txconfig.CONTROL);
	UART4_Putc(txconfig.CHANNEL);

	UART4_Putc((u8)(txconfig.LENGTH >> 8));
	UART4_Putc((u8)txconfig.LENGTH );

	UART4_Putc((u8)(txconfig.WIDTH >> 8));
	UART4_Putc((u8)txconfig.WIDTH );

	UART4_Putc((u8)(txconfig.FREQUENCY >> 8));
	UART4_Putc((u8)txconfig.FREQUENCY);

	UART4_Putc(txconfig.DELAY);
	UART4_Putc(txconfig.CIRCULATE);

	UART4_Putc((u8)(txconfig.TIMES >> 8));
	UART4_Putc((u8)txconfig.TIMES);

	UART4_Putc(txconfig.NUMERATOR);

	UART4_Putc((u8)(txconfig.DENOMINATOR >> 8));
	UART4_Putc((u8)txconfig.DENOMINATOR);

	UART4_Putc(txconfig.AMPLITUDE);

	UART4_Putc(txconfig.ENDFLAG);
	UART4_Putc(txconfig.ENDFLAG);
	UART4_Putc(txconfig.ENDFLAG);
	}

	if (mode==1)
	{txconfig.WIDTH = pulse_width - 0x0032;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	UART4_Putc(txconfig.HEADER );
	UART4_Putc(txconfig.CONTROL);
	UART4_Putc(txconfig.CHANNEL);

	UART4_Putc((u8)(txconfig.LENGTH >> 8));
	UART4_Putc((u8)txconfig.LENGTH );

	UART4_Putc((u8)(txconfig.WIDTH >> 8));
	UART4_Putc((u8)txconfig.WIDTH );

	UART4_Putc((u8)0x00);
	UART4_Putc((u8)0x32);

	UART4_Putc(txconfig.DELAY);
	UART4_Putc(txconfig.CIRCULATE);
											 
	UART4_Putc((u8)(txconfig.TIMES >> 8));
	UART4_Putc((u8)txconfig.TIMES);

	UART4_Putc(txconfig.NUMERATOR);

	UART4_Putc((u8)(txconfig.DENOMINATOR >> 8));
	UART4_Putc((u8)txconfig.DENOMINATOR);

	UART4_Putc(txconfig.AMPLITUDE);

	UART4_Putc(txconfig.ENDFLAG);
	UART4_Putc(txconfig.ENDFLAG);
	UART4_Putc(txconfig.ENDFLAG);
	}
	return 0;
} 

u16 Uart4ConfigNull_tx(u8 sti_chl)
{
	txconfigNull.CHANNEL = sti_chl + 1;

	UART4_Putc(txconfigNull.HEADER );
	UART4_Putc(txconfigNull.CONTROL);
	UART4_Putc(txconfigNull.CHANNEL);

	UART4_Putc((u8)(txconfigNull.LENGTH >> 8));
	UART4_Putc((u8)txconfigNull.LENGTH );

	UART4_Putc(txconfigNull.ENDFLAG);
	UART4_Putc(txconfigNull.ENDFLAG);
	UART4_Putc(txconfigNull.ENDFLAG);

	return 0;
}

//UART5
u16 Uart5Command_tx(u8 CMD)
{
	txcommand.COMMAND = CMD;
	UART5_Putc(txcommand.HEADER );
	UART5_Putc(txcommand.CONTROL);
	UART5_Putc(txcommand.COMMAND);
	return 0;
}

u16 Uart5Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode)
{
	txconfig.CHANNEL = sti_chl + 1;
	txconfig.AMPLITUDE = sti_amp;
	if (mode==0)
	{txconfig.WIDTH = pulse_width - txconfig.FREQUENCY;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	UART5_Putc(txconfig.HEADER );
	UART5_Putc(txconfig.CONTROL);
	UART5_Putc(txconfig.CHANNEL);

	UART5_Putc((u8)(txconfig.LENGTH >> 8));
	UART5_Putc((u8)txconfig.LENGTH );

	UART5_Putc((u8)(txconfig.WIDTH >> 8));
	UART5_Putc((u8)txconfig.WIDTH );

	UART5_Putc((u8)(txconfig.FREQUENCY >> 8));
	UART5_Putc((u8)txconfig.FREQUENCY);

	UART5_Putc(txconfig.DELAY);
	UART5_Putc(txconfig.CIRCULATE);

	UART5_Putc((u8)(txconfig.TIMES >> 8));
	UART5_Putc((u8)txconfig.TIMES);

	UART5_Putc(txconfig.NUMERATOR);

	UART5_Putc((u8)(txconfig.DENOMINATOR >> 8));
	UART5_Putc((u8)txconfig.DENOMINATOR);

	UART5_Putc(txconfig.AMPLITUDE);

	UART5_Putc(txconfig.ENDFLAG);
	UART5_Putc(txconfig.ENDFLAG);
	UART5_Putc(txconfig.ENDFLAG);
	}

	if (mode==1)
	{txconfig.WIDTH = pulse_width - 0x0032;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;
	UART5_Putc(txconfig.HEADER );
	UART5_Putc(txconfig.CONTROL);
	UART5_Putc(txconfig.CHANNEL);

	UART5_Putc((u8)(txconfig.LENGTH >> 8));
	UART5_Putc((u8)txconfig.LENGTH );

	UART5_Putc((u8)(txconfig.WIDTH >> 8));
	UART5_Putc((u8)txconfig.WIDTH );

	UART5_Putc((u8)0x00);
	UART5_Putc((u8)0x32);

	UART5_Putc(txconfig.DELAY);
	UART5_Putc(txconfig.CIRCULATE);
											 
	UART5_Putc((u8)(txconfig.TIMES >> 8));
	UART5_Putc((u8)txconfig.TIMES);

	UART5_Putc(txconfig.NUMERATOR);

	UART5_Putc((u8)(txconfig.DENOMINATOR >> 8));
	UART5_Putc((u8)txconfig.DENOMINATOR);

	UART5_Putc(txconfig.AMPLITUDE);

	UART5_Putc(txconfig.ENDFLAG);
	UART5_Putc(txconfig.ENDFLAG);
	UART5_Putc(txconfig.ENDFLAG);
	}
	return 0;
} 

u16 Uart5ConfigNull_tx(u8 sti_chl)
{
	txconfigNull.CHANNEL = sti_chl + 1;

	UART5_Putc(txconfigNull.HEADER );
	UART5_Putc(txconfigNull.CONTROL);
	UART5_Putc(txconfigNull.CHANNEL);

	UART5_Putc((u8)(txconfigNull.LENGTH >> 8));
	UART5_Putc((u8)txconfigNull.LENGTH );

	UART5_Putc(txconfigNull.ENDFLAG);
	UART5_Putc(txconfigNull.ENDFLAG);
	UART5_Putc(txconfigNull.ENDFLAG);

	return 0;
}