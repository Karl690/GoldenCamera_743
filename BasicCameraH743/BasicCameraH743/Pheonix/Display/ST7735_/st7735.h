#pragma once
#include "configure.h"
#if defined(ST7735) && defined(USE_LCD)
#include "main.h"
#include <stddef.h>
typedef enum {
	scr_normal = 0,
	scr_CW     = 1,
	scr_CCW    = 2,
	scr_180    = 3
} ScrOrientation_TypeDef;

void ST7735_Init();
void ST7735_Clear(uint16_t color);
void ST7735_FillRGBRect(uint32_t Xpos, uint32_t Ypos, uint16_t *pData, uint32_t Width, uint32_t Height);

void ST7735_SetAddress(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE);
void ST7735_WriteBuff(uint16_t *DataBuff, uint16_t DataSize);
#endif
