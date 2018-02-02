/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_it.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"
#include "app_usart.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern vu32 ret;
extern vu16 temp;
extern ReceiveDataType receiveDataFromCom1;
extern ReceiveDataType receiveDataFromCom2;
extern ReceiveDataType receiveDataFromCom3;
extern ReceiveDataType receiveDataFromCom4;
extern ReceiveDataType receiveDataFromCom5;

extern MasterUnitStateType MasterUnitState;
extern vu8 codeBuff;
extern queueBufferType queueBuffer[8];
extern vu8 codeBuf;
extern vu16 IT_CNT;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickHandler(void)
{
/* Decrement the TimingDelay variable */
  Decrement_TimingDelay();
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : This function handles DMA1 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : This function handles DMA1 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : This function handles DMA1 Channel 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : This function handles DMA1 Channel 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel6_IRQHandler
* Description    : This function handles DMA1 Channel 6 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel7_IRQHandler
* Description    : This function handles DMA1 Channel 7 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
	
}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
	
}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
	{	
		//收到中断信号后接受数据(one byte), 存入temp中
		receiveDataFromCom1.temp = USART_ReceiveData(USART1);
		
		//接收到的数据为数据头(temp = 0x38)，即之前无数据接收(startFlag == 0)
		//if (receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom1.temp == 0xBC)   //38
			{
				receiveDataFromCom1.DSPDSUconnectedFlag = 1;
				/*receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataLength = 1;
				receiveDataFromCom.commandTypeFlag = 0;
				receiveDataFromCom.commandType = 0;
				receiveDataFromCom.channelFlag = 0;
				receiveDataFromCom.channel = 0;	*/			
			}	
      if (receiveDataFromCom1.temp == 0x29)
			{
				receiveDataFromCom1.DSPDSUreceivedFlag = 1;
			}
      if (receiveDataFromCom1.temp == 0xAA)
			{
				receiveDataFromCom1.DSPDSUStartStimuFlag = 1;
			}
      if (receiveDataFromCom1.temp == 0xBB)
			{
				receiveDataFromCom1.DSPDSUStopStimuFlag = 1;
			}
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			return;
		}
	}
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{
	//接收数据形式为6位: "800x0y",其中"80"两位为数据头，此处以判别第一位'8'(0x38)确认数据头
	if(USART_GetFlagStatus(USART2,USART_IT_RXNE)==SET)
	{	
		//收到中断信号后接受数据(one byte), 存入temp中
		receiveDataFromCom2.temp = USART_ReceiveData(USART2);
		
		//接收到的数据为数据头(temp = 0x38)，即之前无数据接收(startFlag == 0)
		//if (receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom2.temp == 0xBC)   //38
			{
				receiveDataFromCom2.DSPDSUconnectedFlag = 1;
				/*receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataLength = 1;
				receiveDataFromCom.commandTypeFlag = 0;
				receiveDataFromCom.commandType = 0;
				receiveDataFromCom.channelFlag = 0;
				receiveDataFromCom.channel = 0;	*/			
			}	
      if (receiveDataFromCom2.temp == 0x29)
			{
				receiveDataFromCom2.DSPDSUreceivedFlag = 1;
			}
      if (receiveDataFromCom2.temp == 0xAA)
			{
				receiveDataFromCom2.DSPDSUStartStimuFlag = 1;
			}
      if (receiveDataFromCom2.temp == 0xBB)
			{
				receiveDataFromCom2.DSPDSUStopStimuFlag = 1;
			}
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			return;
		}
		// startFlag == 1, 确认数据头，开始接收下一位数据
/*******************************************************************************lxd
		else
		{
			//temp又接收一个数据，此处增加已接收数据长度dataLength
			if(++receiveDataFromCom.dataLength > 6)
			{
				receiveDataFromCom.startFlag = 0;
				USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				return;
			}
			
			//若收到数据为字符'0', 不作任何操作
			if(receiveDataFromCom.temp == '0')
			{
				USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				return;
			}

			//接收到第四个数据时，判断该数据包是返回命令值还是通道值
			if (receiveDataFromCom.dataLength == 4)
			{
				if (receiveDataFromCom.temp == '1') //不能确定是命令还是通道，假设为channel
				{
					receiveDataFromCom.channelFlag = 1;
					receiveDataFromCom.channel = 0x01;           //虽然无法确认类型，但可先置channel==1
				}
				else if (receiveDataFromCom.temp >= '2' && receiveDataFromCom.temp <= '8')
				{
					receiveDataFromCom.channelFlag = 1;
					receiveDataFromCom.channel = receiveDataFromCom.temp - 0x30;
				}
				else //接收数据有误，数据丢弃，准备下一次数据接收
				{
					receiveDataFromCom.startFlag = 0;
				}
				
				USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				return;
			}
			
			//接收到第6个数据时，判断命令类型或对通道数据位操作
			if (receiveDataFromCom.dataLength == 6 )
			{
				// 注意：当数据为'800101'时 command 和 channel 均被标记，因此处理任意一个后需将两者同时置零
				if (receiveDataFromCom.temp == '1' && receiveDataFromCom.channel == 0x01)  //'800101'
				{
					receiveDataFromCom.commandTypeFlag = 1;
					receiveDataFromCom.commandType = 1;
				}
				
				if (receiveDataFromCom.temp == '2' || receiveDataFromCom.temp == '3')   //'800102' or '800103'
				{
					receiveDataFromCom.channel = 0;
					receiveDataFromCom.channelFlag = 0;
					receiveDataFromCom.commandTypeFlag = 1;
					receiveDataFromCom.commandType = receiveDataFromCom.temp - 0x30;
				}				
				
				//接收数据有误，数据丢弃，准备下一次数据接收
				receiveDataFromCom.startFlag = 0;
				USART_ClearITPendingBit(USART2, USART_IT_RXNE);
				return;
			}
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		return;
		****************************************************/
	}
}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
		if(USART_GetFlagStatus(USART3,USART_IT_RXNE)==SET)
	{	
		//收到中断信号后接受数据(one byte), 存入temp中
		receiveDataFromCom3.temp = USART_ReceiveData(USART3);
		
		//接收到的数据为数据头(temp = 0x38)，即之前无数据接收(startFlag == 0)
		//if (receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom3.temp == 0xBC)   //38
			{
				receiveDataFromCom3.DSPDSUconnectedFlag = 1;
				/*receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataLength = 1;
				receiveDataFromCom.commandTypeFlag = 0;
				receiveDataFromCom.commandType = 0;
				receiveDataFromCom.channelFlag = 0;
				receiveDataFromCom.channel = 0;	*/			
			}	
      if (receiveDataFromCom3.temp == 0x29)
			{
				receiveDataFromCom3.DSPDSUreceivedFlag = 1;
			}
      if (receiveDataFromCom3.temp == 0xAA)
			{
				receiveDataFromCom3.DSPDSUStartStimuFlag = 1;
			}
      if (receiveDataFromCom3.temp == 0xBB)
			{
				receiveDataFromCom3.DSPDSUStopStimuFlag = 1;
			}
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);
			return;
		}
	}
}

/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : This function handles TIM8 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : This function handles TIM8 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : This function handles TIM8 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_CC_IRQHandler
* Description    : This function handles TIM8 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : This function handles ADC3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : FSMC_IRQHandler
* Description    : This function handles FSMC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : This function handles TIM5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : This function handles SPI3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles UART4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{
		if(USART_GetFlagStatus(UART4,USART_IT_RXNE)==SET)
	{	
		//收到中断信号后接受数据(one byte), 存入temp中
		receiveDataFromCom4.temp = USART_ReceiveData(UART4);
		
		//接收到的数据为数据头(temp = 0x38)，即之前无数据接收(startFlag == 0)
		//if (receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom4.temp == 0xBC)   //38
			{
				receiveDataFromCom4.DSPDSUconnectedFlag = 1;
				/*receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataLength = 1;
				receiveDataFromCom.commandTypeFlag = 0;
				receiveDataFromCom.commandType = 0;
				receiveDataFromCom.channelFlag = 0;
				receiveDataFromCom.channel = 0;	*/			
			}	
      if (receiveDataFromCom4.temp == 0x29)
			{
				receiveDataFromCom4.DSPDSUreceivedFlag = 1;
			}
      if (receiveDataFromCom4.temp == 0xAA)
			{
				receiveDataFromCom4.DSPDSUStartStimuFlag = 1;
			}
      if (receiveDataFromCom4.temp == 0xBB)
			{
				receiveDataFromCom4.DSPDSUStopStimuFlag = 1;
			}
			USART_ClearITPendingBit(UART4, USART_IT_RXNE);
			return;
		}
	}
}

/*******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : This function handles UART5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART5_IRQHandler(void)
{
			if(USART_GetFlagStatus(UART5,USART_IT_RXNE)==SET)
	{	
		//收到中断信号后接受数据(one byte), 存入temp中
		receiveDataFromCom5.temp = USART_ReceiveData(UART5);
		
		//接收到的数据为数据头(temp = 0x38)，即之前无数据接收(startFlag == 0)
		//if (receiveDataFromCom.startFlag == 0)
		{
			if ( receiveDataFromCom5.temp == 0xBC)   //38
			{
				receiveDataFromCom5.DSPDSUconnectedFlag = 1;
				/*receiveDataFromCom.startFlag = 1;
				receiveDataFromCom.dataLength = 1;
				receiveDataFromCom.commandTypeFlag = 0;
				receiveDataFromCom.commandType = 0;
				receiveDataFromCom.channelFlag = 0;
				receiveDataFromCom.channel = 0;	*/			
			}	
      if (receiveDataFromCom5.temp == 0x29)
			{
				receiveDataFromCom5.DSPDSUreceivedFlag = 1;
			}
      if (receiveDataFromCom5.temp == 0xAA)
			{
				receiveDataFromCom5.DSPDSUStartStimuFlag = 1;
			}
      if (receiveDataFromCom5.temp == 0xBB)
			{
				receiveDataFromCom5.DSPDSUStopStimuFlag = 1;
			}
			USART_ClearITPendingBit(UART5, USART_IT_RXNE);
			return;
		}
	}
}

/*******************************************************************************
* Function Name  : TIM6_IRQHandler
* Description    : This function handles TIM6 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : This function handles TIM7 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : This function handles DMA2 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : This function handles DMA2 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel4_5_IRQHandler
* Description    : This function handles DMA2 Channel 4 and DMA2 Channel 5
*                  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
