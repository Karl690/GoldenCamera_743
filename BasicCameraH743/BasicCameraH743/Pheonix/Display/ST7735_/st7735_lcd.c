#include "configure.h"
#if defined(ST7735) && defined(USE_LCD)
#include "st7735_lcd.h"
#include "st7735.h"
#include "Display/display.h"
#include "Display/colortables.h"
#include "Display/LcdDefinitions.h"

//LCD_Brightness timer

//if Orientation is 0, it is ORIENTATION_PORTRAIT;
//					1 = PORTRAIT_ROT180
//					2 = LANDSCAPE
//					3 = LANDSCAPE_ROT180
void Init_Display(SPI_LCD_HandleTypeDef* LcdHandler, uint8_t SpiIndex, uint8_t colorMode)
{
	SetupMyLCD(LcdHandler, SpiIndex);
	LcdHandler->controller = MYLCD_CONTROLLER;
	LcdHandler->width = MYLCD_WIDTH;
	LcdHandler->height = MYLCD_HEIGHT;
	LcdHandler->orientation = MYLCD_ORIENTATION;
	ST7735_Init();
	//LcdHandler->ColorMode = colorMode;
	LcdHandler->InitState = 1; //it's ok
}

void FillRGBRect(int16_t row, int16_t linesize, uint16_t* buf)
{
	uint16_t* pData = buf;
	uint16_t ypos = row * linesize;
	//if(ypos + linesize < LCD_HEIGHT)
	LCD_CS_CLR;
	ST7735_SetAddress(0, ypos, LCD_WIDTH-1, ypos + linesize-1);
	LCD_RS_SET;
	
	for(uint16_t i = 0; i < linesize; i ++){
		if(ypos + i > LCD_HEIGHT) break;
		
		ST7735_WriteBuff(pData, LCD_WIDTH);
		pData += MAX_LCD_SIZE;
		
	}
	LCD_CS_SET;
}
#endif
