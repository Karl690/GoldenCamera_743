/*
 * ST7735X_cfg.h
 *
 *  Created on: 16 ���. 2019 �.
 *      Author: Andriy Honcharenko
 *        Blog: https://stm32withoutfear.blogspot.com
 */

#ifndef ST7735X_CFG_H_
#define ST7735X_CFG_H_

#include "main.h"

#define ST7735X_SPI_PORT hspi4	//hspi1, hspi2, hspi3...
#define USE_SPI_DMA			//if used DMA for SPI bus

//#define ST7735X_1_8_DEFAULT_ORIENTATION	// AliExpress/eBay 1.8" display, default orientation
//#define ST7735S_1_8_DEFAULT_ORIENTATION 	// WaveShare ST7735S-based 1.8" display, default orientation
//#define ST7735X_1_44_DEFAULT_ORIENTATION 	// 1.44" display, default orientation
#define ST7735X_MINI_DEFAULT_ORIENTATION 	// mini 160x80 display (it's unlikely you want the default orientation)

//Port and pin connected signal 'RES' (reset) ST7735 display
#ifndef ST7735X_RES_Pin
#define ST7735X_RES_Pin 		GPIO_PIN_10// LCD_RES_Pin
#endif
#ifndef ST7735X_RES_GPIO_Port
#define ST7735X_RES_GPIO_Port 	GPIOE //LCD_RES_GPIO_Port
#endif
//Port and pin connected signal 'DC' (data or command) ST7735 display
#ifndef ST7735X_DC_Pin
#define ST7735X_DC_Pin 			GPIO_PIN_13 //LCD_WR_RS_Pin//GPIO_PIN_13
#endif
#ifndef ST7735X_DC_GPIO_Port
#define ST7735X_DC_GPIO_Port 	GPIOE //LCD_WR_RS_GPIO_Port//GPIOB
#endif
//Port and pin connected signal 'CS' (chip select) ST7735 display
#ifndef ST7735X_CS_Pin
#define ST7735X_CS_Pin 			GPIO_PIN_14 // LCD_CS_Pin//GPIO_PIN_14
#endif
#ifndef ST7735X_CS_GPIO_Port
#define ST7735X_CS_GPIO_Port 	 GPIOB//LCD_CS_GPIO_Port //GPIOB
#endif
//Port and pin connected signal 'BL' (back light) ST7735 display
#ifndef ST7735X_BL_Pin
#define ST7735X_BL_Pin			GPIO_PIN_9 //LCD_BK_Pin
#endif
#ifndef ST7735X_BL_GPIO_Port
#define ST7735X_BL_GPIO_Port 	GPIOE // LCD_BK_GPIO_Port
#endif

#endif /* ST7735X_CFG_H_ */
