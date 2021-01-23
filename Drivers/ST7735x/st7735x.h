/*
 * st7735x.h
 *
 *  Created on: 16 ���. 2019 �.
 *      Author: Andriy Honcharenko
 *        Blog: https://stm32withoutfear.blogspot.com
 */

#ifndef __ST7735X_H__
#define __ST7735X_H__

#include "st7735x_cfg.h""
#include "fonts.h"
#include <stdbool.h>

extern SPI_HandleTypeDef ST7735X_SPI_PORT;

#define ST7735X_MADCTL_MY  0x80
#define ST7735X_MADCTL_MX  0x40
#define ST7735X_MADCTL_MV  0x20
#define ST7735X_MADCTL_RGB 0x00
#define ST7735X_MADCTL_BGR 0x08

// AliExpress/eBay 1.8" display, default orientation
#ifdef ST7735X_1_8_DEFAULT_ORIENTATION
#define ST7735X_IS_160X128		1
#define ST7735X_WIDTH  			128
#define ST7735X_HEIGHT 			160
#define ST7735X_XSTART 			0
#define ST7735X_YSTART 			0
#define ST7735X_DATA_ROTATION 	(ST7735X_MADCTL_MX | ST7735X_MADCTL_MY)
#endif //ST7735X_1_8_DEFAULT_ORIENTATION

// WaveShare ST7735S-based 1.8" display, default orientation
#ifdef ST7735S_1_8_DEFAULT_ORIENTATION
#define ST7735X_IS_160X128 		1
#define ST7735X_WIDTH  			128
#define ST7735X_HEIGHT 			160
#define ST7735X_XSTART 			2
#define ST7735X_YSTART 			1
#define	ST7735X_DATA_ROTATION	(ST7735X_MADCTL_MX | ST7735X_MADCTL_MY | ST7735X_MADCTL_RGB)
#endif //ST7735S_1_8_DEFAULT_ORIENTATION

// 1.44" display, default orientation
#ifdef ST7735X_1_44_DEFAULT_ORIENTATION
#define ST7735X_IS_128X128 		1
#define ST7735X_WIDTH  			128
#define ST7735X_HEIGHT 			128
#define ST7735X_XSTART 			2
#define ST7735X_YSTART 			3
//#define ST7735X_VALUE_ROTATION	0
#define ST7735X_DATA_ROTATION 	(ST7735X_MADCTL_MX | ST7735X_MADCTL_MY | ST7735X_MADCTL_BGR)
#endif //ST7735X_1_44_DEFAULT_ORIENTATION

// mini 160x80 display (it's unlikely you want the default orientation)
#ifdef ST7735X_MINI_DEFAULT_ORIENTATION
#define ST7735X_IS_160X80 		1
#define ST7735X_XSTART 			0
#define ST7735X_YSTART 			0
#define ST7735X_WIDTH  			160
#define ST7735X_HEIGHT 			80
//#define ST7735X_VALUE_ROTATION	0
#define ST7735X_DATA_ROTATION 	(ST7735X_MADCTL_MX | ST7735X_MADCTL_MY | ST7735X_MADCTL_BGR)
#endif //ST7735X_MINI_DEFAULT_ORIENTATION
/****************************/

#define ST7735X_NOP     0x00
#define ST7735X_SWRESET 0x01
#define ST7735X_RDDID   0x04
#define ST7735X_RDDST   0x09

#define ST7735X_SLPIN   0x10
#define ST7735X_SLPOUT  0x11
#define ST7735X_PTLON   0x12
#define ST7735X_NORON   0x13

#define ST7735X_INVOFF  0x20
#define ST7735X_INVON   0x21
#define ST7735X_DISPOFF 0x28
#define ST7735X_DISPON  0x29
#define ST7735X_CASET   0x2A
#define ST7735X_RASET   0x2B
#define ST7735X_RAMWR   0x2C
#define ST7735X_RAMRD   0x2E

#define ST7735X_PTLAR   0x30
#define ST7735X_COLMOD  0x3A
#define ST7735X_MADCTL  0x36

#define ST7735X_FRMCTR1 0xB1
#define ST7735X_FRMCTR2 0xB2
#define ST7735X_FRMCTR3 0xB3
#define ST7735X_INVCTR  0xB4
#define ST7735X_DISSET5 0xB6

#define ST7735X_PWCTR1  0xC0
#define ST7735X_PWCTR2  0xC1
#define ST7735X_PWCTR3  0xC2
#define ST7735X_PWCTR4  0xC3
#define ST7735X_PWCTR5  0xC4
#define ST7735X_VMCTR1  0xC5

#define ST7735X_RDID1   0xDA
#define ST7735X_RDID2   0xDB
#define ST7735X_RDID3   0xDC
#define ST7735X_RDID4   0xDD

#define ST7735X_PWCTR6  0xFC

#define ST7735X_GMCTRP1 0xE0
#define ST7735X_GMCTRN1 0xE1

// Color definitions
#define	ST7735X_BLACK   0x0000
#define	ST7735X_BLUE    0x001F
#define	ST7735X_RED     0xF800
#define	ST7735X_GREEN   0x07E0
#define ST7735X_CYAN    0x07FF
#define ST7735X_MAGENTA 0xF81F
#define ST7735X_YELLOW  0xFFE0
#define ST7735X_WHITE   0xFFFF

void ST7735X_Backlight_On(void);
void ST7735X_Backlight_Off(void);
void ST7735X_Init(void);
void ST7735X_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735X_DrawString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7735X_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735X_FillScreen(uint16_t color);
void ST7735X_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ST7735X_InvertColors(bool invert);
void ST7735X_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ST7735X_DrawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
void ST7735X_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void ST7735X_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void ST7735X_DrawEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color);
void ST7735X_FillEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color);
void ST7735X_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void ST7735X_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void ST7735X_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void ST7735X_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ST7735X_FillTriangle( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void ST7735X_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void ST7735X_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void ST7735X_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void ST7735X_SetRotation(uint8_t m);
uint8_t ST7735X_GetRotation(void);
int16_t ST7735X_GetHeight(void);
int16_t ST7735X_GetWidth(void);


#endif // __ST7735X_H__
