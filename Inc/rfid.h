/*
 * rfid.h
 *
 *  Created on: Mar 14, 2021
 *      Author: falcon
 */

#ifndef RFID_H_
#define RFID_H_
#include "main.h"
#include <stdbool.h>

////////////////////////////////

#ifndef uchar
#define uchar unsigned char
#endif

#define RFID_BLOCK_SIZE 	16
#define RFID_BUFFER_SIZE 	1024
#define RFID_BLOCK_NUMBER 	64
#define RFID_MARK_SIZE 		4 //'RFID'
#define RFID_STATUS_INDEX 		4 //'0,1'
#define RFID_REQUEST_INDEX 		5 //RFID_REQUEST Value
#define RFID_HEADER_SIZE		6 //RFID[STATUS=1Byte]=5
#define RFID_VCP_BUFFER_SIZE 	RFID_BUFFER_SIZE+RFID_HEADER_SIZE


#define RFID_ADDRESS_FREQUENCY		10  //Frequency Data is written from 10 block.

typedef enum RFID_REQUEST{
	RFID_REQUEST_STATUS  =	0x80,
	RFID_REQUEST_READ_TAG  = 0x81,
	RFID_REQUEST_READ_DATA  = 0x82,
	RFID_REQUEST_WRITE  = 0x83,
	RFID_REQUEST_NONE  = 0x84,
}RFID_REQUEST;


typedef enum RFID_STATUS{
	RFID_STATUS_WAIT, RFID_STATUS_DETECTED,
}RFID_STATUS;

#define RFID_A_KEY 0x60
#define RFID_B_KEY 0x61

extern RFID_STATUS RFID_Status;
extern RFID_REQUEST RFID_Request;
extern uchar RFID_BUF[RFID_VCP_BUFFER_SIZE];
void 	rfid_init();
bool 	rfid_is_busy();
bool 	rfid_wait_process();
void 	rfid_reset_param();
bool 	rfid_card_detect(uchar* buf);
void 	rfid_get_card_type(uchar* buf, char* sztype);
bool 	rfid_read_card_id(uchar* cardid);
uchar 	rfid_select_tag(uchar* card);
bool 	rfid_auth(uchar key, uchar address, uchar *serNum);
bool 	rfid_read_block(int blocknumber, uchar* data);
bool 	rfid_write(uchar* data, int len);
bool 	rfid_write_block(int address, uchar* data);
bool 	rfid_read_tag();
bool 	rfid_read_data();
bool 	rfid_tag_detect();
bool 	rfid_process_scan();
bool 	rfid_scan_process(RFID_REQUEST req);
void 	rfid_vcp_report_detected_status(RFID_REQUEST req);
#endif /* RFID_H_ */
