/*
 * gui.cpp
 *
 *  Created on: Jan 12, 2021
 *      Author: falcon
 */

#include "gui.h"
#include "lcd.h"
#include "constant.h"

void GuiReset(uint16_t* lcd_buf, uint16_t Color) {
	for(int i = 0; i < LCD_HEIGHT; i ++ )
	{
		for(int j = 0; j < LCD_WIDTH; j ++) {
			lcd_buf[i * LCD_WIDTH + j] = Color;
		}
	}
	//memset(lcd_buf, Color, LCD_WIDTH* LCD_HEIGHT * sizeof(uint16_t));
}
void GuiDrawAxis(uint16_t* lcd_buf, uint16_t Color)
{
	GuiDrawRectangle(lcd_buf, 0, 0, LCD_WIDTH-1, LCD_HEIGHT-1, Color);
	for(int i = 20; i < LCD_HEIGHT; i += 20)
		GuiDrawHLine(lcd_buf, 0, i, LCD_WIDTH, Color);
	for(int i = 20; i < LCD_WIDTH; i += 20)
			GuiDrawVLine(lcd_buf, i, 0, LCD_HEIGHT, Color);
}
int32_t GuiDrawRectangle(uint16_t* lcd_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color)
{
	uint32_t res = GUI_OK;
	res &= GuiDrawLine(lcd_buf, x1, y1, x1, y2, Color);
	res &= GuiDrawLine(lcd_buf, x1, y2, x2, y2, Color);
	res &= GuiDrawLine(lcd_buf, x2, y2, x2, y1, Color);
	res &= GuiDrawLine(lcd_buf, x2, y1, x1, y1, Color);
	return res;
}
void GuiDrawWave(uint16_t* lcd_buf, uint8_t* wave_buf, uint16_t pos, float scale, uint16_t Color)
{

	int16_t x = LCD_WIDTH-1;
	uint8_t y = 0;
	uint16_t end_pos = pos + 1;
	if(end_pos >= LCD_WIDTH) end_pos = 0;
	uint16_t prev_y = 0;
	int16_t prev_x = x;
	float original_scale = LCD_WIDTH/(float)ADC_SAMPLE_SIZE;

	for(int i = 0; i < ADC_SAMPLE_SIZE; i ++) {
		y = (uint8_t)(LCD_HEIGHT - (wave_buf[i]) /256.0 * LCD_HEIGHT) ;
		x = i * original_scale * 1;
		if(i != 0) GuiDrawLine(lcd_buf, prev_x, prev_y, x, y, Color);
		prev_y = y;
		prev_x = x;
	}
}


int32_t GuiDrawVLine(uint16_t* lcd_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color)
{
  int32_t ret = GUI_OK;
  uint32_t counter;
  if(Xpos >= LCD_WIDTH) return GUI_ERROR;
  for(counter = 0; counter < Length; counter++)
  {
	  if(Ypos + counter < LCD_HEIGHT) {
		  lcd_buf[(Ypos + counter) * LCD_WIDTH + Xpos] = Color;
	  }
  }

  return ret;
}


int32_t GuiDrawHLine(uint16_t* lcd_buf, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint16_t Color)
{
  int32_t ret = GUI_OK;
  uint32_t counter;
  if(Ypos >= LCD_HEIGHT) return GUI_ERROR;
  for(counter = 0; counter < Length; counter++)
  {
	  if(Xpos + counter < LCD_WIDTH)
	  {
		  lcd_buf[Ypos * LCD_WIDTH + (Xpos + counter)] = Color;
	  }
  }

  return ret;
}

int32_t GuiDrawLine(uint16_t* lcd_buf, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint16_t Color)
{
	int32_t ret = GUI_OK;
	float m = 0;
	if((x2 - x1 == 0) && (y2 - y1 == 0)) {
		if(x2 >= 0 && x2 < LCD_WIDTH && y2 >= 0 && y2 < LCD_HEIGHT) {
			lcd_buf[y2 * LCD_WIDTH + x2] = Color;
		}
	}
	if(x2 - x1 == 0 ) {
		GuiDrawVLine(lcd_buf, x1, _MIN(y1, y2), _ABS((int32_t)(y1 - y2)), Color);
		return ret;
	}else if(y2 - y1 == 0) {
		GuiDrawHLine(lcd_buf, _MIN(x1, x2), y1, _ABS((int32_t)(x1 - x2)), Color);
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
		if(i >= LCD_WIDTH) break;
		y = (uint16_t)((m * (i - x1) + y1) + 0.5);
		if(y >= 0 && y < LCD_HEIGHT) {
			uint16_t yindex = (uint16_t)(y * LCD_WIDTH);
			lcd_buf[yindex + i] = Color;
		}

	}
#endif
	return ret;
}

int32_t GuiDrawString(uint16_t* lcd_buf, uint16_t x,uint16_t y,
					uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{

	uint8_t x0=x;
	width+=x;
	height+=y;
	while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
	{
		if(x>=width){x=x0;y+=size;}
		if(y>=height)break;//�˳�
		GuiDrawChar(lcd_buf, x,y,*p,size);
		x+=size/2;
		p++;
	}
}

void GuiDrawChar(uint16_t* lcd_buf, uint16_t x,uint16_t y,uint8_t num,uint8_t size)
{
	uint8_t temp,t1,t;
	uint16_t y0=y;
	uint16_t x0=x;
	uint16_t colortemp = POINT_COLOR;
	uint32_t h,w;

	uint16_t write[size][size==12?6:8];
	uint16_t count;

	w = LCD_WIDTH;
	h = LCD_HEIGHT;

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
				uint16_t yindex = (uint16_t)((y0+count) * LCD_WIDTH);
				uint16_t xindex = x0 + t/2;
				lcd_buf[yindex + xindex] = POINT_COLOR;
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
