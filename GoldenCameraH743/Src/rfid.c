/*
 * rfid.cpp
 *
 *  Created on: Mar 14, 2021
 *      Author: falcon
 */

#include "rfid.h"
#include "gui.h"
#include "lcd.h"
#include "MFRC522.h"
uchar keyA[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
uchar keyB[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
uchar CardID[16] = {0};
uchar RFID_Request_WrittenData[RFID_BUFFER_SIZE] = {0};
uchar block_buf[RFID_BLOCK_SIZE] = {0};

uint32_t RFID_WrittenAddress = 1;
uint32_t RFID_Request_WrittenBufferLen = 0;

RFID_STATUS RFID_Status = RFID_STATUS_WAIT;
RFID_REQUEST RFID_Request = RFID_REQUEST_NONE;
uchar RFID_BUF[RFID_VCP_BUFFER_SIZE] = {0};
bool IsRfidBusy = false;
void rfid_init() {

	SPI_mfrc_Init();
	MFRC522_Init();
	GPIOA->ODR |= 1<<4;

	rfid_reset_param();
}
bool rfid_card_detect(uchar* buf)
{
	return MFRC522_Request(PICC_REQIDL, buf) == MI_OK?true:false;
}

void rfid_get_card_type(uchar* buf, char* sztype)
{
	short shorttype = buf[0] * 0x100 + buf[1];
	switch(shorttype) {
	case 0x4400:
		sprintf(sztype, "Mifare UltraLight");
		break;
	case 0x0400:
		sprintf(sztype, "Mifare One(S50)");
		break;
	case 0x0200:
		sprintf(sztype, "Mifare One(S70)");
		break;
	case 0x0800:
		sprintf(sztype, "Mifare Pro(X)");
		break;
	case 0x4403:
		sprintf(sztype, "Mifare DESFire");
		break;
	}

}
bool rfid_is_busy() {
	return IsRfidBusy;
}
bool rfid_read_card_id(uchar* cardid) {
	memcpy(CardID, cardid, RFID_BLOCK_SIZE);
	return MFRC522_Anticoll(cardid) == MI_OK?true:false;
}
uchar rfid_select_tag(uchar* card) {
	memcpy(CardID, card, RFID_BLOCK_SIZE);
	return MFRC522_SelectTag(card);
}
bool rfid_auth(uchar key, uchar address, uchar *serNum)
{
	return MFRC522_Auth(key, address, keyA, serNum) == MI_OK?true:false;
}
bool rfid_read_block(int blocknumber, uchar* data)
{
	return MFRC522_Read(blocknumber, data) == MI_OK?true:false;
}
bool rfid_write(uchar* data, int len)
{
	if(!rfid_wait_process()) return false;
	RFID_Request_WrittenBufferLen = len;
	memset(RFID_Request_WrittenData, 0, RFID_BUFFER_SIZE);
	memcpy(RFID_Request_WrittenData, data, len);
	RFID_Request = RFID_REQUEST_WRITE;
	return true;
}

bool rfid_write_block(int address, uchar* data)
{
	return MFRC522_Write(address, data) == MI_OK?true:false;
}


//this function return turn if process is in reading RFID tag, otherwise, false.
bool rfid_wait_process(){

	if(RFID_Status == RFID_STATUS_WAIT) return false; //in this case, Tag isn't detected.
	while(IsRfidBusy){
		break;
	}
	return true;

}
bool rfid_read_tag()
{
	if(!rfid_wait_process()) return false;
	RFID_Request = RFID_REQUEST_READ_TAG;
	return true;
}
bool rfid_read_data()
{
	if(!rfid_wait_process()) return false;
	RFID_Request = RFID_REQUEST_READ_DATA;
	return true;
}
void rfid_reset_param() {
	RFID_Request = RFID_REQUEST_NONE;
	RFID_Status = RFID_STATUS_DETECTED;
	RFID_BUF[0] = 'R';
	RFID_BUF[1] = 'F';
	RFID_BUF[2] = 'I';
	RFID_BUF[3] = 'D';
	RFID_BUF[RFID_STATUS_INDEX] = RFID_STATUS_WAIT;
	RFID_BUF[RFID_REQUEST_INDEX] = RFID_REQUEST_NONE;
}

//Read/Write the RFID Data.
//RFID Data has  64 Blocks. one block size is 16bits
bool rfid_scan_process(RFID_REQUEST req){

	uchar rfidtype[2] = {0};
	if(RFID_Request != RFID_REQUEST_NONE && RFID_Status == RFID_STATUS_WAIT) return false;
	while(!IsRfidBusy){
		break;
	}

	IsRfidBusy = true;
	bool Res = false;
	uint16_t WrittenAddress = 1;
	uint16_t WrittenBufferLen = 0;
	memset(block_buf, 0, RFID_BLOCK_SIZE);
	if(rfid_card_detect(block_buf))
	{
		rfidtype[0] = block_buf[0];
		rfidtype[1] = block_buf[1];
		RFID_Status = RFID_STATUS_DETECTED;
		if(rfid_read_card_id(block_buf))
		{

			block_buf[10] = rfidtype[0];
			block_buf[11] = rfidtype[1];
			memcpy(RFID_BUF+RFID_HEADER_SIZE, block_buf, RFID_BLOCK_SIZE);
			Res = true;

			if(req != RFID_REQUEST_NONE) {
				if(rfid_select_tag(block_buf) > 0) {
					for(int i = 0; i < RFID_BLOCK_NUMBER; i ++)
					{

						if(!rfid_auth(0x60, i, block_buf))
						{
							Res = false;
							break;
						}

						if(req == RFID_REQUEST_WRITE) {
							if(i == WrittenAddress){
								rfid_write_block(i, RFID_Request_WrittenData + (i - 1) * RFID_BLOCK_SIZE);
								WrittenAddress ++;
								if(WrittenAddress % 4  == 3 )
								{
									WrittenAddress ++;
									WrittenBufferLen += RFID_BLOCK_SIZE;
								}
								WrittenBufferLen += RFID_BLOCK_SIZE;
								if(WrittenBufferLen >= RFID_Request_WrittenBufferLen) {
									req = RFID_REQUEST_READ_DATA;
								}
							}
						}
						if(!rfid_read_block(i, RFID_BUF + i * RFID_BLOCK_SIZE + RFID_HEADER_SIZE))
						{
							Res = false;
							break;
						}

						if(req == RFID_REQUEST_READ_TAG && i > 2) {
							//in this case , we would be send the 2 block data.
							//there is tag information in the first block, and the IP address is in the second block
							Res = true;
							break;
						}
					}

				}
			}
		}
	}else{
		RFID_Status = RFID_STATUS_WAIT;
	}
	MFRC522_Halt();
	MFRC522_Init();

	rfid_vcp_report_detected_status(RFID_Request);
	IsRfidBusy = false;
	return Res;
}


//report the status of rfid detection thru VCP.
void rfid_vcp_report_detected_status(RFID_REQUEST req)
{

	RFID_BUF[RFID_REQUEST_INDEX] = req;
	if(req != RFID_REQUEST_NONE){
		RFID_BUF[RFID_STATUS_INDEX] = (uint8_t)RFID_Status;
		if(req == RFID_REQUEST_READ_TAG)
			CDC_Transmit_FS(RFID_BUF, RFID_HEADER_SIZE + RFID_BLOCK_SIZE * 2);
		else
			CDC_Transmit_FS(RFID_BUF, RFID_VCP_BUFFER_SIZE);
	}
	else if(RFID_BUF[RFID_STATUS_INDEX] != RFID_Status) {
		RFID_BUF[RFID_STATUS_INDEX] = (uint8_t)RFID_Status;
		CDC_Transmit_FS(RFID_BUF, RFID_HEADER_SIZE + RFID_BLOCK_SIZE);
		RFID_BUF[RFID_REQUEST_INDEX] = RFID_REQUEST_NONE;
		HAL_GPIO_WritePin(PE3_HeartbeatLed_GPIO_Port, PE3_HeartbeatLed_Pin, RFID_Status == RFID_STATUS_WAIT?GPIO_PIN_RESET:GPIO_PIN_SET);
	}
	RFID_Request = RFID_REQUEST_NONE;
}
