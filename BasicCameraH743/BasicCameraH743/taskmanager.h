#pragma once

typedef void (*PFUNC)(void);

#define NUM_1000HZ              8
#define NUM_100HZ               8      // must remain 10 otherwise loop timing will not be correct
#define NUM_10HZ                8      // must remain 10 otherwise loop timing will not be correct
#define NUM_1HZ                 8     // must remain 10 otherwise loop timing will not be correct
#define ADC_CHANNELS			3

//#define SYSTICKS_PER_SECOND     (NUM_1000HZ * NUM_100HZ * NUM_10HZ * NUM_1HZ)
#define TASK_MAXCOUNT	0xFFFF

typedef enum {
	HZ_1000     = 0,
	HZ_100      = 1,
	HZ_10       = 2,
	HZ_1        = 3
} indexType;

enum {
	TASK_IDLE = 0,
	TASK_CAN_READ_SOAPSTRING,
	TASK_CAN_WRITE_SOAPSTRING,
};

typedef struct {
	uint8_t TaskType;
	uint32_t CanTaskCounter;
	uint16_t TargetDevice;
}ExtendedCanTaskInfo;

typedef struct {
	uint32_t TaskTime;
	uint32_t TaskSliceNumber;
	uint32_t ComRxBufferPoint;
	uint32_t ComTxBufferPoint;

	uint16_t LastMessageTail;
	uint32_t LastCharsInBuf;
	uint16_t LastRxTail;
	uint16_t LastRxHead;
	uint32_t LastRxLineCount;

	uint16_t ParsedLineCounter;
	uint16_t GcodeLineCounter;
	uint16_t NumberOfFaults;
	uint16_t Reserved;
}FaultVariableInfo;

extern volatile FaultVariableInfo faultVariableInfo;

extern uint32_t bootMode;
extern uint32_t DisplayIndex;
extern uint32_t HeartBeat;
extern uint32_t Percent;
extern uint32_t DevicePosition;
extern uint32_t BootStateStep;
extern uint32_t WatchdogCounterMs;
extern uint32_t WatchdogMs;
extern uint32_t CanRxCount;
extern uint32_t CanTxCount;
extern uint32_t LastCanRxMsgId;
extern uint32_t LastCanTxMsgId;
extern uint16_t requestToPauseAtEndOfMove;
extern uint16_t requestToPauseAtEndOfLayer;
extern ForeTaskFlag_t ForegroundTaskFlag;

extern uint16_t TaskTime[32];			// last execution time
extern uint16_t MaxTaskTime[32];       // Maximum execution time
extern float ADCValues[ADC_CHANNELS];			//array of ADC for 8 channels.
extern uint8_t BarStatus[];
extern uint16_t BarDutty[];
extern float BarFloat[];

extern ForeTaskFlag_t ForegroundTaskFlag;

extern ExtendedCanTaskInfo extendedCanTaskInfo;

extern uint32_t PWMSubCounter;
void func_SystickCallback(void);
void Spare (void);
void Execute1000HzTask(void);
void Execute100HzTask(void);
void Execute10HzTask(void);
void Execute1HzTask(void);
void BlinkHeartBeat(void);
void PWMSweeper(void);
void ClearSliceTimes(void);
void CheckUserSwitches(void);
void UpdateLeds(void);
void CanHeartBeat(void);
void CanBusExtendedMessageProcessor(void);
void InitFaultVariable();
void StoreFaultVariable();