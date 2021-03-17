/*
 * gui.cpp
 *
 *  Created on: Jan 12, 2021
 *      Author: falcon
 */

#include "gui.h"
#include "lcd.h"
#include "constant.h"

uint16_t 		GUI_BUF[GUI_HEIGHT][GUI_WIDTH];

void gui_reset(uint16_t* gui_buf, uint16_t Color) {
	for(int i = 0; i < GUI_HEIGHT; i ++ )
	{
		for(int j = 0; j < GUI_WIDTH; j ++) {
			gui_buf[i * GUI_WIDTH + j] = Color;
		}
	}
	//memset(lcd_buf, Color, LCD_WIDTH* LCD_HEIGHT * sizeof(uint16_t));
}
void gui_draw_axis(uint16_t* gui_buf, uint16_t Color)
{
	gui_draw_rectangle(gui_buf, 0, 0, GUI_WIDTH-1, GUI_HEIGHT-1, Color);
	for(int i = 20; i < GUI_HEIGHT; i += 20)
		gui_draw_hline(gui_buf, 0, i, GUI_WIDTH, Color);
	for(int i = 20; i < GUI_WIDTH; i += 20)
		gui_draw_hline(gui_buf, i, 0, GUI_HEIGHT, Color);
}
int32_t gui_draw_rectangle(uint16_t* gui_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color)
{
	uint32_t res = GUI_OK;
	res &= gui_draw_line(gui_buf, x1, y1, x1, y2, Color);
	res &= gui_draw_line(gui_buf, x1, y2, x2, y2, Color);
	res &= gui_draw_line(gui_buf, x2, y2, x2, y1, Color);
	res &= gui_draw_line(gui_buf, x2, y1, x1, y1, Color);
	return res;
}
void gui_draw_wave(uint16_t* gui_buf, uint8_t* wave_buf, uint16_t pos, float scale, uint16_t Color)
{

	int16_t x = GUI_WIDTH-1;
	uint8_t y = 0;
	uint16_t end_pos = pos + 1;
	if(end_pos >= GUI_WIDTH) end_pos = 0;
	uint16_t prev_y = 0;
	int16_t prev_x = x;
	float original_scale = GUI_WIDTH/(float)ADC_SAMPLE_SIZE;

	for(int i = 0; i < ADC_SAMPLE_SIZE; i ++) {
		y = (uint8_t)(GUI_HEIGHT - (wave_buf[i]) /256.0 * GUI_HEIGHT) ;
		x = i * original_scale * 1;
		if(i != 0) gui_draw_line(gui_buf, prev_x, prev_y, x, y, Color);
		prev_y = y;
		prev_x = x;
	}
}


int32_t gui_draw_hline(uint16_t* gui_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color)
{
  int32_t ret = GUI_OK;
  uint32_t counter;
  if(Xpos >= GUI_WIDTH) return GUI_ERROR;
  for(counter = 0; counter < Length; counter++)
  {
	  if(Ypos + counter < GUI_HEIGHT) {
		  gui_buf[(Ypos + counter) * GUI_WIDTH + Xpos] = Color;
	  }
  }

  return ret;
}


int32_t gui_draw_vline(uint16_t* gui_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color)
{
  int32_t ret = GUI_OK;
  uint32_t counter;
  if(Ypos >= GUI_HEIGHT) return GUI_ERROR;
  for(counter = 0; counter < Length; counter++)
  {
	  if(Xpos + counter < GUI_WIDTH)
	  {
		  gui_buf[Ypos * GUI_WIDTH + (Xpos + counter)] = Color;
	  }
  }

  return ret;
}

int32_t gui_draw_line(uint16_t* gui_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color)
{
	int32_t ret = GUI_OK;
	float m = 0;
	if((x2 - x1 == 0) && (y2 - y1 == 0)) {
		if(x2 >= 0 && x2 < GUI_WIDTH && y2 >= 0 && y2 < GUI_HEIGHT) {
			gui_buf[y2 * GUI_WIDTH + x2] = Color;
		}
	}
	if(x2 - x1 == 0 ) {
		gui_draw_vline(gui_buf, x1, _MIN(y1, y2), _ABS((int32_t)(y1 - y2)), Color);
		return ret;
	}else if(y2 - y1 == 0) {
		gui_draw_hline(gui_buf, _MIN(x1, x2), y1, _ABS((int32_t)(x1 - x2)), Color);
		return ret;
	}
#ifndef _NN_
	m = (y2- y1) /(float)(x2 - x1);
	uint32_t xstart, xend;
	uint16_t y = 0;
	xstart = _MIN(x1, x2);
	xend = _MAX(x1, x2);

	for(uint32_t i = xstart; i < xend; i ++)
	{
		if(i < 0) break;
		if(i >= GUI_WIDTH) break;
		y = (uint16_t)((m * (i - x1) + y1) + 0.5);
		if(y >= 0 && y < GUI_HEIGHT) {
			uint16_t yindex = (uint16_t)(y * GUI_WIDTH);
			gui_buf[yindex + i] = Color;
		}
	}
#endif
	return ret;
}

int32_t gui_draw_string(uint16_t* gui_buf, uint16_t x,uint16_t y,
					uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{

	uint8_t x0=x;
	width+=x;
	height+=y;
	while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
	{
		if(x>=width){x=x0;y+=size;}
		if(y>=height)break;//�˳�
		gui_draw_char(gui_buf, x,y,*p,size);
		x+=size/2;
		p++;
	}
}

void gui_draw_char(uint16_t* gui_buf, uint16_t x,uint16_t y,uint8_t num,uint8_t size)
{
	uint8_t temp,t1,t;
	uint16_t y0=y;
	uint16_t x0=x;
	uint16_t colortemp = POINT_COLOR;
	uint32_t h,w;

	uint16_t write[size][size==12?6:8];
	uint16_t count;

	w = GUI_WIDTH;
	h = GUI_HEIGHT;

	num=num-' ';
	count = 0;
	extern const unsigned char asc2_1206[95][12];
	extern const unsigned char asc2_1608[95][16];
	for(t=0;t<size;t++)
	{
		if(size==12)temp=asc2_1206[num][t];  //����1206����
		else temp=asc2_1608[num][t];		 //����1608����

		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)
			{
				uint16_t yindex = (uint16_t)((y0+count) * GUI_WIDTH);
				uint16_t xindex = x0 + t/2;
				gui_buf[yindex + xindex] = POINT_COLOR;
			}else {

			}
			count ++;
			if(count >= size) count =0;

			temp<<=1;
			y++;
			if(y>=h)
			{
				return;
			}
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=w)
				{
					return;
				}
				break;
			}
		}
	}
}
