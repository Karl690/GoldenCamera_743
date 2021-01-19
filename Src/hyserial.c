#include <hyserial.h>
#include <stdbool.h>
#include "constant.h"
#include "systeminfo.h"
#include <string.h>

#define HYCOMMAND_NUM  1
enum {M777, ADC, };
char* hycommand[HYCOMMAND_NUM] = {"M777", "ADC"};
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

bool ParseCommand(char* buf, uint8_t len)
{
	char* command = NULL;
	uint8_t CMD_ID = -1;
	for(int i = 0; i < HYCOMMAND_NUM; i ++) {
		if(strstr(buf, hycommand[i]) == buf) {
			CMD_ID = i;
			break;
		}
	}
	if(CMD_ID == -1) return false;

	switch(CMD_ID) {
	case M777:
		ParesM777Commad(buf, len);
		break;
	case ADC:
		break;

	}
	return true;
}

//M777 F1, F10, F100, F1K,...
bool ParesM777Commad(char* buf, uint8_t len)
{
	if(len < 6) return false;
	char* param = buf + 5; //"M777 F"

	len -= 5;
	param[len] = '\0';
	extern uint8_t IsRequestSendAdcData;
	char sendbuf[100] = {0};
	if(strcmp(param, "Stop") == 0) {
		ADC_Stop();
	}else if(strcmp(param, "Start") == 0) {
		ADC_Start();
	}else if(strcmp(param, "Status") == 0) {
		SendAdcStatus();
	}else if(strcmp(param, "Connect") == 0) {
		SendAdcStatus();
	}else if(strcmp(param, "RequestSignal") == 0) {
		IsRequestSendAdcData = true;
		SendAdcStatus();
	}else if(strcmp(param, "NoRequestSignal") == 0) {
		IsRequestSendAdcData = false;
		SendAdcStatus();
	}else if(strcmp(param, "F1") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_1HZ);
	}else if(strcmp(param, "F10") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_10HZ);
	}else if(strcmp(param, "F100") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_100HZ);
	}else if(strcmp(param, "F1K") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_1KHZ);
	}else if(strcmp(param, "F1K") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_10KHZ);
	}else if(strcmp(param, "F10K") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_10KHZ);
	}else if(strcmp(param, "F100K") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_100KHZ);
	}else if(strcmp(param, "F1M") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_1MHZ);
	}else if(strcmp(param, "F10M") == 0) {
		ChangeADCSampleRate(ADC_SAMPLERATE_10MHZ);
	}
	return true;
}
bool GetADCRequestSignalStatus() {

	extern uint8_t IsRequestSendAdcData;
	return IsRequestSendAdcData;
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
	case ADC_SAMPLERATE_1HZ:
		break;
	case ADC_SAMPLERATE_10HZ:
		break;
	case ADC_SAMPLERATE_100HZ:
		break;
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

	SendAdcStatus();

	HAL_ADC_Start_DMA(&hadc1, &ADC1_Buf[3], ADC_SAMPLE_SIZE);
	HAL_TIM_Base_Start(&htim6);
}
void ADC_Start() {
	extern ADC_HandleTypeDef hadc1;
	extern TIM_HandleTypeDef htim6;
	extern uint8_t ADC1_Buf[ADC_SAMPLE_SIZE];
	extern uint8_t IsRequestSendAdcData;
	HAL_ADC_Start_DMA(&hadc1, &ADC1_Buf[3], ADC_SAMPLE_SIZE);
	HAL_TIM_Base_Start(&htim6);

	SendVcpData(ADC_STATUS_VCP_BUSY, strlen(ADC_STATUS_VCP_BUSY));
	IsRequestSendAdcData = true;
}

void ADC_Stop() {
	extern ADC_HandleTypeDef hadc1;
	extern TIM_HandleTypeDef htim6;
	extern uint8_t IsRequestSendAdcData;
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_TIM_Base_Stop(&htim6);
	SendVcpData(ADC_STATUS_VCP_IDLE, strlen(ADC_STATUS_VCP_IDLE));
	IsRequestSendAdcData = false;
}

void SendAdcStatus() {
	char buf[50] = {0};
	sprintf(buf, "%s %d", GetADCRequestSignalStatus()? ADC_STATUS_VCP_BUSY: ADC_STATUS_VCP_IDLE, GetAdcFrequence() );
	SendVcpData(buf, strlen(buf));
}

void SendVcpData(char* text, uint8_t len) {
	extern uint8_t IsRequestSendAdcData;
	uint8_t PrevIsRequestAdcData = IsRequestSendAdcData;
	IsRequestSendAdcData = false;

	CDC_Transmit_FS(text,  len);

	IsRequestSendAdcData = PrevIsRequestAdcData;
}
