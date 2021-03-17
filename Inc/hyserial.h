/**
  ******************************************************************************
  * File Name          : command.h
  * Description        : This file provides code for the command thru VCP
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMAND_H
#define __COMMAND_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
 #include "main.h"


#define NULL_CHAR                  '\0'    // 0
#define TERMINATE_WAIT_CHAR          1
#define PAUSE_AT_END_OF_MOVE_CHAR    2
#define PAUSE_AT_END_OF_LAYER_CHAR   3
#define AVAILABLE_4                  4  // can be harvested for Repetrel to Hydra comm
#define HELLO_WORLD_CHAR             4  // char to send to Repetrel to get repetrel to talk to Hydra over the master comm port with a PING
#define SEND_STATUS_CHAR             5
#define ASCII_ACK                    6
#define PING_CHAR                    7  // (bell)
#define ABORT_CHAR                   8  // abort all processes, and stop all motion (backspace)
#define URGENT_911_CMD_CHAR          9
#define CATASTROPHIC_ERROR_ALERT_CHAR 9
#define CMD_END_CHAR                 10 // '\n' -  used to terminate every gcode line (linefeet)
#define SENDSTRING_TERM_CHAR         10
#define LF_CHAR                      10 // '\n'
#define JOG_Z_TABLE_UP               11
#define JOG_Z_TABLE_DOWN             12
#define CR_CHAR                      13 // '\r' (carriage return)
#define REPETREL_COMM_WATCHDOG_CHAR  14
#define LIGHTBURN_STOP               0x18
#define LARGEST_SPECIAL_CHAR         31 // anything below this will end a comment string

#define COMMENT_CHAR                 ';'
#ifdef USE_NEW_SOAPSTRING_DELIMTER_AND_STRIP_COMMENTS
#define SOAPSTRING_CHAR              '?'
#else //!USE_NEW_SOAPSTRING_DELIMTER_AND_STRIP_COMMENTS
#define SOAPSTRING_CHAR              ';'
#endif //!USE_NEW_SOAPSTRING_DELIMTER_AND_STRIP_COMMENTS
#define DIRECT_START_CHAR            '$'
#define RUN_LENGTH_ENCODE_CHAR       '#'
#define DIRECT_CONTINUATION_CHAR     '~'
#define SPACE_CHAR                   ' '
#define NOP_CHAR                     ' '

#define CHECKSUM_CHAR                '*'


#define LOOP_COUNT                   '!'
#define SCRIPT_LABEL                 '\''
#define STRING_DELIM                 '"'


#define ADC_SAMPLERATE_1HZ			0xF0
#define ADC_SAMPLERATE_10HZ			0xF1
#define ADC_SAMPLERATE_100HZ		0xF2
 #define ADC_SAMPLERATE_1KHZ		0xF3
#define ADC_SAMPLERATE_10KHZ		0xF4
#define ADC_SAMPLERATE_100KHZ		0xF5
#define ADC_SAMPLERATE_1MHZ			0xF6
#define ADC_SAMPLERATE_10MHZ		0xF7


#define RESPOND_CHAR				0x0F
#define AXIS_VISIBLE_CHAR			0x20
#define AXIS_INVISIBLE_CHAR			0x21
#define LCD_LIVESTREAM_CHAR			0x22
#define LCD_LOGO_CHAR				0x23


#define CMD_REQ 						"REQ"
#define CMD_RESPOND						"RPD"
#define CMD_RESPOND_SUCCESS				"SUC"
#define CMD_RESPOND_ERROR				"ERR"


#define ADC_STATUS_VCP_IDLE				"M777_STATUS_VCP_IDLE"
#define ADC_STATUS_VCP_BUSY				"M777_STATUS_VCP_BUSY"

 void ReceivedVCPMessage(uint8_t* buf, uint32_t len);
 bool ParseCommand(char* buf, uint32_t len);
 bool ParesRfidCommand(char* buf, uint32_t len);
 bool ParesM777Command(char* buf, uint32_t len);
 void ChangeADCSampleRate(uint8_t Code);
 bool GetADCRequestSignalStatus();
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__COMMAND_H

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



