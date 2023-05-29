#include <stdint.h>
#include "lcddefinitions.h"
#define GUI_OK 		1
#define GUI_ERROR 	0



#define GUI_COLOR_BACKGROUND 		0x6101
#define GUI_COLOR_AXIS				0x2203
#define GUI_COLOR_GREEN				0xE707
#define GUI_COLOR_YELLOW			0xE0CF
#define GUI_COLOR_PINK				0x1FF8

#define GUI_COLOR_ADC_CHANNEL_01	GUI_COLOR_GREEN
#define GUI_COLOR_ADC_CHANNEL_02	GUI_COLOR_PINK


#define ABS(a) 		(a > 0? a: -a)
extern 	uint16_t GUI_BUF[LCD_HEIGHT][MAX_LCD_SIZE];

//void gui_reset(uint16_t Color);
//void gui_draw_axis(uint16_t Color);
//void gui_draw_wave(uint8_t* wave_buf, uint16_t buf_size, uint16_t pos, float scale, uint16_t Color);
//int32_t gui_draw_vline(uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color);
//int32_t gui_draw_hline(uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color);
//int32_t gui_draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color);
//int32_t gui_draw_rectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color);
//int32_t gui_draw_string(uint16_t x,uint16_t y, uint16_t width,uint16_t height,uint8_t size,uint8_t *p, uint16_t Color);
//void 	gui_draw_char(uint16_t x,uint16_t y,uint8_t num,uint8_t size, uint16_t Color);

void ResetGuiBuffer(uint16_t color);
void DrawPixel(uint16_t X, uint16_t Y, uint16_t color);
void DrawHLine(uint16_t X1, uint16_t X2, uint16_t Y, uint16_t color);
void DrawVLine(uint16_t X, uint16_t Y1, uint16_t Y2, uint16_t color);
void DrawLine(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint16_t color);
void DrawRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
void FillRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
void DrawChar(uint16_t X, uint16_t Y, uint8_t chr, uint16_t color);
void DrawString(uint16_t X, uint16_t Y, char *str, uint16_t color);
void FillRectBuffer(uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, uint8_t* buf);
