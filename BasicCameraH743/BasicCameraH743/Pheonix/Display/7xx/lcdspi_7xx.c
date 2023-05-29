#include "configure.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
SPI_LCD_HandleTypeDef* LCDHandler;
DMA_HandleTypeDef hdma_SPI_tx;

void SetupMyLCD(SPI_LCD_HandleTypeDef* LcdHandler, int SPIIndex)
{
	LCDHandler = LcdHandler;
	LcdHandler->InitState = 0;
	
	//Setup the Clock for SPI.
	switch (SPIIndex)
	{
	case 2:
		RCC->APB1LENR |= (RCC_APB1LENR_SPI2EN);
		RCC->APB1LRSTR &= ~(RCC_APB1LENR_SPI2EN);
		break;
	case 3:
		RCC->APB1LENR |= (RCC_APB1LENR_SPI3EN);
		RCC->APB1LRSTR &= ~(RCC_APB1LENR_SPI3EN);
		break;
	case 4:
		RCC->APB2ENR |= (RCC_APB2ENR_SPI4EN);
		RCC->APB2RSTR &= ~(RCC_APB2ENR_SPI4EN);
		break;
	}

	switch (SPIIndex)
	{
	case 0:break;
	case 1:break;
	case 2:LcdHandler->SpiHandle.Instance = SPI2;
		LcdHandler->PinType_RST = SPI2_LCD_RST;
		LcdHandler->PinType_CS = SPI2_LCD_CS;
		LcdHandler->PinType_RS = SPI2_LCD_RS;
		LcdHandler->PinType_SCK = SPI2_LCD_SCK;
		LcdHandler->PinType_MOSI = SPI2_LCD_MOSI;
		break;
	case 3:LcdHandler->SpiHandle.Instance = SPI3;
		LcdHandler->PinType_RST = SPI3_LCD_RST;
		LcdHandler->PinType_CS = SPI3_LCD_CS;
		LcdHandler->PinType_RS = SPI3_LCD_RS;
		LcdHandler->PinType_SCK = SPI3_LCD_SCK;
		LcdHandler->PinType_MOSI = SPI3_LCD_MOSI;
		break;
	case 4:LcdHandler->SpiHandle.Instance = SPI4;
		LcdHandler->PinType_RST = SPI4_LCD_RST;
		LcdHandler->PinType_CS = SPI4_LCD_CS;
		LcdHandler->PinType_RS = SPI4_LCD_RS;
		LcdHandler->PinType_SCK = SPI4_LCD_SCK;
		LcdHandler->PinType_MOSI = SPI4_LCD_MOSI;
		break;
	//put in code to catch a default as false and return;
  	  default : return;
  }

	LcdHandler->RST_Pin   = pinExtractPinMask(LcdHandler->PinType_RST);     LcdHandler->RST_Port    =pinExtractPortPtr(LcdHandler->PinType_RST);
	LcdHandler->CS_Pin   = pinExtractPinMask(LcdHandler->PinType_CS);     LcdHandler->CS_Port    =pinExtractPortPtr(LcdHandler->PinType_CS);
	LcdHandler->RS_Pin   = pinExtractPinMask(LcdHandler->PinType_RS);     LcdHandler->RS_Port    =pinExtractPortPtr(LcdHandler->PinType_RS);
	pinInit(LcdHandler->PinType_RS);
	pinInit(LcdHandler->PinType_CS);
	pinInit(LcdHandler->PinType_RST);

	//pinInit(LcdHandler->PinType_SCK);
	//pinInit(LcdHandler->PinType_MOSI);

	//reset the display so it will be ready to run
	LCD_RST_CLR;

	//finished with the GPIO, now it is time to setup the spi port
	LcdHandler->SpiHandle.Init.Mode = SPI_MODE_MASTER;
	LcdHandler->SpiHandle.Init.Direction = SPI_DIRECTION_1LINE;
	LcdHandler->SpiHandle.Init.DataSize = SPI_DATASIZE_8BIT;
	LcdHandler->SpiHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
	LcdHandler->SpiHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	LcdHandler->SpiHandle.Init.NSS = SPI_NSS_SOFT;
	LcdHandler->SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	LcdHandler->SpiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	LcdHandler->SpiHandle.Init.TIMode = SPI_TIMODE_DISABLE;
	LcdHandler->SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	LcdHandler->SpiHandle.Init.CRCPolynomial = 0x0;
	//////////////////// this part is for STM32H750 ///////////////////////////////////////////
	LcdHandler->SpiHandle.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	LcdHandler->SpiHandle.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	LcdHandler->SpiHandle.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	LcdHandler->SpiHandle.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	LcdHandler->SpiHandle.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	LcdHandler->SpiHandle.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	LcdHandler->SpiHandle.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	LcdHandler->SpiHandle.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	LcdHandler->SpiHandle.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	LcdHandler->SpiHandle.Init.IOSwap = SPI_IO_SWAP_DISABLE;
	//////////////////////////////////////////////////////////////////////////////////////////

	if (HAL_SPI_Init(&LcdHandler->SpiHandle) != HAL_OK)
	{
		Error_Handler();
	}
	LCD_RST_SET;
}


void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };
	//
	if (spiHandle->Instance == SPI2)
	{
		//Initializes the peripherals clock

		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI2;
		PeriphClkInitStruct.Spi123ClockSelection = RCC_PERIPHCLK_SPI123; //RCC_SPI45CLKSOURCE_D2PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			Error_Handler();
		}
		__HAL_RCC_SPI2_CLK_ENABLE(); /* SPI4 clock enable */

		/**SPI4 GPIO Configuration
		PD3     ------> SPI2_SCK
		PC1     ------> SPI2_MOSI
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_1;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		return;
	}
	//maybe spi3,
	if (spiHandle->Instance == SPI3)
	{
		// Initializes the peripherals clock

		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI3;
		PeriphClkInitStruct.Spi123ClockSelection = RCC_PERIPHCLK_SPI123; //RCC_SPI45CLKSOURCE_D2PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			Error_Handler();
		}
		__HAL_RCC_SPI3_CLK_ENABLE(); /* SPI4 clock enable */
		/**SPI4 GPIO Configuration
		 C10    ------> SPI3_SCK
		 C12     ------> SPI3_MOSI
		  */
		GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	}
	//maybe it is SPI4
	if (spiHandle->Instance == SPI4)
	{
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4;
		PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			Error_Handler();
		}
		__HAL_RCC_SPI4_CLK_ENABLE();

		__HAL_RCC_GPIOE_CLK_ENABLE();
		/**SPI4 GPIO Configuration
			PE11     ------> SPI4_NSS
			PE12     ------> SPI4_SCK
			PE14     ------> SPI4_MOSI
			*/
		GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_14;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		return;
	}
	return;
}
int32_t LCD_SPI_Senddata(uint8_t* pdata,uint32_t length)
{
	int32_t result;
	LCD_CS_CLR;
	LCD_RS_SET;


	result = HAL_SPI_Transmit(SPI_Drv,pdata,length,100);

	LCD_CS_SET;
	return result;
}


int32_t LCD_SPI_Recvdata(uint8_t* pdata,uint32_t length)
{
	int32_t result;
	LCD_CS_CLR;
	result = HAL_SPI_Receive(SPI_Drv,pdata,length,500);
	LCD_CS_SET;
	return result;
}

