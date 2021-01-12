/* vim: set ai et ts=4 sw=4: */
#ifndef __ST7735X_H__
#define __ST7735X_H__

#include "main.h"
#include <stdbool.h>

#include "../ST7735x/fonts.h"

#define ST7735X_MADCTL_MY  0x80
#define ST7735X_MADCTL_MX  0x40
#define ST7735X_MADCTL_MV  0x20
#define ST7735X_MADCTL_ML  0x10
#define ST7735X_MADCTL_RGB 0x00
#define ST7735X_MADCTL_BGR 0x08
#define ST7735X_MADCTL_MH  0x04

/*** Redefine if necessary ***/
#define ST7735X_SPI_PORT hspi2
extern SPI_HandleTypeDef ST7735X_SPI_PORT;

#define ST7735X_RES_Pin       LCD2_SPI2_MISO_RST_Pin// SPI2_MISO_LCD_Pin
#define ST7735X_RES_GPIO_Port LCD2_SPI2_MISO_RST_GPIO_Port   //SPI2_MISO_LCD_GPIO_Port
#define ST7735X_CS_Pin        LCD2_SPI_NSS_CS_Pin  //LCD_CS_Pin
#define ST7735X_CS_GPIO_Port  LCD2_SPI_NSS_CS_GPIO_Port //LCD_CS_GPIO_Port
#define ST7735X_DC_Pin        LCD2_GPIO_RS_Pin  // LCD_RS_Pin
#define ST7735X_DC_GPIO_Port  LCD2_GPIO_RS_GPIO_Port //LCD_RS_GPIO_Port

// AliExpress/eBay 1.8" display, default orientation
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 0
#define ST7735_YSTART 0
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY)
*/

// AliExpress/eBay 1.8" display, rotate right
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 0
#define ST7735_YSTART 0
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV)
*/

// AliExpress/eBay 1.8" display, rotate left
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 0
#define ST7735_YSTART 0
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV)
*/

// AliExpress/eBay 1.8" display, upside down
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 0
#define ST7735_YSTART 0
#define ST7735_ROTATION (0)
*/

// WaveShare ST7735S-based 1.8" display, default orientation
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB)
*/

// WaveShare ST7735S-based 1.8" display, rotate right
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 1
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB)
*/

// WaveShare ST7735S-based 1.8" display, rotate left
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 128
#define ST7735_XSTART 1
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB)
*/

// WaveShare ST7735S-based 1.8" display, upside down
/*
#define ST7735_IS_160X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ST7735_ROTATION (ST7735_MADCTL_RGB)
*/

// 1.44" display, default orientation
#define ST7735X_IS_128X128 1
#define ST7735X_WIDTH  128
#define ST7735X_HEIGHT 128
#define ST7735X_XSTART 2
#define ST7735X_YSTART 3
#define ST7735X_ROTATION (ST7735X_MADCTL_MX | ST7735X_MADCTL_MY | ST7735X_MADCTL_BGR)

// 1.44" display, rotate right
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 3
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// 1.44" display, rotate left
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 1
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// 1.44" display, upside down
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ST7735_ROTATION (ST7735_MADCTL_BGR)
*/

// mini 160x80 display (it's unlikely you want the default orientation)
/*
#define ST7735_IS_160X80 1
#define ST7735_XSTART 26
#define ST7735_YSTART 1
#define ST7735_WIDTH  80
#define ST7735_HEIGHT 160 
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_BGR)
*/

// mini 160x80, rotate left
/*
#define ST7735_IS_160X80 1
#define ST7735_XSTART 1
#define ST7735_YSTART 26
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 80
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// mini 160x80, rotate right 
/*
#define ST7735_IS_160X80 1
#define ST7735_XSTART 1
#define ST7735_YSTART 26
#define ST7735_WIDTH  160
#define ST7735_HEIGHT 80
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

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
#define ST7735X_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// call before initializing any SPI devices
void ST7735X_Unselect();

void ST7735X_Init(void);
void ST7735X_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735X_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7735X_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735X_FillScreen(uint16_t color);
void ST7735X_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ST7735X_InvertColors(bool invert);

#endif // __ST7735X_H__
