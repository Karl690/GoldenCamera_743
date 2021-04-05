/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
#include "lcd.h"
#include "gui.h"
#include "tim.h"

bool 		ADC_EnableDrawWave = false;
float 		ADC_WaveScale = 1.0;
uint16_t 	ADC_WavePos = 0;
uint8_t 	ADC1_Buf[ADC_SAMPLE_SIZE + 3] = {0};
uint8_t 	ADC1_DoneFlag = 0;
uint32_t 	ADC1_SampleRate = 10000;
uint8_t 	IsRequestSendAdcData = 0;

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_8B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T6_TRGO;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance == ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA7     ------> ADC1_INP7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Stream1;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC12_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA7     ------> ADC1_INP7
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_7);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void adc_init(){
	ADC1_Buf[0] = 'A';
	ADC1_Buf[1] = 'D';
	ADC1_Buf[2] = 'C';

	HAL_ADC_Start_DMA(&hadc1, &ADC1_Buf[3], ADC_SAMPLE_SIZE);
	HAL_TIM_Base_Start_IT(&htim6);
}
void adc_display_wave() {
	char text[30] = {0};
	if(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET && (ADC1_DoneFlag))
	{
		gui_reset(GUI_BUF, GUI_COLOR_BACKGROUND);
		gui_draw_axis(GUI_BUF, GUI_COLOR_AXIS);
		if(ADC1_DoneFlag == 1){ // && ADC_EnableDrawWave) {
			gui_draw_wave(GUI_BUF, ADC1_Buf+3, ADC_SAMPLE_SIZE, ADC_WavePos, ADC_WaveScale, GUI_COLOR_ADC_CHANNEL_01);
			ADC1_DoneFlag = 0;
			ADC_EnableDrawWave = false;
		}

		sprintf(text, "SR: %dHz", ADC1_SampleRate);
		gui_draw_string(GUI_BUF, 10, 10, 100, 16, 12, text);
		ST7735_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)&GUI_BUF[0][0], ST7735Ctx.Width, ST7735Ctx.Height);
		ADC1_SampleRate = GetAdcFrequence(); //SystemCoreClock / (float)(htim6.Init.Prescaler * htim6.Init.Period) ;
	  //LCD_ShowString(10,10, ST7735Ctx.Width, 16, 12, text);
	}
}

uint32_t g_timerTick = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(IsRequestSendAdcData)
	{
		uint32_t threshhold = GetAdcFrequence();
		threshhold /= 100;
		if(threshhold < g_timerTick)
		{
			g_timerTick = 0;
			CDC_Transmit_FS(ADC1_Buf, ADC_SAMPLE_SIZE+3);
		}
		g_timerTick ++;
	}
	//HAL_GPIO_TogglePin(PE3_HeartbeatLed_GPIO_Port, PE3_HeartbeatLed_Pin);
	if(hadc == &hadc1) ADC1_DoneFlag = 1;
#ifdef _HAS_ADC2_
	else if(hadc == &hadc2) ADC2_DoneFlag = 1;
#endif

}


void adc_change_samplerate(uint8_t Code)
{
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_TIM_Base_Stop(&htim6);
	uint32_t prescaler = htim6.Init.Prescaler;
	uint32_t period = htim6.Init.Period;

	switch(Code)
	{
	case ADC_SAMPLERATE_1HZ:
		prescaler = 10000 - 1;
		period = 10000-1;
		break;
	case ADC_SAMPLERATE_10HZ:
		prescaler = 10000-1;
		period = 1000-1;
		break;
	case ADC_SAMPLERATE_100HZ:
		prescaler = 10000-1;
		period = 100-1;
		break;
	case ADC_SAMPLERATE_1KHZ:
		prescaler = 10000-1;
		period = 10-1;
		break;
	case ADC_SAMPLERATE_10KHZ:
		prescaler = 1000-1;
		period = 10-1;
		break;
	case ADC_SAMPLERATE_100KHZ:
		prescaler = 100-1;
		period = 10-1;
		break;
	case ADC_SAMPLERATE_1MHZ:
		prescaler = 10-1;
		period = 10-1;
		break;
	case ADC_SAMPLERATE_10MHZ:
		prescaler = 0;
		period = 10-1;
		break;
	}

	htim6.Init.Prescaler = prescaler;
	htim6.Init.Period = period;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
	    Error_Handler();
	}

	HAL_ADC_Start_DMA(&hadc1, &ADC1_Buf[3], ADC_SAMPLE_SIZE);
	HAL_TIM_Base_Start_IT(&htim6);
}
void adc_start()
{
	HAL_ADC_Start_DMA(&hadc1, &ADC1_Buf[3], ADC_SAMPLE_SIZE);
	HAL_TIM_Base_Start(&htim6);

	SendVcpData(ADC_STATUS_VCP_BUSY, strlen(ADC_STATUS_VCP_BUSY));
	IsRequestSendAdcData = true;
}

void sdc_stop()
{
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_TIM_Base_Stop(&htim6);
	SendVcpData(ADC_STATUS_VCP_IDLE, strlen(ADC_STATUS_VCP_IDLE));
	IsRequestSendAdcData = false;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
