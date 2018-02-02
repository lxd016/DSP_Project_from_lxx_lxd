//-----------------------------------------------------------------------------
// \file    ads1256.h
// \brief   ADS1256 module Register & Defines.
//-----------------------------------------------------------------------------

#ifndef ADS1256_H
#define ADS1256_H

#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"

//-----------------------------------------------------------------------------
// Register Defines
//-----------------------------------------------------------------------------
 /*Registers' Address*/
#define REG_STATUS  0
#define REG_MUX     1
#define REG_ADCON   2
#define REG_DRATE   3
#define REG_IO      4
#define REG_OFC0    5
#define REG_OFC1    6
#define REG_OPC2    7
#define REG_FSC0    8
#define REG_FSC1    9
#define REG_FSC2    10

/*Operation Command*/
//#define CMD_WAKEUP     0x00
#define CMD_RDATA      0x01
#define CMD_RDATAC     0x03
#define CMD_SDATAC     0x0F
#define CMD_RREG       0x10
#define CMD_WREG       0x50
#define CMD_SELFCAL    0xf0
#define CMD_SELFOCAL   0xf1
#define CMD_SELFGCAL   0xf2
#define CMD_SYSOCAL    0xf3
#define CMD_SYSGCAL    0xf4
#define CMD_SYNC       0xfc
#define CMD_STANDBY    0xfd
#define CMD_RESET      0xfe
#define CMD_WAKEUP     0xFF

#define PGA_1            0x00
#define PGA_2            0x01
#define PGA_4            0x02
#define PGA_8            0x03
#define PGA_16           0x04
#define PGA_32           0x05
#define PGA_64           0x06
//#define PGA_64           0x07


#define POSITIVE_AIN0            (0X00<<4)
#define POSITIVE_AIN1            (0X01<<4)
#define POSITIVE_AIN2            (0X02<<4)
#define POSITIVE_AIN3            (0X03<<4)
#define POSITIVE_AIN4            (0X04<<4)
#define POSITIVE_AIN5            (0X05<<4)
#define POSITIVE_AIN6            (0X06<<4)
#define POSITIVE_AIN7            (0X07<<4)
#define POSITIVE_AINCOM          (0X08<<4)

#define NEGTIVE_AIN0              0X00
#define NEGTIVE_AIN1              0X01
#define NEGTIVE_AIN2              0X02
#define NEGTIVE_AIN3              0X03
#define NEGTIVE_AIN4              0X04
#define NEGTIVE_AIN5              0X05
#define NEGTIVE_AIN6              0X06
#define NEGTIVE_AIN7              0X07
#define NEGTIVE_AINCOM            0X08

/*For fclkin=7.68MHz, data rate*/
#define DATARATE_30K              0xf0
#define DATARATE_15K              0xe0
#define DATARATE_7_5K             0xd0
#define DATARATE_3_7_5K           0xc0
#define DATARATE_2K               0xb0

/*STATUS REGISTER*/
#define MSB_FRIST                (0x00<<3)
#define LSB_FRIST                (0x01<<3)
#define ACAL_OFF                 (0x00<<2)
#define ACAL_ON                  (0x01<<2)
#define BUFEN_OFF                (0x00<<1)
#define BUFEN_ON                 (0x01<<1)

/*ADCON REGISTER*/
#define CLKOUT_OFF               (0x00<<5)
#define CLKOUT_CLKIN             (0x01<<5)
#define DETECT_OFF               (0x00<<3)
#define DETECT_ON_2UA            (0x02<<3)

/*GPIO REGISTER*/
/*
#define DIR3_OUT                 (~(0x1<<7))
#define DIR3_IN                  (0x1<<7)
#define DIR2_OUT                 (~(0x1<<6))
#define DIR2_IN                  (0x1<<6)
#define DIR1_OUT                 (~(0x1<<5))
#define DIR1_IN                  (0x1<<5)
*/

//-----------------------------------------------------------------------------
// Public Defines and Macros
//-----------------------------------------------------------------------------
#define GPIO_AD_BANK   (GPIOF)
#define ADS1256_CLK    (GPIO_Pin_1)
#define ADS1256_IN     (GPIO_Pin_2)
#define ADS1256_OUT    (GPIO_Pin_3)
#define ADS1256_DRDY   (GPIO_Pin_4)   // GPIO[5]->PIN11 读端口E的数据寄存器
#define ADS1256_CS     (GPIO_Pin_5)
#define ADS1256_RESET  (GPIO_Pin_6)
#define trigger        (GPIO_Pin_1)

//for the second AD module:the same clk reset and the different in and out and drdy and cs (12-15)
#define ADS1256_IN2     (GPIO_Pin_12)  //the second ads1256
#define ADS1256_OUT2    (GPIO_Pin_13)
#define ADS1256_DRDY2   (GPIO_Pin_14)   
#define ADS1256_CS2     (GPIO_Pin_15)
/*
 * for the second AD module, the pin mux will be like below
#define ADS1256_CLK    (GPIO_PIN4)
#define ADS1256_IN     (GPIO_PIN6)
#define ADS1256_OUT    (GPIO_PIN8)
#define ADS1256_DRDY   (GPIO_PIN10)   // GPIO[5]->PIN11 读端口E的数据寄存器
#define ADS1256_CS     (GPIO_PIN12)
#define ADS1256_RESET  (GPIO_PIN14)
 */

//-----------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------

extern void initads1256(void);

void ADS1256_Write_Byte(u8 data);
u8 ADS1256_Read_Byte(void);

void  ADS1256_Write_Reg(u8 reg_name, u8 reg_data);

void ADS1256_Write_Byte2(u8 data);
u8 ADS1256_Read_Byte2(void);

void  ADS1256_Write_Reg2(u8 reg_name, u8 reg_data);

extern u8 ADS1256_Read_one_Reg(u8 reg_name);

extern u32 read_single_chl(u8 channel);
extern u32 read_single_chl2(u8 channel);
extern u32 read_single_average(u8 channel);
extern u32 read_single_average2(u8 channel);
extern u32 read_all_chl(u32* data_addr);


#endif
