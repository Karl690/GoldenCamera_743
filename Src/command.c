#include <stdbool.h>
#include "constant.h"
#include "command.h"
#include "systeminfo.h"
void ReceivedVCPMessage(uint8_t* buf, uint16_t len) {
	if(len == 1) {
		extern uint8_t IsDrawingAxis;
		extern uint8_t IsLiveStream;
		switch(buf[0]) {
		case PING_CHAR:
			SendRevisionString("PingReply");
			break;
		case ADC_SAMPLERATE_1KHZ:
		case ADC_SAMPLERATE_10KHZ:
		case ADC_SAMPLERATE_100KHZ:
		case ADC_SAMPLERATE_1MHZ:
		case ADC_SAMPLERATE_10MHZ:
			ChangeADCSampleRate(buf[0]);
			break;
		}

	}else {
		if(ParseCommand(buf, len)) {

		}else {

		}

		//CDC_Transmit_FS(buf, len);
	}
	CDC_Transmit_FS(ASCII_ACK, 1);
}

void PingReply (void){
	sendRevisionString("PingReply");
}

void SendRevisionString(char *reason){
	extern SYSTEMINFO SystemInfo;
	uint8_t trans_buffer[100] = {0};
	//trans_buffer[0] = PING_CHAR;
	sprintf(trans_buffer, ">Hy: %s :GoldenCamera sw %d.%03d", reason, SystemInfo.softwareMajorVersion, SystemInfo.softwareMinorVersion);
	CDC_Transmit_FS(trans_buffer, strlen(trans_buffer));
}

bool ParseCommand(uint8_t* buf, uint8_t len) {

	return true;
}


void ChangeADCSampleRate(uint8_t Code)
{
	extern ADC_HandleTypeDef hadc1;
	extern TIM_HandleTypeDef htim6;
	extern uint8_t ADC1_Buf[ADC_SAMPLE_SIZE];
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_TIM_Base_Stop(&htim6);
	uint32_t prescaler = htim6.Init.Prescaler;
	uint32_t period = htim6.Init.Period;
	switch(Code) {
	case ADC_SAMPLERATE_1KHZ:
		prescaler = 10000;
		period = 10;
		break;
	case ADC_SAMPLERATE_10KHZ:
		prescaler = 1000;
		period = 10;
		break;
	case ADC_SAMPLERATE_100KHZ:
		prescaler = 100;
		period = 10;
		break;
	case ADC_SAMPLERATE_1MHZ:
		prescaler = 100;
		period = 1;
		break;
	case ADC_SAMPLERATE_10MHZ:
		prescaler = 10;
		period = 1;
		break;
	}

	htim6.Init.Prescaler = prescaler;
	htim6.Init.Period = period;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
	    Error_Handler();
	}

	HAL_ADC_Start_DMA(&hadc1, ADC1_Buf, ADC_SAMPLE_SIZE);
	HAL_TIM_Base_Start(&htim6);
}
