#include "ads1256.h"


//u8 data_fro_reg[11];
u8 read_val;
u8 read_val2;
u8 drdy_value;
u8 drdy_value2;
//-----------------------------------------------------------------------------
// \brief   time delay function
//
// \param   u8 time: time length to be delayed (time base is 1 us)
// System clock is 72Mhz, single period is (1000,000/12M) = 1/72 us
//
// \return  none
//-----------------------------------------------------------------------------

void AD_Delay(u8 nTime)
{
	u32 i = 1;
	i = nTime * 12;
	while(i > 0)
		i--;
}

//在SCLK的下降沿，系统通过DIN向ADSl256发送数据；
//而在SCLK的上升沿，系统则通过DOUT从ADSl256读取数
//-----------------------------------------------------------------------------
// \brief   write the cmd to ads1256
//
// \param   u8 data - data cmd to be written
//
// \return  none
//-----------------------------------------------------------------------------
 void ADS1256_Write_Byte(u8 data)
{
    u8 i=8;
    GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
    AD_Delay(1);                                       //min=200ns
    while(i--)
    {
        if(data & 0X80)
            GPIO_SetBits(GPIO_AD_BANK, ADS1256_IN);
        else
            GPIO_ResetBits(GPIO_AD_BANK, ADS1256_IN);
        AD_Delay(2);
        GPIO_SetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        data <<= 1;
    }
}


//the second AD module
 void ADS1256_Write_Byte2(u8 data)
{
    u8 i=8;
    GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
    AD_Delay(1);                                       //min=200ns
    while(i--)
    {
        if(data & 0X80)
            GPIO_SetBits(GPIO_AD_BANK, ADS1256_IN2);
        else
            GPIO_ResetBits(GPIO_AD_BANK, ADS1256_IN2);
        AD_Delay(2);
        GPIO_SetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        data <<= 1;
    }
}


//-----------------------------------------------------------------------------
// \brief   read byte from ads1256
//
// \param   none
//
// \return  u8: byte data read from ads1256
//-----------------------------------------------------------------------------
u8 ADS1256_Read_Byte(void)
{  
    u8 i=8,rtn_data=0;
    GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
    AD_Delay(2);                                       //min=200ns
    while(i--)
    {
        rtn_data <<=1;
        GPIO_SetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        read_val = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_OUT);
        rtn_data |= read_val;
    }
    return rtn_data;
}
//the second AD module
u8 ADS1256_Read_Byte2(void)
{  
    u8 i=8,rtn_data=0;
    GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
    AD_Delay(2);                                       //min=200ns
    while(i--)
    {
        rtn_data <<=1;
        GPIO_SetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CLK);
        AD_Delay(2);
        read_val2 = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_OUT2);
        rtn_data |= read_val2;
    }
    return rtn_data;
}

 /*
void  ADS1256_Read_Reg(u8 reg_name, u8 number)
{
    u8 i;
    ADS1256_Write_Byte(CMD_RREG|reg_name);
    ADS1256_Write_Byte(0x00|number);
    for(i=0;i<number+1;i++)
     data_fro_reg[i]=ADS1256_Read_Byte();
}
*/


u8  ADS1256_Read_one_Reg(u8 reg_name)
{
    u8 dat;
    do
    {
        drdy_value = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_DRDY);
    }
    while(drdy_value);
    ADS1256_Write_Byte(CMD_RREG|reg_name);
    ADS1256_Write_Byte(0x00);
    AD_Delay(10);                                 //min=50*(1/fCLKIN)=50*(1/7.68MHZ)=6500ns;max=whatever
//  while(ADS1256_DRDY);
    dat=ADS1256_Read_Byte();
    return dat;
}
 

//-----------------------------------------------------------------------------
// \brief   write the cmd to ads1256 register
//
// \param   u8 reg_name - name of register
//
// \param   u8 reg_data - data cmd to be written into the register
//
// \return  none
//-----------------------------------------------------------------------------
void  ADS1256_Write_Reg(u8 reg_name, u8 reg_data)
{
    do
    {
        drdy_value = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_DRDY);
    }
    while(drdy_value);

    ADS1256_Write_Byte(CMD_WREG|reg_name);
    ADS1256_Write_Byte(0x00);
    ADS1256_Write_Byte(reg_data);
}


//the second AD module
void  ADS1256_Write_Reg2(u8 reg_name, u8 reg_data)
{
    do
    {
        drdy_value2 = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_DRDY2);
    }
    while(drdy_value2);

    ADS1256_Write_Byte2(CMD_WREG|reg_name);
    ADS1256_Write_Byte2(0x00);
    ADS1256_Write_Byte2(reg_data);
}

//-----------------------------------------------------------------------------
// \brief   initialize the ads1256 module
//
// \param   none
//
// \return  none
//-----------------------------------------------------------------------------
void initads1256(void)
{
    //SetADS1256_SYNC;
//  GPIO_SetBits(GPIO_AD_BANK, ADS1256_CLK, OUTPUT_LOW);
    GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS);
	  GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS2);
    AD_Delay(100);
    GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CS);
	  GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CS2);
    //while(!ADS1256_DRDY);
    ADS1256_Write_Byte(CMD_RESET);
	  ADS1256_Write_Byte2(CMD_RESET);
    AD_Delay(10);
    //ADS1256_Write_Byte(CMD_WREG);

    ADS1256_Write_Reg(REG_STATUS,CMD_SYSGCAL);                  //STATUS REGISTER:Auto-Calibration Enabled,Analog Input Buffer Disabled
    ADS1256_Write_Reg(REG_MUX,POSITIVE_AIN0+ NEGTIVE_AINCOM);   //MUX:AIN0, AIN0 is Positive,single-ended measurements
    ADS1256_Write_Reg(REG_ADCON,CLKOUT_OFF+DETECT_OFF+PGA_1);   //ADCON=00h, input range = 0~5V
    ADS1256_Write_Reg(REG_DRATE,DATARATE_15K);                  //data rate 15k SPS
    ADS1256_Write_Reg(REG_IO,0x00);                             //GPIO output

    ADS1256_Write_Reg2(REG_STATUS,CMD_SYSGCAL);                  //STATUS REGISTER:Auto-Calibration Enabled,Analog Input Buffer Disabled
    ADS1256_Write_Reg2(REG_MUX,POSITIVE_AIN0+ NEGTIVE_AINCOM);   //MUX:AIN0, AIN0 is Positive,single-ended measurements
    ADS1256_Write_Reg2(REG_ADCON,CLKOUT_OFF+DETECT_OFF+PGA_1);   //ADCON=00h, input range = 0~5V
    ADS1256_Write_Reg2(REG_DRATE,DATARATE_15K);                  //data rate 15k SPS
    ADS1256_Write_Reg2(REG_IO,0x00);                             //GPIO output
	
    do
    {
        drdy_value = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_DRDY);
    }
    while(drdy_value);

    do
    {
        drdy_value2 = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_DRDY2);
    }
    while(drdy_value2);
    ADS1256_Write_Byte(CMD_SELFCAL);
		//while(!drdy_value);
    while(drdy_value);
		
    ADS1256_Write_Byte2(CMD_SELFCAL);
		//while(!drdy_value);
    while(drdy_value2);
    AD_Delay(2);
		
    GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS);
		GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS2);
}

//-----------------------------------------------------------------------------
// \brief   read 24-bit data from ads1256
//
// \param   none
//
// \return  u8: singal channel data read from ads1256
//-----------------------------------------------------------------------------
u32 read_single_chl(u8 channel)
{
    u32 result = 0;
    u8 result1, result2, result3;
    GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CS);
	
    channel <<=4;
	
    ADS1256_Write_Reg(REG_MUX,0x08|channel);
	
    do
    {
         drdy_value = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_DRDY);
    }
    while(drdy_value);                                                     //DRDY信号为低表示AD转换完成
    ADS1256_Write_Byte(CMD_RDATA);
    AD_Delay(10);                                                      //min=50*(1/fCLKIN)=50*(1/7.68MHZ)=6500ns; max=whatever

    result1 = ADS1256_Read_Byte();
    result2 = ADS1256_Read_Byte();
    result3 = ADS1256_Read_Byte();
    GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS);;
    //result=result1*65536+result2*256+result3;

    result = result1;
    result <<= 8;
    result |= result2;
    result <<= 8;
    result |= result3;

    return result;
}
//the second AD module
u32 read_single_chl2(u8 channel)
{
    u32 result = 0;
    u8 result1, result2, result3;
    GPIO_ResetBits(GPIO_AD_BANK, ADS1256_CS2);
	
    channel <<=4;
	
    ADS1256_Write_Reg2(REG_MUX,0x08|channel);
	
    do
    {
         drdy_value2 = GPIO_ReadInputDataBit(GPIO_AD_BANK, ADS1256_DRDY2);
    }
    while(drdy_value2);                                                     //DRDY信号为低表示AD转换完成
    ADS1256_Write_Byte2(CMD_RDATA);
    AD_Delay(10);                                                      //min=50*(1/fCLKIN)=50*(1/7.68MHZ)=6500ns; max=whatever

    result1 = ADS1256_Read_Byte2();
    result2 = ADS1256_Read_Byte2();
    result3 = ADS1256_Read_Byte2();
    GPIO_SetBits(GPIO_AD_BANK, ADS1256_CS2);;
    //result=result1*65536+result2*256+result3;

    result = result1;
    result <<= 8;
    result |= result2;
    result <<= 8;
    result |= result3;

    return result;
}


u32 read_single_average(u8 channel)
{
	u32 read_data = 0;
	u8 read_num = 300; //test 30  right 3
	u8 cnt;
	read_data = read_single_chl(channel);
	read_data = 0;

	for(cnt=0; cnt<read_num; cnt++)
	{
		read_data += read_single_chl(channel);
	}
	read_data = read_data/(read_num+1);

	return read_data;
}

u32 read_single_average2(u8 channel)
{
	u32 read_data = 0;
	u8 read_num = 300; //test 30  right 3
	u8 cnt;
	read_data = read_single_chl2(channel);
	read_data = 0;

	for(cnt=0; cnt<read_num; cnt++)
	{
		read_data += read_single_chl2(channel);
	}
	read_data = read_data/(read_num+1);

	return read_data;
}

u32 read_all_chl(u32* data_addr)
{
	u8 cnt_chl;

	for(cnt_chl=0; cnt_chl<8; cnt_chl++)
	{
		data_addr[cnt_chl] = read_single_average(cnt_chl);
	}

	return 0;
}

