/*
 * hyrel.c
 *
 *  Created on: Apr 28, 2022
 *      Author: hyrel
 *      this is the roundrobing scehdular
 *      to set the basic int interval search for
 *      HAL_SYSTICK_Config(SystemCoreClock
 *      it is in stm32h7xx_hal.c
 *      in the current version we set the value to 8000
 */
#include "main.h"
//#include "ADC/adc.h"
#include "taskmanager.h"
//#include "Execution/cmdprocessor.h"
//#include "Communication/parser.h"
//#include "Communication/serial.h"
//#include "CAN/can.h"
#include "Display/display.h"
#include "GPIO/gpio.h"
//#include "Timer/timer.h"
//#include "Execution/tools.h"
//#include "SETTINGS/settings.h"
//#include "DAC/dac.h"
//#include "PNP/pnp.h"
//#include "Communication/secsserial.h"
uint32_t PWMSubCounter=0;
uint32_t Seconds = 0;               // needed for heartbeat (number of seconds since boot)
uint16_t SliceCnt = 0;              // current slice being processed
uint16_t TaskTime[32]={0};			// last execution time
uint16_t MaxTaskTime[32]={0};       // Maximum execution time
uint16_t SliceOffset=0;
float ADCValues[ADC_CHANNELS] = {0};
uint8_t BarStatus[4] = {0};
uint16_t BarDutty[4] = {0};
float BarFloat[8] = {0};

uint16_t Key1Debounce=1;
uint16_t Key2Debounce=1;

volatile FaultVariableInfo faultVariableInfo __attribute__ ((section (".no_init"))) = {0};
ExtendedCanTaskInfo extendedCanTaskInfo = {0};

const PFUNC F1000HZ[NUM_1000HZ] =
{
	Spare,    // keep as last call in this array
	Spare, //ParseIncomingLineIntoGCodeArgs,//canProcessTxQueueNoReturn,
	Spare, //CheckCanRxMessages,
	Spare, //ProcessCanRxMessage,
	Spare, //ProcessCanTxMessage,
	Spare, //GenerateSineWave,
	Spare, //CheckForUart3TxRx,
	Spare, //CheckForUart6TxRx,
};

const PFUNC F100HZ[NUM_100HZ] =
{
	Spare,//loop_100Hz_simple_work, // keep as last call in this array
	Spare, //CanBusExtendedMessageProcessor,
	Spare, //Sequencer,
	Spare, //Update_Home_Status,
	Spare, //PWMSweeper,
	Spare, //Sequencer,
	Spare, //ProcessRawADC_Data,
	Spare, //USBTxProcessor,
};

const PFUNC F10HZ[NUM_10HZ] =
{
	Spare,
	CheckUserSwitches,
	Spare,
	Spare, //PnP_SetValves,
	Spare, //LatchPnPData,
	Spare, //ParseIncommingLineToSecsString,
	Spare, //SecsTimers,
	Spare,
};

const PFUNC F1HZ[NUM_1HZ] =
{
	Spare,
	Spare,
	Spare,
	BlinkHeartBeat,
	Spare,//CheckedRegisteredToolStatus,
	Spare,
	Spare,
	Spare,
};
/*
 * to make the slice scedular more effecient, we are going to use a binary counter, not base 10
 *
 */
//void TaskManager()
void func_SystickCallback()
{

	TIM6->CNT = 0;//reset the slice timer
	SliceCnt++;
	SliceOffset=SliceCnt&0x0007;  //precalculate the slice index into the jump table
	if(SliceOffset)
	{
		F1000HZ[SliceOffset]();//run the task
		if(TIM6->CNT > TaskTime[SliceOffset])
		{
			TaskTime[SliceOffset]=TIM6->CNT;
		}
		//Y_STEP_CLR;
		return;//toggle pin so we can see on Oscillosclope and exit
	}
	if(SliceCnt&0x0038)
	{
		SliceOffset=(SliceCnt>>3) & 0x0007;
		F100HZ[SliceOffset]();
		SliceOffset+=8;
		if(TIM6->CNT > TaskTime[SliceOffset]) TaskTime[SliceOffset]=TIM6->CNT;
		return;//toggle pin so we can see on Oscillosclope and exit
	}

	if(SliceCnt&0x01C0)
	{
		SliceOffset=(SliceCnt>>6)  & 0x0007;
		F10HZ[SliceOffset]();
		SliceOffset+=16;
		if(TIM6->CNT > TaskTime[SliceOffset]) TaskTime[SliceOffset]=TIM6->CNT;
		return;//toggle pin so we can see on Oscillosclope and exit
	}

	SliceOffset=(SliceCnt>>9)  & 0x0007;
	F1HZ[SliceOffset]();
	SliceOffset+=24;
	if(TIM6->CNT > TaskTime[SliceOffset])
	{
		TaskTime[SliceOffset]=TIM6->CNT;
	}
	return;//toggle pin so we can see on Oscillosclope and exit

}

void Spare (void)
{
	// placeholder call for empty slice
}
void BlinkHeartBeat(void)
{
	HeartBeat++;
	if(HeartBeat&1) HEARTBEAT_SET;
	else HEARTBEAT_CLR;
	
	//Timer1Count=TIM1->RCR;
	//Timer15Count=TIM15->CNT;
	//Timer2Count=TIM2->CNT;
	//Timer6Count=TIM6->CNT;
}
void PWMSweeper()
{
	if (++ PWMSubCounter > 255)
	{
		PWMSubCounter=1;
	}
	TIM16->CCR1=PWMSubCounter;//PWMSubCounter;
	TIM17->CCR1=PWMSubCounter;//101-PWMSubCounter;
}
void ClearSliceTimes(void)
{
	memset(TaskTime, 0, sizeof(TaskTime) * sizeof(uint32_t));
	memset(MaxTaskTime, 0, sizeof(MaxTaskTime) * sizeof(uint16_t));
}

void CanHeartBeat(void)
{
	//CanAddTxBuffer(CAN_HEAD_12, CAN_READ, CAN_MSG_PING, 0, 0, 0, 0);
}

void UpdateLeds(void)
{
//	if(CanRxLedCountDown) { CanRxLedCountDown --;  LED_CAN_RX_ON;	}
//	else LED_CAN_RX_OFF;
//	if(CanTxLedCountDown) { CanTxLedCountDown --;  LED_CAN_TX_ON;	}
//	else LED_CAN_TX_OFF;
}
void CheckUserSwitches(void)
{//monitor switches and change display index if pressed
	USERKEY1_READ;//read the status
	USERKEY2_READ;//read the status

	if(!UserKey1_Status)
	{//switch is pressed and input is low
		if(Key1Debounce)return;
		Key1Debounce=1;//turn on debounce
		ShowNextDisplay();
	}
	Key1Debounce=0;//turn off debounce

	if(!UserKey2_Status)
	{//switch is pressed and input is low
		if(Key2Debounce)return;
		Key2Debounce=1;//turn on debounce
		ShowPreviousDisplay();
	}
	Key2Debounce=0;//turn off debounce
}

void CanBusExtendedMessageProcessor(void)
{
//	switch(extendedCanTaskInfo.TaskType) {
//	case TASK_CAN_READ_SOAPSTRING: break;
//	case TASK_CAN_WRITE_SOAPSTRING:
//		if(extendedCanTaskInfo.CanTaskCounter * 6 >= 0x400) {
//			extendedCanTaskInfo.TaskType = TASK_IDLE;
//			break;
//		}
//		//in this case , TaskCoutUp means soap string's offset address.
//		//2bytes are address
//		CanMessageBuffer[0] = extendedCanTaskInfo.CanTaskCounter & 0xFF;
//		CanMessageBuffer[1] = (extendedCanTaskInfo.CanTaskCounter & 0xFF00) >> 8;
//		//6bytes are data
//		uint8_t size = 0;
//		for(uint8_t i = 0; i < 6; i ++){
//			CanMessageBuffer[i+2] = RemoteSoapString[extendedCanTaskInfo.CanTaskCounter * 6 + i];
//			if(CanMessageBuffer[i+2] == 0) {
//				size ++;
//				break;
//			}
//			size ++;
//		}
//
//		CanAddTxBuffer(extendedCanTaskInfo.TargetDevice, CAN_WRITE, CAN_MSG_WRITE_SOAPSTRING, 0, 0, CanMessageBuffer, size + 2);
//		if(size < 6) {
//			extendedCanTaskInfo.TaskType = TASK_IDLE;
//		}
//		break;
//	}
//	extendedCanTaskInfo.CanTaskCounter ++;
//	if(extendedCanTaskInfo.CanTaskCounter >= TASK_MAXCOUNT) extendedCanTaskInfo.CanTaskCounter = 0;
}

void InitFaultVariable() {
	//memset(&faultVariableInfo, 0, sizeof(FaultVariableInfo));
	faultVariableInfo.ComRxBufferPoint = 0;
	faultVariableInfo.ComTxBufferPoint = 0;
	faultVariableInfo.GcodeLineCounter = 0;
	faultVariableInfo.LastCharsInBuf = 0;
	faultVariableInfo.LastMessageTail = 0;
	faultVariableInfo.LastRxHead = 0;
	faultVariableInfo.ParsedLineCounter = 0;
	faultVariableInfo.TaskSliceNumber = 0;
	faultVariableInfo.TaskTime = 0;
	faultVariableInfo.NumberOfFaults = 0;
	DisplayIndex = 0;
}

void StoreFaultVariable()
{
//	faultVariableInfo.ComRxBufferPoint = (uint32_t)&COMUSB.RxBuffer;
//	faultVariableInfo.ComTxBufferPoint = (uint32_t)&COMUSB.TxBuffer;
//	faultVariableInfo.GcodeLineCounter = gcodeLineNumber;
//	faultVariableInfo.LastMessageTail = LastMessageTail;
//	faultVariableInfo.LastRxHead = COMUSB.RxBuffer.Head;
//	faultVariableInfo.ParsedLineCounter = ParsedLineCounter;
//	faultVariableInfo.TaskTime = SliceCnt;
//	faultVariableInfo.TaskSliceNumber = 0;
//	faultVariableInfo.NumberOfFaults = faultVariableInfo.NumberOfFaults + 1;
//	faultVariableInfo.Reserved = 0xff;
//	bootMode = 0x0f;
//	DisplayIndex = 6;
//	NVIC_SystemReset();
}
