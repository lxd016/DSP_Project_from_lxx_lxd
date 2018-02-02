//-----------------------------------------------------------------------------
// \file    uart.c
// \brief   Initialize and array sending of uart module
//
//-----------------------------------------------------------------------------

#include "types.h"
#include "evmomapl138.h"
#include "evmomapl138_uart.h"
#include "uart.h"

//-----------------------------------------------------------------------------
// Global Variable Initializations
//-----------------------------------------------------------------------------
configtx txconfig = {
					0x80,			//communication header
					0x02,			//transmit data stream
					0x01, 			//default channel is 1st channel
					0x000C, 		//length is 12
					0x0032, 		//default time width is 50us = 0x32H
					0x000A, 		//default frequency is 10 Hz = 0x0064H
					0x0A, 			//default time delay is 10us = 0x0AH
					0x01, 			//no circulation
					0x0004,			//stimulate times is 4
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

commandtx txcommand = {
					0x80,			//communication header
					0x01,			//transmit command stream
					0x02,			//default command is stop, command: 01 start, 02 stop, 03 searching device, 04 end of data transmit
			};

//-----------------------------------------------------------------------------
// \brief   transmit command data through uart port.
//
// \param   uint8_t CMD - the command type to transmit, default is stop(04).
//
// \return  none.
//-----------------------------------------------------------------------------
void UartCommand_tx(uint8_t CMD)
{
	txcommand.COMMAND = CMD;
	UART_txByte(UART2, txcommand.HEADER );
	UART_txByte(UART2, txcommand.CONTROL);
	UART_txByte(UART2, txcommand.COMMAND);
}


//-----------------------------------------------------------------------------
// \brief   transmit stimuli pattern data through uart port.
//
// \param   uint8_t sti_chl - the stimuli channel to be set (0~7).
//
// \param   uint8_t sti_amp - the stimuli amplitude.
//
// \param   uint16_t pulse_width - the stimuli pulse width.
//
// \return  none.
//-----------------------------------------------------------------------------
void UartConfig_tx(uint8_t sti_chl, uint8_t sti_amp, uint16_t pulse_width)
{
	txconfig.CHANNEL = sti_chl + 1;
	txconfig.AMPLITUDE = sti_amp;
	txconfig.WIDTH = pulse_width - txconfig.FREQUENCY;
	if(txconfig.WIDTH < 10)
		txconfig.WIDTH = 10;

	UART_txByte(UART2, txconfig.HEADER );
	UART_txByte(UART2, txconfig.CONTROL);
	UART_txByte(UART2, txconfig.CHANNEL);

	UART_txByte(UART2, (uint8_t)(txconfig.LENGTH >> 8));
	UART_txByte(UART2, (uint8_t)txconfig.LENGTH );

	UART_txByte(UART2, (uint8_t)(txconfig.WIDTH >> 8));
	UART_txByte(UART2, (uint8_t)txconfig.WIDTH );

	UART_txByte(UART2, (uint8_t)(txconfig.FREQUENCY >> 8));
	UART_txByte(UART2, (uint8_t)txconfig.FREQUENCY);

	UART_txByte(UART2, txconfig.DELAY);
	UART_txByte(UART2, txconfig.CIRCULATE);

	UART_txByte(UART2, (uint8_t)(txconfig.TIMES >> 8));
	UART_txByte(UART2, (uint8_t)txconfig.TIMES);

	UART_txByte(UART2, txconfig.NUMERATOR);

	UART_txByte(UART2, (uint8_t)(txconfig.DENOMINATOR >> 8));
	UART_txByte(UART2, (uint8_t)txconfig.DENOMINATOR);

	UART_txByte(UART2, txconfig.AMPLITUDE);

	UART_txByte(UART2, txconfig.ENDFLAG);
	UART_txByte(UART2, txconfig.ENDFLAG);
	UART_txByte(UART2, txconfig.ENDFLAG);
} 

//-----------------------------------------------------------------------------
// \brief   transmit stimuli pattern data through uart port.
//
// \param   uint8_t sti_chl - the stimuli channel to be set (0~7).
//
// \return  none.
//-----------------------------------------------------------------------------
void UartConfigNull_tx(uint8_t sti_chl)
{
	txconfigNull.CHANNEL = sti_chl + 1;

	UART_txByte(UART2, txconfigNull.HEADER );
	UART_txByte(UART2, txconfigNull.CONTROL);
	UART_txByte(UART2, txconfigNull.CHANNEL);

	UART_txByte(UART2, (uint8_t)(txconfigNull.LENGTH >> 8));
	UART_txByte(UART2, (uint8_t)txconfigNull.LENGTH );

	UART_txByte(UART2, txconfigNull.ENDFLAG);
	UART_txByte(UART2, txconfigNull.ENDFLAG);
	UART_txByte(UART2, txconfigNull.ENDFLAG);
}

//-----------------------------------------------------------------------------
// \brief   check if the command is received by the stimulator.
//
// \param   uint8_t command - the command type to be checked (01-03).
//
// \return  uint32_t 'ERR_NO_ERROR' or '1'
//-----------------------------------------------------------------------------
uint32_t Uart_confirm_command(uint8_t command)
{
	uint8_t cnt = 0, recv_data[6]={0};
	for(cnt = 0; cnt<6; cnt++)
	{
		UART_rxByte(UART2, &recv_data[cnt]);
	}

	cnt = command + 0x30;
	if (recv_data[5] == cnt)
	{
		return ERR_NO_ERROR;
	}
	else
		return 1;
}

//-----------------------------------------------------------------------------
// \brief   check if the command is received by the stimulator.
//
// \param   uint8_t channel - the channel to be checked (00-07).
//
// \return  uint32_t 'ERR_NO_ERROR' or '1'
//-----------------------------------------------------------------------------
uint32_t Uart_confirm_channel(uint8_t channel)
{
	uint8_t cnt = 0, recv_data[6]={0};
	for(cnt = 0; cnt<6; cnt++)
	{
		UART_rxByte(UART2, &recv_data[cnt]);
	}

	cnt = channel + 0x31;
	if (recv_data[3] == cnt)
	{
		return ERR_NO_ERROR;
	}
	else
		return 1;
}
