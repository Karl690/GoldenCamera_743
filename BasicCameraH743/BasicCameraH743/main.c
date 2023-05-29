/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include "configure.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "taskmanager.h"
//#include "EEPROM/eeprom.h"
//#include "Communication/messages.h"
//#include "Communication/serial.h"
#include "Display/display.h"
#include "Display/DisplayList.h"
#include "Display/gui.h"
//#include "Motor/motor.h"
//#include "SETTINGS/settings.h"
//#include "DAC/dac.h"
//#include "Timer/timer.h"
#include "USB/usb_device.h"



SPI_LCD_HandleTypeDef LCDSpi1;
SPI_LCD_HandleTypeDef LCDSpi2;

SPI_HandleTypeDef PnP_Spi;//spi3

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


uint32_t bootMode __attribute__ ((section (".no_init")));
uint32_t HeartBeat;
uint32_t DisplayIndex __attribute__ ((section (".no_init")));
uint32_t Percent = 89;
uint32_t DevicePosition;
uint32_t BootStateStep;
uint32_t WatchdogCounterMs = 0;
uint32_t WatchdogMs = 0;
uint32_t CanRxCount;
uint32_t CanTxCount;
uint32_t LastCanRxMsgId;
uint32_t LastCanTxMsgId;
uint16_t requestToPauseAtEndOfMove=0;
uint16_t requestToPauseAtEndOfLayer=0;

//uint32_t DCMI_FrameIsReady;
//uint32_t Camera_FPS = 0;

ForeTaskFlag_t ForegroundTaskFlag = FORETASK_IDLE;
#define FRAME_WIDTH 160
#define FRAME_HEIGHT 120
uint16_t DCMI_BUF[FRAME_WIDTH][FRAME_HEIGHT];
uint32_t DCMI_FrameIsReady;
uint32_t Camera_FPS = 0;

void MX_DMA_Init(void);
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	bootMode = 0;
	
	HAL_Init();
	SystemClock_Config(); /* Configure the system clock */
	
	//Init_RCC();
	Init_GPIO();                 //configure direction and purpose of the I/O pin
	MX_DMA_Init();
	//Camera Init
	MX_DCMI_Init();
	MX_I2C1_Init();
	
	
	//Init_Settings();
	//COMSECS = &COM6; //set com6 as the secs port for testing, normall will be used for GCode
	//Init_Uart(SERIAL_UART3);
	//Init_Uart(SERIAL_UART6);
	
	//Init_ADC();
	//Init_DAC();
	//Init_CAN();
	
	SysTick_Config(SystemCoreClock / 4000); //slice timer has lowest interrupt priority
	MX_USB_DEVICE_Init();
	Camera_Init_Device(&hi2c1, FRAMESIZE_QQVGA);
	
	
	
	//Init_MotionTimers();
	//ConfigureTimer16PwmOutputsFor0_10V();
	//ConfigureTimer17PwmOutputsFor0_10V();
	////ConfigureTimer4PwmOutputsFor0_10V();//set the 0-10v output  karllvana change to timer 16,17 for this
	//ConfigureFreeRunning1usecTimer();//setup timer6 as my slice execution timer.
	//Init_SPI3();//pick and place feeder
	Init_Display(&LCDSpi1, LCD_SPI_PORT, COLOR_MODE_NORMAL);
	
	//Start_ADC();

	//Init_SineWaveBuffer();
	//Start_DAC();

//	if(!bootMode) {
//		InitFaultVariable();
//	}
//	bootMode = BOOT_NORMAL;
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)&DCMI_BUF, FRAME_WIDTH * FRAME_HEIGHT * 2 / 4);
	while (1)
	{
		
		//UpdateScreen(&LCDSpi1, NULL);
		//lcd_fillRect(0, 0, MAX_LCD_SIZE, LCD_HEIGHT, GUI_BUF);
#ifdef USE_CAMERA
		if (DCMI_FrameIsReady)
		{
			DCMI_FrameIsReady = 0;
			FillRGBRect(0, 0, LCD_WIDTH, LCD_HEIGHT, &DCMI_BUF[0][0]);	
		}		
#endif
		
		HAL_Delay(100);
//		switch (DisplayIndex)
//		{
//		case 0:UpdateScreen(&LCDSpi1, SecsStringTable); break;
//		case 0:UpdateScreen(&LCDSpi1, LcdVarsTable); break;
//		case 1:UpdateScreen(&LCDSpi1, UsbGcodeArguments); break;
//		case 2:UpdateScreen(&LCDSpi1, CMDQueValues);break;
//		case 3:UpdateScreen(&LCDSpi1, TaskTimeTable1);break;
//		case 4:UpdateScreen(&LCDSpi1, ADCValueTable);break;
//		case 5:UpdateScreen(&LCDSpi1, BarValueTable);break;
//		case 6:UpdateScreen(&LCDSpi1, FaultValueTable);break;
//		}

		//foreground task
//		switch(ForegroundTaskFlag) {
//		case FORETASK_ERASE_SOAPSTRING:
//			EraseSoapString();
//			ForegroundTaskFlag = FORETASK_IDLE;
//			break;
//		case FORETASK_WRITE_SOAPSTRING:
//			WriteSoapStringLine(WriteSoapString);
//			ForegroundTaskFlag = FORETASK_IDLE;
//			break;
//		case FORETASK_READ_SOAPSTRING:
//			if(ReadSoapStringLine(ReadSoapString)) {
//				SendUsbVcpString(ReadSoapString);
//				SendUsbVcpString(",");
//			}else{
//				SendUsbVcpString("\n");
//				ForegroundTaskFlag = FORETASK_IDLE;
//			}
//			break;
//		}
	}
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Supply configuration update enable
	*/
	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
	/** Configure the main internal regulator output voltage
	*/
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
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
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
	                            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
	                            | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
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
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4 | RCC_PERIPHCLK_I2C1;
	PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
	PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_D2PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI48, RCC_MCODIV_4);
}



/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */


void MX_DMA_Init(void)
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}

void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	static uint32_t count = 0, tick = 0;
	if (HAL_GetTick() - tick >= 1000)
	{
		tick = HAL_GetTick();
		Camera_FPS = count;
		count = 0;
	}
	count++;
	DCMI_FrameIsReady = 1;
}
//Motor ISR routines vector to here, with highest priority
void ShowNextDisplay()
{
	DisplayIndex++;
	if(DisplayIndex > (NUMBER_OF_DISPLAY_LISTS)) DisplayIndex = 0;
}
void ShowPreviousDisplay()
{
	if(DisplayIndex==0)
	{
		DisplayIndex = NUMBER_OF_DISPLAY_LISTS - 1;
		return;
	}
	if(DisplayIndex) DisplayIndex --; //if (rawChar==16)

}


void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}


