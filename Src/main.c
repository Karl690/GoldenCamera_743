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
#include "lcd.h"
#include "constant.h"
#include "systeminfo.h"
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
uint16_t DCMI_BUF[FRAME_HEIGHT][FRAME_WIDTH];
uint16_t LCD_BUF[LCD_HEIGHT][LCD_WIDTH];
uint32_t DCMI_FrameIsReady;
uint8_t WAVE_BUF[FRAME_WIDTH] = {0};
uint32_t Camera_FPS=0;
uint16_t WAVE_POS = 0;
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
  SysTick_Config(SystemCoreClock / SYSTICKS_PER_SECOND);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DCMI_Init();
  MX_I2C1_Init();
  MX_SPI4_Init();
  MX_TIM1_Init();
  MX_USB_DEVICE_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  uint8_t text[20];

  SystemInfo.softwareMajorVersion = SOFTWARE_MAJOR_REVISION;
  SystemInfo.softwareMinorVersion = SOFTWARE_MINOR_REVISION;
  strcpy(SystemInfo.softwareUpdateDate, SOFTWARE_UPDATE_DATE);
  SystemInfo.mcuVersion = HAL_GetHalVersion();
  SystemInfo.mcuDeviceID = HAL_GetDEVID();
  SystemInfo.mcuRevisionID = HAL_GetREVID();
  LCD_Init();
  //LCDx_Init();
  LCD_Logo();
  //LCDx_Hyrellogo();


  Camera_Init_Device(&hi2c1, FRAMESIZE_QQVGA);
  sprintf((char *)&text, "SW %d.%03d   ", SOFTWARE_MAJOR_REVISION, SOFTWARE_MINOR_REVISION);
  LCD_ShowString(40, 2, ST7735Ctx.Width, 16, 12, text);

  sprintf((char *)&text, "LongPress K1 to Run");
  LCD_ShowString(50, 58, ST7735Ctx.Width, 16, 12, text);

  while (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
  {
	  HAL_Delay(10);
  }
#ifdef _HAS_CAMERA_
  HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)&DCMI_BUF, FRAME_WIDTH * FRAME_HEIGHT * 2 / 4);
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint16_t AD_RES = 0;
  uint16_t raw;
#ifndef _HAS_CAMERA_
  ST7735_FillRect(&st7735_pObj, 0, 0, ST7735Ctx.Width, 80, 0x000);
#endif
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 10);
	  raw = HAL_ADC_GetValue(&hadc1);
	  if(WAVE_POS >= ST7735Ctx.Width) WAVE_POS = 0;

	  WAVE_BUF[WAVE_POS] = raw;
	  HAL_ADC_Stop(&hadc1);
#ifdef _HAS_CAMERA_
	  if (DCMI_FrameIsReady)
	  {
		  DCMI_FrameIsReady = 0;
		  //CDx_Hyrellogo();
		  ST7735_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)&DCMI_BUF[20][0], ST7735Ctx.Width, 80);
		  sprintf((char *)&text,"%d", raw);
		  LCD_ShowString(5,5,60,16,12,text);
		  HAL_Delay(10);
	  }
#else
	  //ST7735_FillRect(&st7735_pObj, 0, 0, ST7735Ctx.Width, ST7735Ctx.Height, 0x00);
  	  //ST7735_DrawHLine(&st7735_pObj, 0, ST7735Ctx.Height/2, ST7735Ctx.Width, 0x07E0);
  	  //ST7735_DrawVLine(&st7735_pObj, ST7735Ctx.Width / 2, 0, ST7735Ctx.Height, 0x07E0);
  	  GuiDrawADC(LCD_BUF, WAVE_BUF, WAVE_POS);
	  //DrawWave(WAVE_BUF, WAVE_POS, ST7735Ctx.Width);
  	  ST7735_FillRGBRect(&st7735_pObj,0,0,(uint8_t *)&LCD_BUF[0][0], ST7735Ctx.Width, ST7735Ctx.Height);
	  sprintf((char *)&text,"%d", raw);
	  LCD_ShowString(5,5,160,16,12,text);
	  HAL_Delay(10);
	  WAVE_POS ++;
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4|RCC_PERIPHCLK_SPI2
                              |RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.PLL2.PLL2M = 2;
  PeriphClkInitStruct.PLL2.PLL2N = 32;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
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
