 //FES system data difine
/* Define to prevent recursive inclusion -------------------------------------*/



#ifndef __SYSTEMDATASTRUCTURE_H
#define __SYSTEMDATASTRUCTURE_H
#include "stm32f10x_lib.h"
#include "stm32f10x_type.h"
//system state define
typedef struct
{
  vu8 SysHarewareReady;
  vu8 SysParaReady;
  vu8 SysOnReady;
  vu8 SysIsWorking;
  vu8 SystemWarning;
}SystemOperationStateType;



//DSSU state
typedef struct
{
	vu8 DSSUConnectingFlag;
	vu8 DSSUNumber;
	vu8 DSSUConState;
}DSSUStateType;


//PC state
//typedef struct
//{
//	vu8 PCConnectingFlag;
//}PCConnectingStateType;


//code 
//typedef struct
//{
//	vu8 AskForDSSUState;
//	vu8 StopOrder;
//	vu8 BeginOrder;
//	vu8 ReBeginOrder;
//}SystemInstructionType;


//parametermanagement
//typedef struct
//{
//	vu8 *StartOpoint;
//	vu8 *EndOpoint;
//	vu8 DataBuf[1024];
//}DataQue;


//parametermanagement
typedef struct
{
	vu8 ParameterUpdataFlag;
	vu8 ParameterValidFlag;
	vu8 ParameterErr;
}ParameterStateType;


typedef struct
{
  vu16 StimuliFreq;
  vu16 StimuliAmp;
  vu16 StimuliDelay;
  vu16 stimuliWidth;
  vu8 *stimulationParaBuffer;
  vu16 dataLen;
}StimuliParameterTypeDef;

//parameter data structure
typedef struct
{
	vu8 ChannelNum;
	vu8 ChannelValid;
	vu8 ChannelParameterAdress;
	StimuliParameterTypeDef StimulationParameter;
}EachChannelParaType;
 
		 
#endif /* __SYSTEMDATASTRUCTURE_H */



