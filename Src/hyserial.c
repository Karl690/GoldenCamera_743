#include <hyserial.h>
#include <stdbool.h>
#include "constant.h"
#include "systeminfo.h"
#include <string.h>
#include "rfid.h"
#include "adc.h"
#define HYCOMMAND_NUM  3
enum {M777, ADC, RFID};
char* hycommand[HYCOMMAND_NUM] = {"M777", "ADC", "RFID"};
char serial_buf[MAX_BUFFER_SIZE] = {0};
uint32_t  received_size = 0;
uint32_t  received_address = 0;
#define ONE_BUFFER_SIZE 64
void ReceivedVCPMessage(uint8_t* buf, uint32_t len)
{
	if(len == 1)
	{
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
			adc_change_samplerate(buf[0]);
			break;
		}
	}else {
		memcpy(serial_buf + received_address, buf, len);
		received_address += len;
		received_size += len;
		if(len < ONE_BUFFER_SIZE){
			ParseCommand(serial_buf, received_size);
			received_address = 0;
			received_size = 0;
			memset(serial_buf, 0, MAX_BUFFER_SIZE);
		}else {
			if(received_size >= MAX_BUFFER_SIZE) {
				received_address = 0;
				received_size = 0;
				memset(serial_buf, 0, MAX_BUFFER_SIZE);
			}
		}
		//CDC_Transmit_FS(buf, len);
	}
	//CDC_Transmit_FS(ASCII_ACK, 1);
}

void PingReply (void)
{
	sendRevisionString("PingReply");
}

void SendRevisionString(char *reason){
	extern SYSTEMINFO SystemInfo;
	uint8_t trans_buffer[100] = {0};
	//trans_buffer[0] = PING_CHAR;
	sprintf(trans_buffer, ">Hy: %s : GoldenCamera sw %d.%03d", reason, SystemInfo.softwareMajorVersion, SystemInfo.softwareMinorVersion);
	CDC_Transmit_FS(trans_buffer, strlen(trans_buffer));
}

bool ParseCommand(char* buf, uint32_t len)
{

	//return true;
	char* command = NULL;
	uint8_t CMD_ID = -1;
	for(int i = 0; i < HYCOMMAND_NUM; i ++) {
		if(strstr(buf, hycommand[i]) == buf) {
			CMD_ID = i;
			break;
		}
	}
	if(CMD_ID == -1) return false;

	switch(CMD_ID)
	{
	case M777:
		ParesM777Command(buf, len);
		break;
	case ADC:
		ParseADCCommand(buf, len);
		break;
	case RFID:
		ParesRfidCommand(buf, len);
		break;
	}
	return true;
}
//RFID [String]
bool ParesRfidCommand(char* buf, uint32_t len)
{
	if(len < 6) return false;
	char* param = buf + 5;
	char txt[256] = {0};
	if(strcmp(param, "ReadTag") == 0) { //RFID ReadTag : it reads the only 16byte
		rfid_read_tag();
	}else if(strcmp(param, "ReadData") == 0) { //Read ReadData: it reads the all
		rfid_read_data();
	}else if(strstr(param, "Write")){
		param += 6;
		rfid_write(param, len - 11);
	}

	return true;
}

bool ParseADCCommand(char* buf, uint32_t len)
{
	if(len < 4) return false;
	char* param = buf + 4; //"ADC F"
	len -= 4;
		param[len] = '\0';
		extern uint8_t IsRequestSendAdcData;
		char sendbuf[100] = {0};
		if(strcmp(param, "RequestSignal") == 0) {
			IsRequestSendAdcData = true;
		}else if(strcmp(param, "NoRequestSignal") == 0) {
			IsRequestSendAdcData = false;
		}else if(strcmp(param, "F1") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_1HZ);
		}else if(strcmp(param, "F10") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_10HZ);
		}else if(strcmp(param, "F100") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_100HZ);
		}else if(strcmp(param, "F1K") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_1KHZ);
		}else if(strcmp(param, "F1K") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_10KHZ);
		}else if(strcmp(param, "F10K") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_10KHZ);
		}else if(strcmp(param, "F100K") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_100KHZ);
		}else if(strcmp(param, "F1M") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_1MHZ);
		}else if(strcmp(param, "F10M") == 0) {
			adc_change_samplerate(ADC_SAMPLERATE_10MHZ);
		}
		return true;
}

bool ParesM777Command(char* buf, uint32_t len)
{
	if(len < 6) return false;
	char* param = buf + 5; //"M777 F"

	len -= 5;
	param[len] = '\0';
	extern uint8_t IsRequestSendAdcData;
	char sendbuf[100] = {0};
	if(strcmp(param, "Status") == 0) {

	}else if(strcmp(param, "Connect") == 0) {
		rfid_init();
	}else if(strcmp(param, "Close") == 0) {

	}
	return true;
}
bool GetADCRequestSignalStatus() {

	extern uint8_t IsRequestSendAdcData;
	return IsRequestSendAdcData;
}


void SendVcpData(char* text, uint8_t len)
{
	extern uint8_t IsRequestSendAdcData;
	uint8_t PrevIsRequestAdcData = IsRequestSendAdcData;
	IsRequestSendAdcData = false;
	CDC_Transmit_FS(text,  len);
	IsRequestSendAdcData = PrevIsRequestAdcData;
}
