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
#define RFID_BLOCK_SIZE 	16
#define RFID_BUFFER_SIZE 	1024
#define RFID_BLOCK_NUMBER 	64
#define RFID_MARK_SIZE 		4 //'RFID'
#define RFID_COMMAND_SIZE 		1 //'RFID'
#define RFID_HEADER_SIZE		RFID_MARK_SIZE+RFID_COMMAND_SIZE
#define RFID_VCP_BUFFER_SIZE 	RFID_BUFFER_SIZE+RFID_MARK_SIZE+RFID_COMMAND_SIZE


#define RFID_ADDRESS_FREQUENCY		10  //Frequency Data is written from 10 block.

#define RFID_COMMAND_DECTECTED  	0x80
#define RFID_COMMAND_READ  			0x81
#define RFID_COMMAND_WRITEN  		0x82
#define RFID_COMMAND_NODETECTED 	0x83

#ifndef uchar
#define uchar unsigned char
#endif
#define RFID_A_KEY 0x60
#define RFID_B_KEY 0x61
void 	rfid_init();
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
bool 	rfid_process_scan();
#endif /* RFID_H_ */
