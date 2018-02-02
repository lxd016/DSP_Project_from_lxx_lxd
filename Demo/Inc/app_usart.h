/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_USART_H
#define __APP_USART_H


#include "stm32f10x_lib.h"

typedef struct {
	volatile u8 HEADER;
	volatile u8 CONTROL;
	volatile u8 CHANNEL;
	volatile u16 LENGTH;
	volatile u16 WIDTH;
	volatile u16 FREQUENCY;
	volatile u8 DELAY;
	volatile u8 CIRCULATE;
	volatile u16 TIMES;
	volatile u8 NUMERATOR;
	volatile u16 DENOMINATOR;
	volatile u8 AMPLITUDE;
	volatile u8 ENDFLAG;
} configtx;

typedef struct {
	volatile u8 HEADER;
	volatile u8 CONTROL;
	volatile u8 CHANNEL;
	volatile u16 LENGTH;
	volatile u8 ENDFLAG;
} configNulltx;

typedef struct {
	volatile u8 HEADER;
	volatile u8 CONTROL;
	volatile u8 COMMAND;
} commandtx;

typedef struct receiveData
{
	vu8 startFlag;                   //communication start flag ('8', 0x38)
	vu8 startConfirmFlag;            //communication start confirm flag('0', 0x30)
	vu8 dataLength;                  //data length, record the received data length(to identify the exact '0' data received)
	vu16 temp;
	vu8 commandType;                 //confrim the command type received (start, stop, search)
	vu8 commandTypeFlag;						 //if received the command type
	vu8 channel;										 //confirm the channel received(0x01~0x08)
	vu8 channelFlag;                 //if received the stimulation channel
	vu8 DSPDSUconnectedFlag;
	vu8 DSPDSUreceivedFlag;
	vu8 DSPDSUStartStimuFlag;
	vu8 DSPDSUStopStimuFlag;
}ReceiveDataType;



//-----------------------------------------------------------------------------
// Public Function Declaration
//-----------------------------------------------------------------------------
u32 Uart_tx(u16 * Revbuf);

u16 UartCommand_tx(u8 CMD);
u16 UartConfig_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode);
u16 UartConfigNull_tx(u8 sti_chl);
u16 Uart_confirm_command(u8 command);
u16 Uart_confirm_channel(u8 channel);

//MULTICHANNEL LXD
u16 Uart1Command_tx(u8 CMD);
u16 Uart1Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode);
u16 Uart1ConfigNull_tx(u8 sti_chl);
u16 Uart1_confirm_command(u8 command);
u16 Uart1_confirm_channel(u8 channel);

u16 Uart3Command_tx(u8 CMD);
u16 Uart3Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode);
u16 Uart3ConfigNull_tx(u8 sti_chl);
u16 Uart3_confirm_command(u8 command);
u16 Uart3_confirm_channel(u8 channel);

u16 Uart4Command_tx(u8 CMD);
u16 Uart4Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode);
u16 Uart4ConfigNull_tx(u8 sti_chl);
u16 Uart4_confirm_command(u8 command);
u16 Uart4_confirm_channel(u8 channel);

u16 Uart5Command_tx(u8 CMD);
u16 Uart5Config_tx(u8 sti_chl, u8 sti_amp, u16 pulse_width,u8 mode);
u16 Uart5ConfigNull_tx(u8 sti_chl);
u16 Uart5_confirm_command(u8 command);
u16 Uart5_confirm_channel(u8 channel);

//END LXD

void USART_Configuration(void);
void USART2_Putc(u16 c);
void USART2_Puts(char * str);
u16 USART2_ReceiveC(void);
void USART2_ReceiveS(u16 *str,int Datalength);
//int fputc(int ch, FILE *f);

#endif /* APP_USART_H */

