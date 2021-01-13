/*
 * gui.h
 *
 *  Created on: Jan 12, 2021
 *      Author: falcon
 */

#ifndef GUI_H_
#define GUI_H_
#include "st7735.h"
#define GUI_OK 		1
#define GUI_ERROR 	0
void GuiReset(uint16_t* lcd_buf, uint16_t Color);
void GuiDrawAxis(uint16_t* lcd_buf, uint16_t Color);
void GuiDrawADC(uint16_t* lcd_buf, uint8_t* wave_buf, float scale);
void GuiDrawWave(uint16_t* lcd_buf, uint8_t* wave_buf, uint16_t pos, float scale, uint16_t Color);
int32_t GuiDrawVLine(uint16_t* lcd_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color);
int32_t GuiDrawHLine(uint16_t* lcd_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color);
int32_t GuiDrawLine(uint16_t* lcd_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color);
int32_t GuiDrawRectangle(uint16_t* lcd_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color);
#endif /* GUI_H_ */
