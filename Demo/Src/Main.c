/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main program body
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#include "main.h"

/* Local includes ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED} TestStatus;

/* Private define ------------------------------------------------------------*/
//#define DEBUG
//#define DEBUG_GPIO
/* Private macro -------------------------------------------------------------*/
#define MODULE_AD     1
#define MODULE_SEARCH 1
#define MODULE_PROC   1
#define MODULE_STIM   1

#define CHANNEL_NUM   (10)
/* Private variables ---------------------------------------------------------*/
static vu32 TimingDelay = 0;
vu32 ret; /* for return of the interrupt handling */
ErrorStatus HSEStartUpStatus;
ReceiveDataType receiveDataFromCom1;				   //串口接收数据的
ReceiveDataType receiveDataFromCom2;				   //串口接收数据的
ReceiveDataType receiveDataFromCom3;				   //串口接收数据的
ReceiveDataType receiveDataFromCom4;				   //串口接收数据的
ReceiveDataType receiveDataFromCom5;				   //串口接收数据的
vu16 rtnValue = 0;


/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Config(void);
void Delay(u32 nCount);
void Decrement_TimingDelay(void);
void displayDigital(u16 num,u8 *displayString,u8 displaystringLength);



/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
	u8 displayPara[5] = {0};
	u8 stim_amp[10] = {0,0,0,0,0,0,0,0,0,0};
  u16 stim_pulse[10] = {110,110,110,110,110,110,110,110,110,110};
  float sam_pres[CHANNEL_NUM] = {0,0,0,0,0,0,0,0,0,0};
  u32 read_val[CHANNEL_NUM] = {0,0,0,0,0,0,0,0,0,0};

  u8 chl = 0, amp_flag = 0, pulse_flag = 0,module_train=0,user_button=1,mode_meg=1;
  int iii=20;
	float test1 = 0;
	u8 test2 = 0;
	u8 displayBuf[10];
	float displayBuf2[10];
#ifdef DEBUG
  debug();
#endif

  /* System Clocks Configuration */
  RCC_Configuration();

  /* NVIC Configuration */
  NVIC_Configuration();
  
  /* GPIO ports pins Configuration */
  GPIO_Configuration();

  /* Configure the systick */    
  SysTick_Config();

  /* configure the device */
  USART_Configuration();

  /*configure the sysdata*/
	initads1256();
	GPIO_SetBits(GPIOA, trigger);

  /* Initialize the LCD */
	STM3210E_LCD_Init();
  LCD_Clear(White);
  LCD_SetTextColor(Blue); 
	LCD_DisplayStringLine(Line0, "  Initialize done ");
  LCD_DisplayStringLine(Line1, "| Signal Acquiring |");
 	Delay(10);

#ifdef DEBUG_GPIO
	while(1)
	{
		GPIO_SetBits(GPIO_AD_BANK, ADS1256_IN);
		GPIO_SetBits(GPIO_AD_BANK, ADS1256_CLK);
		GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS);
		Delay(1);
		
		GPIO_ResetBits(GPIO_AD_BANK, ADS1256_IN);
		GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
		GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CS);
		Delay(1);
	}
	
#endif
	
#ifdef DEBUG_GPIO
	while(1)
	{
		GPIO_SetBits(GPIO_AD_BANK, ADS1256_IN2);
		GPIO_SetBits(GPIO_AD_BANK, ADS1256_CLK);
		GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS2);
		Delay(1);
		
		GPIO_ResetBits(GPIO_AD_BANK, ADS1256_IN2);
		GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
		GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CS2);
		Delay(1);
	}
	
#endif
	
	//Send stop stimulating command to make sure no current output
  UartCommand_tx(0x02);
	LCD_Clear(White);
		
	//Begin to search the stimulator

	//Delay(100);

	//rtnValue |= stim_search();
	//Device connected, send initial parameters
while (1)
{
	//USART3_Putc(0x03);
	stim_search();
	LCD_DisplayStringLine(Line0, " Searching Device... ");
	if (receiveDataFromCom3.DSPDSUconnectedFlag == 1)
	//if ((receiveDataFromCom1.DSPDSUconnectedFlag == 1)&&(receiveDataFromCom2.DSPDSUconnectedFlag == 1)&&(receiveDataFromCom3.DSPDSUconnectedFlag == 1)&&(receiveDataFromCom4.DSPDSUconnectedFlag == 1)&&(receiveDataFromCom5.DSPDSUconnectedFlag == 1))
	{
		LCD_DisplayStringLine(Line3, " test... ");
		receiveDataFromCom1.DSPDSUconnectedFlag = 0;
		receiveDataFromCom2.DSPDSUconnectedFlag = 0;
		receiveDataFromCom3.DSPDSUconnectedFlag = 0;
		receiveDataFromCom4.DSPDSUconnectedFlag = 0;
		receiveDataFromCom5.DSPDSUconnectedFlag = 0;
	//rtnValue |= stim_send_init_parameter(stim_amp, stim_pulse);
	
	// If initialize the stimuli para failed, send the "ERROR" signal by Morse Code
/***	while(rtnValue != 0)
	{		
		//莫尔斯电码, 'ERROR'
		// 'E' = '.'
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(10);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30+50);
		
		// 'R' = '.-.'
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(10);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(50);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(10);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30+50);
		
		// 'R' = '.-.'
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(10);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(50);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(10);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30+50);
		
		// 'O' = '---'
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(50);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(50);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(50);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30+50);
		
		// 'R' = '.-.'
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(10);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(50);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30);
		
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
		Delay(10);
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		Delay(30+50);
		
		Delay(150);
	}
	******/
	//If init success, then continue, LED always on
	LCD_Clear(White);
  LCD_DisplayStringLine(Line0, " Device linked ");
	Delay(10);
	/***********显示暂时不需要
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
	LCD_Clear(White);
  LCD_DisplayStringLine(Line0, " |---Stim Begin!---| ");
	Delay(10);

	for(chl = 1; chl < 9; chl++)
	{
		displayDigital((u16)*(stim_amp+chl-1), displayPara, 3); //the last number represent the length of the data
		LCD_DisplayStringLineOnX(chl*24, "Amp:    mA", 0);
		LCD_DisplayStringLineOnX(chl*24, displayPara, 5);
		
		displayDigital(*(stim_pulse+chl-1), displayPara, 3);
		LCD_DisplayStringLineOnX(chl*24, "PW:    us", 11);
		LCD_DisplayStringLineOnX(chl*24, displayPara, 15);	
	}
	******************/
		user_button=1;
		  //user_button=0; //test
		mode_meg=1;
		LCD_DisplayStringLine(Line0, " Please push button ");
		LCD_DisplayStringLine(Line2, "Key: PulseWidth Mode");
		LCD_DisplayStringLine(Line3, "Tamper: Current Mode");
	while((user_button==1)&&(mode_meg==1))  // RIGHT 1，1  test 0，1 
		  //while(1)
				{		   
					mode_meg=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8); //the key button:PulseWidth Mode
					user_button=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);  //the tamper button:Current Mode
				//	user_button = 0;
			  }
	if(user_button==0)
	{
		LCD_Clear(White);
		LCD_DisplayStringLine(Line0, " |---Current Mode---| ");
		amp_flag = 1;
	}
	else
  {
		LCD_Clear(White);
		LCD_DisplayStringLine(Line0, " |--Pulse Width Mode--| ");
		pulse_flag = 1;
	}	

	//LCD_Clear(White); //test
  while (1)
  {
		//Begin to collect signal and process stimuli parameters
	/*			if ((stim_amp[0]>0)||(stim_amp[1]>0)||(stim_amp[2]>0)||(stim_amp[3]>0)||(stim_amp[4]>0))
				{
				GPIO_ResetBits(GPIOA, trigger);
				Delay(1);
				GPIO_SetBits(GPIOA, trigger);
				}
    	
      Delay(9);
			if ((stim_amp[0]=0)&&(stim_amp[1]=0)&&(stim_amp[2]=0)&&(stim_amp[3]=0)&&(stim_amp[4]=0))
			{
				Delay(1);
			}
		
	*/	
					stim_stop();
       		for(chl = 0; chl<CHANNEL_NUM; chl++)
       		{
       			if (chl < 5)
						{
							read_val[chl] = read_single_average(chl);	
							sam_pres[chl] = stim_pres_cal(read_val[chl]);//reture voltage
						}else
						{
							read_val[chl] = read_single_average2(chl - 5);
							sam_pres[chl] = stim_pres_cal(read_val[chl]);//reture voltage							
						}       			
						//sprintf((char*)displayBuf,"%d",sam_pres[0]);
						//LCD_DisplayStringLineOnX(Line4,displayBuf,1);
						//sprintf((char*)displayBuf,"%d",sam_pres[chl]);
						//LCD_DisplayStringLineOnX(Line5,displayBuf,1);
       			if(amp_flag && !pulse_flag)
       			{
							stim_amp[chl] = stim_amp_gen(sam_pres[chl]);
       				stim_pulse[chl] =110;
       			}
       			else
       			{
       				stim_pulse[chl] = stim_pul_gen(sam_pres[chl]);
       				stim_amp[chl] = 6;
       			}
       		}
				 
    	   while (receiveDataFromCom1.DSPDSUreceivedFlag != 1 && receiveDataFromCom2.DSPDSUreceivedFlag != 1 && receiveDataFromCom3.DSPDSUreceivedFlag != 1 && receiveDataFromCom4.DSPDSUreceivedFlag != 1 && receiveDataFromCom5.DSPDSUreceivedFlag != 1)
				 {
						stim_send_parameter(stim_amp, stim_pulse,1);
					  Delay(5);
				 }
				 LCD_DisplayStringLine(Line3, "Send successfully");		
				 receiveDataFromCom1.DSPDSUreceivedFlag = 0;	
				 receiveDataFromCom2.DSPDSUreceivedFlag = 0;
				 receiveDataFromCom3.DSPDSUreceivedFlag = 0;		
				 receiveDataFromCom4.DSPDSUreceivedFlag = 0;		
				 receiveDataFromCom5.DSPDSUreceivedFlag = 0;		
				 
				 stim_start();
			// Stop stim, get ready to update stimuli parameters.
			//excute the stimulation

    		//stim_send_parameter(stim_amp, stim_pulse,0);
    		//stim_start();			
			Delay(10);
			//stim_stop();
			}                //M1

			
/***can not understand this mode 
		if  (mode_meg==0)
		{
		   mode_meg=1;
		   while   (mode_meg==1)
		  {LCD_DisplayStringLine(Line0, " M2: MEG mode on ...  ");
		  for(chl = 0; chl<CHANNEL_NUM; chl++)
       		{
       			read_val[chl] = read_single_average(chl);				
       			sam_pres[chl] = stim_pres_cal(read_val[chl]);

       			if(amp_flag && !pulse_flag)
       			{
       				stim_amp[chl] = stim_amp_gen(sam_pres[chl]);
       				stim_pulse[chl] =150;
       			}
       			else
       			{
       				stim_pulse[chl] = stim_pul_gen(sam_pres[chl]);
       				stim_amp[chl] = 6;
       			}
       		}
		   stim_send_parameter(stim_amp, stim_pulse,1);
    	   stim_start();
		 if ((stim_amp[0]>0)||(stim_amp[1]>0)||(stim_amp[2]>0)||(stim_amp[3]>0)||(stim_amp[4]>0))
				{
				GPIO_ResetBits(GPIOA, trigger);
				Delay(1);
				GPIO_SetBits(GPIOA, trigger);
				}
    	
           Delay(9);
			if ((stim_amp[0]=0)&&(stim_amp[1]=0)&&(stim_amp[2]=0)&&(stim_amp[3]=0)&&(stim_amp[4]=0))
			{
				Delay(1);
			}
			stim_stop();
			Delay(25);
			AD_Delay(2100); 
			mode_meg=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
			if(	  mode_meg==0)
			{
			  LCD_DisplayStringLine(Line0, " MX: wait 3 seconds ...");
			  Delay(300);
			}
		}
		}		     //M2					   
   ****///end the understand 
  }
}
}
/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		/* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
		
		/* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);


    

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
    

	
  /* GPIOA and GPIO_LED clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_AFIO| RCC_APB2Periph_GPIOG| RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//multichannel
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
  /* CAN Periph clock enable */
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure1;
	NVIC_InitTypeDef  NVIC_InitStructure3;
	NVIC_InitTypeDef  NVIC_InitStructure4;
	NVIC_InitTypeDef  NVIC_InitStructure5;
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//multichannal
	/* Enable USART1 interrupt IRQ channel */
	NVIC_InitStructure1.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure1);	
	/* Enable USART3 interrupt IRQ channel */
	NVIC_InitStructure3.NVIC_IRQChannel = USART3_IRQChannel;
	NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure3);	
	/* Enable UART4 interrupt IRQ channel */
	NVIC_InitStructure4.NVIC_IRQChannel = UART4_IRQChannel;
	NVIC_InitStructure4.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure4.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure4.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure4);	
	/* Enable UART5 interrupt IRQ channel */
	NVIC_InitStructure5.NVIC_IRQChannel = UART5_IRQChannel;
	NVIC_InitStructure5.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure5.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure5.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure5);	
	
	
	/* Enable CAN RX0 interrupt IRQ channel 
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);*/


}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_PinRemapConfig(GPIO_Remap1_CAN, ENABLE);// remap
	
  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
//ADD  LXD
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART3 Tx (PB.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure UART4 Tx (PC.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
    
  /* Configure UART4 Rx (PC.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/* Configure UART5 Tx (PC.12) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
    
  /* Configure UART5 Rx (PD.2) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
// END ADD LXD
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure INSTRUSTION LED (PF.10, MCU OUTPUT)*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	/* --------------------------------------------- */
	/* Configure the ADS1256 module, set the IO port */
	/* --------------------------------------------- */
	/* Configure ADS1256 CLK (MCU OUTPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_CLK;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
	
	/* Configure ADS1256 IN (MCU OUTPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_IN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
	
	/* Configure ADS1256 OUT (MCU INPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_OUT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
	
	/* Configure ADS1256 DRDY (MCU INPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_DRDY;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
    
  /* Configure ADS1256 CS (MCU OUTPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
	
	//  Configure trigger line
	GPIO_InitStructure.GPIO_Pin = trigger;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/* Configure user's button*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/* Configure tamper button*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
// the second AD module
	/* Configure ADS1256 IN2 (MCU OUTPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_IN2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
	
	/* Configure ADS1256 OUT2 (MCU INPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_OUT2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
	
	/* Configure ADS1256 DRDY2 (MCU INPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_DRDY2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
    
  /* Configure ADS1256 CS2 (MCU OUTPUT)*/
  GPIO_InitStructure.GPIO_Pin = ADS1256_CS2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_AD_BANK, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : SysTick_Config
* Description    : Configure a SysTick Base time to 10 ms.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
 void SysTick_Config(void)
{
  /* Configure HCLK clock as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
 
  /* SysTick interrupt each 100 Hz with HCLK equal to 72MHz */
  SysTick_SetReload(720000);

  /* Enable the SysTick Interrupt */
  SysTick_ITConfig(ENABLE);
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length (time base 10 ms).
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(u32 nCount)
{
  TimingDelay = nCount;

  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
  
  while(TimingDelay != 0)
  {
  }

  /* Disable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Disable);

  /* Clear the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Clear);
}

/*******************************************************************************
* Function Name  : Decrement_TimingDelay
* Description    : Decrements the TimingDelay variable.
* Input          : None
* Output         : TimingDelay
* Return         : None
*******************************************************************************/
void Decrement_TimingDelay(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}


void displayDigital(u16 num,u8 *displayString,u8 displaystringLength)
{
	
	u8 i;
	u16 temp = num;
	
	u16 number = 1;
	for (i = 0;i<  (displaystringLength - 1);i++)
	{
		number = number*10;
	}
	for (i = 0; i < displaystringLength; i++)
	{
		
		*(displayString + i) = (u8)(temp/number + 0x30);
		temp = temp%number;
		number = number/10;
	}
	*(displayString + displaystringLength + 1) = '\0';
}



	

/******************* *****END OF FILE****/
