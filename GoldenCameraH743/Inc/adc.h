/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */

#define ADC_SAMPLE_SIZE 1024

#define ADC_SAMPLERATE_1HZ			0xF0
#define ADC_SAMPLERATE_10HZ			0xF1
#define ADC_SAMPLERATE_100HZ		0xF2
 #define ADC_SAMPLERATE_1KHZ		0xF3
#define ADC_SAMPLERATE_10KHZ		0xF4
#define ADC_SAMPLERATE_100KHZ		0xF5
#define ADC_SAMPLERATE_1MHZ			0xF6
#define ADC_SAMPLERATE_10MHZ		0xF7


#define ADC_STATUS_VCP_IDLE				"ADC_STATUS_VCP_IDLE"
#define ADC_STATUS_VCP_BUSY				"ADC_STATUS_VCP_BUSY"


/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */
void adc_change_samplerate(uint8_t Code);
void adc_start();
void adc_stop();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
