/*
 * gui.h
 *
 *  Created on: Jan 12, 2021
 *      Author: falcon
 */

#ifndef GUI_H_
#define GUI_H_
#include "st7735x.h"
#define GUI_OK 		1
#define GUI_ERROR 	0

#define GUI_COLOR_BACKGROUND 		0x6101
#define GUI_COLOR_AXIS				0x2203
#define GUI_COLOR_GREEN				0xE707
#define GUI_COLOR_YELLOW			0xE0CF
#define GUI_COLOR_PINK				0x1FF8

#define GUI_COLOR_ADC_CHANNEL_01	GUI_COLOR_GREEN
#define GUI_COLOR_ADC_CHANNEL_02	GUI_COLOR_PINK


#define GUI_WIDTH 			160
#define GUI_HEIGHT 			80

extern 	uint16_t GUI_BUF[GUI_HEIGHT][GUI_WIDTH];

void gui_reset(uint16_t* lcd_buf, uint16_t Color);
void gui_draw_axis(uint16_t* lcd_buf, uint16_t Color);
void gui_draw_wave(uint16_t* lcd_buf, uint8_t* wave_buf, uint16_t pos, float scale, uint16_t Color);
int32_t gui_draw_vline(uint16_t* lcd_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color);
int32_t gui_draw_hline(uint16_t* lcd_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color);
int32_t gui_draw_line(uint16_t* gui_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color);
int32_t gui_draw_rectangle(uint16_t* lcd_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color);
int32_t gui_draw_string(uint16_t* lcd_buf, uint16_t x,uint16_t y,
					uint16_t width,uint16_t height,uint8_t size,uint8_t *p);
void 	gui_draw_char(uint16_t* lcd_buf, uint16_t x,uint16_t y,uint8_t num,uint8_t size);
#endif /* GUI_H_ */
