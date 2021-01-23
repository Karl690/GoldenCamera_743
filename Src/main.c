/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dcmi.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "camera.h"
#include "lcdx.h"
#include "constant.h"
#include "systeminfo.h"
#include "gui.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
SYSTEMINFO SystemInfo = {0};
#ifdef _HAS_CAMERA_
uint16_t DCMI_Buf[FRAME_HEIGHT][FRAME_WIDTH];
uint32_t Camera_FPS=0;
uint32_t DCMI_FrameIsReady;
#else
float ADC_WaveScale = 1.0;
uint16_t ADC_WavePos = 0;
uint8_t ADC1_Buf[ADC_SAMPLE_SIZE + 3] = {0};
uint8_t ADC2_Buf[ADC_SAMPLE_SIZE + 3] = {0};
uint8_t ADC1_DoneFlag = 0;
uint8_t ADC2_DoneFlag = 0;
uint32_t ADC1_SampleRate = 10000;
uint8_t IsRequestSendAdcData = 0;
uint32_t Wave_LUT[128] = {
    2048, 2149, 2250, 2350, 2450, 2549, 2646, 2742, 2837, 2929, 3020, 3108, 3193, 3275, 3355,
    3431, 3504, 3574, 3639, 3701, 3759, 3812, 3861, 3906, 3946, 3982, 4013, 4039, 4060, 4076,
    4087, 4094, 4095, 4091, 4082, 4069, 4050, 4026, 3998, 3965, 3927, 3884, 3837, 3786, 3730,
    3671, 3607, 3539, 3468, 3394, 3316, 3235, 3151, 3064, 2975, 2883, 2790, 2695, 2598, 2500,
    2400, 2300, 2199, 2098, 1997, 1896, 1795, 1695, 1595, 1497, 1400, 1305, 1212, 1120, 1031,
    944, 860, 779, 701, 627, 556, 488, 424, 365, 309, 258, 211, 168, 130, 97,
    69, 45, 26, 13, 4, 0, 1, 8, 19, 35, 56, 82, 113, 149, 189,
    234, 283, 336, 394, 456, 521, 591, 664, 740, 820, 902, 987, 1075, 1166, 1258,
    1353, 1449, 1546, 1645, 1745, 1845, 1946, 2047
};
uint32_t Pulse_LUT[128] = {
    3000, 0, 3000, 0, 3000, 0, 3000, 0, 3000,0,
	1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000,0,
	3000, 0, 3000, 0, 3000, 0, 3000, 0, 3000,0,
	1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000,0,
	3000, 0, 3000, 0, 3000, 0, 3000, 0, 3000,0,
	1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000,0,
	3000, 0, 3000, 0, 3000, 0, 3000, 0, 3000,0,
	1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000,0,
	3000, 0, 3000, 0, 3000, 0, 3000, 0, 3000,0,
	1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000,0,
	3000, 0, 3000, 0, 3000, 0, 3000, 0, 3000,0,
	1000, 0, 1000, 0, 1000, 0, 1000, 0, 1000,0,
	3000, 0, 3000, 0, 3000, 0, 3000, 0
};
#endif
uint16_t LCD_BUF[LCD_HEIGHT][LCD_WIDTH];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  //SysTick_Config(SystemCoreClock / SYSTICKS_PER_SECOND);

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DCMI_Init();
  MX_I2C1_Init();
  MX_SPI4_Init();
  MX_USB_DEVICE_Init();
  MX_ADC1_Init();
  MX_DAC1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  uint8_t text[30];

  SystemInfo.softwareMajorVersion = SOFTWARE_MAJOR_REVISION;
  SystemInfo.softwareMinorVersion = SOFTWARE_MINOR_REVISION;
  strcpy(SystemInfo.softwareUpdateDate, SOFTWARE_UPDATE_DATE);
  SystemInfo.mcuVersion = HAL_GetHalVersion();
  SystemInfo.mcuDeviceID = HAL_GetDEVID();
  SystemInfo.mcuRevisionID = HAL_GetREVID();
  ADC1_SampleRate  =  SystemCoreClock / (float)(htim6.Init.Prescaler * htim6.Init.Period * 1000) ;
  lcdx_init();
  lcdx_logo();

#ifdef _HAS_CAMERA_
  Camera_Init_Device(&hi2c1, FRAMESIZE_QQVGA);
#endif
  sprintf((char *)&text, "SW %d.%03d   ", SOFTWARE_MAJOR_REVISION, SOFTWARE_MINOR_REVISION);
  //LCD_ShowString(40, 2, ST7735Ctx.Width, 16, 12, text);

  sprintf((char *)&text, "LongPress K1 to Run");
  //LCD_ShowString(50, 58, ST7735Ctx.Width, 16, 12, text);

  while (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
  {
	  HAL_Delay(10);
  }
#ifdef _HAS_CAMERA_
  HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)&DCMI_Buf, FRAME_WIDTH * FRAME_HEIGHT * 2 / 4);
#endif
  ADC1_Buf[0] = 'A';
  ADC1_Buf[1] = 'D';
  ADC1_Buf[2] = 'C';
  HAL_ADC_Start_DMA(&hadc1, &ADC1_Buf[3], ADC_SAMPLE_SIZE);
  HAL_TIM_Base_Start(&htim6);
  HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, (uint32_t*)Pulse_LUT, 128, DAC_ALIGN_8B_R);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

#ifndef _HAS_CAMERA_
  //ST7735_FillRect(&st7735_pObj, 0, 0, ST7735Ctx.Width, 80, 0x000);
#endif
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
#ifdef _HAS_CAMERA_
	  if (DCMI_FrameIsReady)
	  {
		  DCMI_FrameIsReady = 0;
		  //CDx_Hyrellogo();
		  //ST7735_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)&DCMI_Buf[20][0], ST7735Ctx.Width, 80);
		  sprintf((char *)&text,"%d", raw);
		  //LCD_ShowString(5,5,60,16,12,text);
		  HAL_Delay(10);
	  }
#else
	  if(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET && (ADC1_DoneFlag || ADC2_DoneFlag))
	  {

		  //GuiReset(LCD_BUF, GUI_COLOR_BACKGROUND);
		  if(ADC1_DoneFlag == 1 ) {
			  //GuiDrawWave(LCD_BUF, ADC1_Buf, ADC_WavePos, ADC_WaveScale, GUI_COLOR_ADC_CHANNEL_01);
			  ADC1_DoneFlag = 0;
		  }

		  //GuiDrawAxis(LCD_BUF, GUI_COLOR_AXIS);
		  //ST7735X_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)&LCD_BUF[0][0], ST7735Ctx.Width, ST7735Ctx.Height);
		  ADC1_SampleRate  =  GetAdcFrequence(); //SystemCoreClock / (float)(htim6.Init.Prescaler * htim6.Init.Period) ;
		  sprintf(text, "SR: %dHz", ADC1_SampleRate);
		  //LCD_ShowString(10,10, ST7735Ctx.Width, 16, 12, text);
	  }
	  HAL_Delay(1);

#endif
	  // Start ADC Conversion

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI48, RCC_MCODIV_4);
  /** Enable USB Voltage detector
  */
  HAL_PWREx_EnableUSBVoltageDetector();
}

/* USER CODE BEGIN 4 */
#ifdef _HAS_CAMERA_
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	static uint32_t count = 0,tick = 0;
	if(HAL_GetTick() - tick >= 1000)
	{
		tick = HAL_GetTick();
		Camera_FPS = count;
		count = 0;
	}
	count ++;
	DCMI_FrameIsReady = 1;
}
#endif


uint32_t g_timerTick = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(IsRequestSendAdcData)
	{
		uint32_t threshhold = SystemCoreClock / ((htim6.Init.Prescaler * htim6.Init.Period));
		threshhold /= 10000 * 5;
		if(threshhold < g_timerTick)
		{
			g_timerTick = 0;
			CDC_Transmit_FS(ADC1_Buf, ADC_SAMPLE_SIZE+3);
		}
		g_timerTick ++;
	}

	HAL_GPIO_TogglePin(PE3_HeartbeatLed_GPIO_Port, PE3_HeartbeatLed_Pin);
	if(hadc == &hadc1) ADC1_DoneFlag = 1;
#ifdef _HAS_ADC2_
	else if(hadc == &hadc2) ADC2_DoneFlag = 1;
#endif

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
