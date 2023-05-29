/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS. version
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
/* Includes ------------------------------------------------------------------*/

#include "configure.h"
#include "global.h"
/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void ShowNextDisplay(void);
void ShowPreviousDisplay(void);

////////////////////////////////////////////////////////////////////////////////cmdQue
extern uint32_t bootMode;
extern uint32_t DisplayIndex;
extern uint32_t HeartBeat;
extern uint32_t Percent ;
extern uint32_t DevicePosition ;
extern uint32_t BootStateStep ;
extern uint32_t WatchdogCounterMs ;
extern uint32_t WatchdogMs;
extern uint32_t CanRxCount;
extern uint32_t CanTxCount;
extern uint32_t LastCanRxMsgId;
extern uint32_t LastCanTxMsgId;
extern uint16_t requestToPauseAtEndOfMove;
extern uint16_t requestToPauseAtEndOfLayer;



extern ForeTaskFlag_t ForegroundTaskFlag;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
