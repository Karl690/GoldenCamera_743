#pragma once

//to change target just uncomment ONLY ONE of the following defines
//#define FK_407   //102207 board, rev X series, works with stm32F407VBT6 100 pin lqfp parts.
//#define FK_750   //102207 board, rev X series, works with STM32H750VBT6 100 pin lqfp parts.
//#define CORE_407I     //waveshare CORE407I on legacy 102207 boards, for EHR, and Hydras
#define H_743 
/* Display Compiling Option */
#define LCD_SPI_PORT 4  //set to 2,3,4  to use with x10 version of 102207 H board
#define USE_LCD
#define USE_CAMERA



#define ST7735
//#define ST7789
//#define ILI9341

#ifdef FK_407
#define USE_FLASH
#include "stm32f4xx_hal.h"
#include "GPIO/4xx/pininit.h"
#include "GPIO/4xx/pins_4xx.h"
#include "usb_device.h"
#include "ADC/4xx/adc_4xx.h"
#include "CAN/4xx/can_4xx.h"
#include "DAC/4xx/dac_4xx.h"
#include "Display/4xx/lcdspi_4xx.h"
#include "FLASH/4xx/flash_4xx.h"
#include "GPIO/4xx/pinout_FK_407.h"
#include "PNP/4xx/pnp_4xx.h"
#include "RCC/4xx/rcc_4xx.h"

#elif defined(FK_750)
#define USE_QSPI
#include "stm32h7xx_hal.h"
#include "GPIO/7xx/pininit.h"
#include "GPIO/7xx/pins_7xx.h"
#include "usb_device.h"
#include "ADC/7xx/adc_7xx.h"
#include "CAN/7xx/can_7xx.h"
#include "DAC/7xx/dac_7xx.h"
#include "Display/7xx/lcdspi_7xx.h"
#include "FLASH/7xx/flash_7xx.h"

#include "GPIO/7xx/pinout_FK_750.h"
#include "PNP/7xx/pnp_7xx.h"
#include "RCC/7xx/rcc_7xx.h"

#elif defined(H_743) 
#include "stm32h7xx_hal.h"
#include "GPIO/7xx/pininit.h"
#include "GPIO/7xx/pins_7xx.h"
#include "GPIO/7xx/pinout_H_743.h"
#include "usb_device.h"
#include "Display/7xx/lcdspi_7xx.h"
#include "RCC/7xx/rcc_7xx.h"
#ifdef USE_CAMERA
#include "Camera/i2c.h"
#include "Camera/dcmi.h"
#include "Camera/camera.h"
#endif

#elif defined(CORE_407I)
#define USE_FLASH
#include "stm32f4xx_hal.h"
#include "GPIO/4xx/pininit.h"
#include "GPIO/4xx/pins_4xx.h"
#include "usb_device.h"
#include "ADC/4xx/adc_4xx.h"
#include "CAN/4xx/can_4xx.h"
#include "DAC/4xx/dac_4xx.h"
#include "Display/4xx/lcdspi_4xx.h"
#include "FLASH/4xx/flash_4xx.h"

#include "GPIO/4xx/pinout_CORE_407I.h"
#include "PNP/4xx/pnp_4xx.h"
#include "RCC/4xx/rcc_4xx.h"
#endif



#ifdef ST7789 
#include  "Display/ST7789/st7789.h"
#elif defined(ST7735)
#include  "Display/ST7735/st7735.h"
#endif


#define RX_BUFFER_SIZE 0x7ff			//2k
#define RX_URGENT_BUFFER_SIZE 0x3ff	//1k
#define TX_BUFFER_SIZE 0x3ff			 //1k

//#define SECS_USART6
//#define USE_SERIAL_DMA3   //dma for serial port 3
//#define USE_SERIAL_DMA6   //dma for serial port 6
//#define USE_SERIAL_DMA