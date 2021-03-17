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
uchar WrittenData[RFID_BUFFER_SIZE] = {0};
uchar block_buf[RFID_BLOCK_SIZE] = {0};
enum {READ_NONE, READ_TAG, READ_DATA,};
uchar RequestRead = READ_NONE;
bool  isRequestWriten = false;
uint32_t WrittenAddress = 1;
uint32_t WriteReqeustLen = 0;
uint32_t WrittenLen = 0;

u_char RFID_BUF[RFID_VCP_BUFFER_SIZE] = {0};

void rfid_init() {

	SPI_mfrc_Init();
	MFRC522_Init();
	GPIOA->ODR |= 1<<4;

	RFID_BUF[0] = 'R';
	RFID_BUF[1] = 'F';
	RFID_BUF[2] = 'I';
	RFID_BUF[3] = 'D';
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
	isRequestWriten = true;
	WriteReqeustLen = len;
	WrittenLen = 0;
	WrittenAddress = 1;
	memset(WrittenData, 0, RFID_BUFFER_SIZE);
	memcpy(WrittenData, data, len);
	return true;
}

bool rfid_write_block(int address, uchar* data)
{
	return MFRC522_Write(address, data) == MI_OK?true:false;
}


bool rfid_read_tag()
{
	RequestRead = READ_TAG;
	return true;
}
bool rfid_read_data()
{
	RequestRead = READ_DATA;
	return true;
}
bool rfid_process_scan()
{
	HAL_GPIO_WritePin(PE3_HeartbeatLed_GPIO_Port, PE3_HeartbeatLed_Pin, GPIO_PIN_RESET);
	char text[256] = {0};
	uchar rfidtype[2] = {0};
	gui_reset(GUI_BUF, GUI_COLOR_BACKGROUND);
	if(rfid_card_detect(block_buf))
	{
	  rfid_get_card_type(block_buf, text);
	  rfidtype[0] = block_buf[0];
	  rfidtype[1] = block_buf[1];
	  gui_draw_string(GUI_BUF, 5, 5, 160, 16, 12, text);

	  //HAL_Delay(1);
	  memset(RFID_BUF+RFID_MARK_SIZE, 0, RFID_BUFFER_SIZE);
	  if(rfid_read_card_id(block_buf))
	  {
		  sprintf(text,"UID:%x %x %x %x", block_buf[0], block_buf[1], block_buf[2], block_buf[3]);
		  gui_draw_string(GUI_BUF, 5,25, 160, 16, 12, text);
		  RFID_BUF[RFID_MARK_SIZE] = RFID_COMMAND_DECTECTED;

		  block_buf[10] = rfidtype[0];
		  block_buf[11] = rfidtype[1];

		  memcpy(RFID_BUF+RFID_HEADER_SIZE, block_buf, RFID_BLOCK_SIZE);
		  CDC_Transmit_FS(RFID_BUF, RFID_BLOCK_SIZE + RFID_MARK_SIZE);
		  //HAL_Delay(100);
		  if(rfid_select_tag(block_buf) > 0 )
		  {
			  bool IsSuccess = true;

			  for(int i = 0; i < RFID_BLOCK_NUMBER; i ++ ) {
				  if(!rfid_auth(0x60, i, block_buf)) {
					  IsSuccess = false;
					  continue;
				  }
				  if(isRequestWriten && i == WrittenAddress) {
					  rfid_write_block(i, WrittenData + (i-1) * RFID_BLOCK_SIZE);
					  WrittenAddress ++;
					  if(WrittenAddress % 4 == 3) {
						  WrittenAddress ++;
						  WrittenLen += RFID_BLOCK_SIZE;
					  }
					  WrittenLen += RFID_BLOCK_SIZE;
					  if(WrittenLen >= WriteReqeustLen) {
						  isRequestWriten = false;
					  }
				  }
				  if(!rfid_read_block(i, RFID_BUF + i * RFID_BLOCK_SIZE + RFID_HEADER_SIZE)) {
					  IsSuccess = false;
					  break;
				  }
			  }
			  if(IsSuccess) {
				  sprintf(text,"Data Read!");
				  gui_draw_string(GUI_BUF, 5,45, 160, 16, 12, text);
				  RFID_BUF[RFID_MARK_SIZE] = RFID_COMMAND_READ;
				  if(RequestRead != READ_NONE)
					  CDC_Transmit_FS(RFID_BUF, RFID_VCP_BUFFER_SIZE);
			  }
		  }

	  }
	  MFRC522_Halt();
	  MFRC522_Init();
	}
	else {
	  sprintf(text, "Waiting for Card");
	  gui_draw_string(GUI_BUF, 10, 10, 100, 16, 12, text);

	  RFID_BUF[RFID_MARK_SIZE] = RFID_COMMAND_NODETECTED;
	  CDC_Transmit_FS(RFID_BUF, RFID_HEADER_SIZE);
	}
	ST7735_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)&GUI_BUF[0][0], ST7735Ctx.Width, ST7735Ctx.Height);
	//HAL_Delay(1000);

	return true;
}
