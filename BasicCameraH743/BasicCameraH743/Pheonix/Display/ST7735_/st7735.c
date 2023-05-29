#include "configure.h"
#if defined(ST7735) && defined(USE_LCD)
/* Includes ------------------------------------------------------------------*/
#include "st7735.h"
#include "Display/LcdDefinitions.h"
void ST7735_write(uint8_t data) {
#if defined(H_743) || defined(FK_750)
#ifdef ST7735_USE_DMA
	result = HAL_SPI_Transmit_DMA(SPI_Drv, pdata, length);
	while (SPI_Drv->State == HAL_SPI_STATE_BUSY_TX) ;
#else
	//HAL_SPI_Transmit(&ST7735X_SPI_PORT, buff, buff_size, HAL_MAX_DELAY);
	HAL_SPI_Transmit(SPI_Drv, &data, 1, 100);
#endif
#else	
	while (SPI_I2S_GetFlagStatus(SPI_Drv,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI_Drv,data);
#endif	
}

void ST7735_cmd(uint8_t cmd) {
	LCD_RS_CLR;//A0_L();
	ST7735_write(cmd);
#if defined(H_743) || defined(FK_750)
#else
	while (SPI_I2S_GetFlagStatus(SPI_Drv,SPI_I2S_FLAG_BSY) == SET);
#endif	
}

void ST7735_data(uint8_t data) {
	LCD_RS_SET;//A0_H();
	ST7735_write(data);
#if defined(H_743) || defined(FK_750)
#else
	while (SPI_I2S_GetFlagStatus(SPI_Drv,SPI_I2S_FLAG_BSY) == SET);
#endif
}
void ST7735_Orientation(ScrOrientation_TypeDef orientation) {
	LCD_CS_CLR;// CS_L();
	ST7735_cmd(0x36); // Memory data access control:
	ST7735_data(0xA8);
//	switch(orientation) {
//	case scr_CW:
//		ST7735_data(0xA0); // X-Y Exchange,Y-Mirror
//		break;
//	case scr_CCW:
//		ST7735_data(0x60); // X-Y Exchange,X-Mirror
//		break;
//	case scr_180:
//		ST7735_data(0xc0); // X-Mirror,Y-Mirror: Bottom to top; Right to left; RGB
//		break;
//	default:
//		ST7735_data(0x00); // Normal: Top to Bottom; Left to Right; RGB
//		break;
//	}
	LCD_CS_SET; //CS_H();
}

void ST7735_SetAddress(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE) {
	ST7735_cmd(0x2a); // Column address set
#ifdef ST7735_160_80_LANDSCAPE
	XE += 1;
	YE += 26;
#endif
	LCD_RS_SET;// A0_H();
	ST7735_write(XS >> 8);
	ST7735_write(XS);
	ST7735_write(XE >> 8);
	ST7735_write(XE);

	ST7735_cmd(0x2b); // Row address set
	LCD_RS_SET; //A0_H();
	ST7735_write(YS >> 8);
	ST7735_write(YS);
	ST7735_write(YE >> 8);
	ST7735_write(YE);

	ST7735_cmd(0x2c); // Memory write
}

void ST7735_WriteBuff(uint16_t *DataBuff, uint16_t DataSize)
{
	
	for (uint16_t i = 0; i < DataSize; i++)
	{
		uint16_t color = DataBuff[i];
		ST7735_write(color >> 8);
		ST7735_write(color & 0xFF);
	}
}

void ST7735_FillRGBRect(uint32_t Xpos, uint32_t Ypos, uint16_t *pData, uint32_t Width, uint32_t Height)
{
  uint16_t *rgb_data = pData;
  uint32_t i, j;
  uint8_t  CH,CL;


  for(j = 0; j < Height; j ++)
  {
	  rgb_data = pData + (MAX_LCD_SIZE * j * 2);
	  LCD_CS_CLR;
	  ST7735_SetAddress(Xpos, Ypos + j, Xpos+Width, Ypos + j +1);
	  LCD_RS_SET;
	  for(i = 0; i < Width; i++)
	  {
		  CH = (*rgb_data) >> 8;
		  CL = (uint8_t)(*rgb_data);
		  ST7735_write(CL);
		  ST7735_write(CH);
		  
		  rgb_data ++;
	  }
	  LCD_CS_SET;
  }
}
void ST7735_Clear(uint16_t color) {
	uint16_t i;
	uint8_t  CH,CL;

	CH = color >> 8;
	CL = (uint8_t)color;

	LCD_CS_CLR;
	ST7735_SetAddress(0,0,LCD_WIDTH - 1,LCD_HEIGHT - 1);
	LCD_RS_SET;
	for (i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
		ST7735_write(CL);
		ST7735_write(CH);
	}
	LCD_CS_SET;
}
void ST7735_Init()
{
	LCD_CS_SET;
	LCD_RST_SET;
	Delay_ms(5);
	LCD_RST_CLR;
	Delay_ms(5);
	LCD_RST_SET;
	LCD_CS_SET;
	Delay_ms(5);
	LCD_CS_CLR;

	ST7735_cmd(0x11); // Sleep out & booster on
	Delay_ms(20); // Datasheet says what display wakes about 120ms (may be much faster actually)

	ST7735_cmd(0xb1);   // In normal mode (full colors):
	LCD_RS_SET;
	ST7735_write(0x01U); //   RTNA set 1-line period: RTNA2, RTNA0 -- 0x05
	ST7735_write(0x2CU); //   Front porch: FPA5,FPA4,FPA3,FPA2  --0x3c
	ST7735_write(0x2DU); //   Back porch: BPA5,BPA4,BPA3,BPA2   --0x3c

	ST7735_cmd(0xb2);   // In idle mode (8-colors):
	LCD_RS_SET;
	ST7735_write(0x01U); //   RTNA set 1-line period: RTNA2, RTNA0 -- 0x05
	ST7735_write(0x2CU); //   Front porch: FPA5,FPA4,FPA3,FPA2  --0x3c
	ST7735_write(0x2DU); //   Back porch: BPA5,BPA4,BPA3,BPA2   --0x3c


	ST7735_cmd(0xb3);   // In partial mode + full colors:
	LCD_RS_SET;
	ST7735_write(001U); //   RTNC set 1-line period: RTNC2, RTNC0  -- 0x05
	ST7735_write(0x2CU); //   RTNC set 1-line period: RTNC2, RTNC0  -- 0x05
	ST7735_write(0x2DU); //   Front porch: FPC5,FPC4,FPC3,FPC2   --0x3c
	ST7735_write(0x01U); //   Back porch: BPC5,BPC4,BPC3,BPC2   --0x3c
	ST7735_write(0x2CU); //   RTND set 1-line period: RTND2, RTND0 --0x2CU
	ST7735_write(0x2DU); //   Front porch: FPD5,FPD4,FPD3,FPD2  --0x2DU
	


	ST7735_cmd(0xB4);   // Display dot inversion control:
	ST7735_data(0x07);  // NLB,NLC  ---0x03

	/* Power control, 3 args, no delay: -4.6V , AUTO mode */
	ST7735_cmd(0xC0U);
	ST7735_data(0xA2U);
	ST7735_data(0x02U);
	ST7735_data(0x84U);
	

	/* Power control, 1 arg, no delay: VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD */
	ST7735_cmd(0xC1U);
	ST7735_data(0xC5U);
	/* Power control, 2 args, no delay: Opamp current small, Boost frequency */
	ST7735_cmd(0xC2U);
	ST7735_data(0x0AU);
	ST7735_data(0x00U);	
	/* Power control, 2 args, no delay: BCLK/2, Opamp current small & Medium low */
	ST7735_cmd(0xC3U);
	ST7735_data(0x8AU);
	ST7735_data(0x2AU);
	
	/* Power control, 2 args, no delay */
	ST7735_cmd(0xC4U);
	ST7735_data(0x8AU);
	ST7735_data(0xEEU);
	
	/* Power control, 1 arg, no delay */
	ST7735_cmd(0xC5U);
	ST7735_data(0x0EU);
	
	/* display inversion on/off */
	ST7735_cmd(0x20U);  //0x21U 
	
	/* Set color mode, 1 arg, no delay */
	ST7735_cmd(0x3AU); 
	ST7735_data(0x02U); //RGB565
	
	/* Magical unicorn dust, 16 args, no delay */
	ST7735_cmd(0xE0U); //ST7735_PV_GAMMA_CTRL
	ST7735_data(0x02U);
	ST7735_data(0x1CU);
	ST7735_data(0x07U);
	ST7735_data(0x12U);
	ST7735_data(0x37U);
	ST7735_data(0x32U);
	ST7735_data(0x29U);
	ST7735_data(0x2DU);
	ST7735_data(0x29U);
	ST7735_data(0x25U);
	ST7735_data(0x2BU);
	ST7735_data(0x39U);
	ST7735_data(0x00U);
	ST7735_data(0x01U);
	ST7735_data(0x03U);
	ST7735_data(0x10U);
	ST7735_data(0x00U);
	
	/* Sparkles and rainbows, 16 args, no delay */
	ST7735_cmd(0xE1U); //ST7735_NV_GAMMA_CTRL
	ST7735_data(0x03U);
	ST7735_data(0x1DU);
	ST7735_data(0x07U);
	ST7735_data(0x06U);
	ST7735_data(0x2EU);
	ST7735_data(0x2CU);
	ST7735_data(0x29U);
	ST7735_data(0x2DU);
	ST7735_data(0x2EU);
	ST7735_data(0x2EU);
	ST7735_data(0x37U);
	ST7735_data(0x3FU);
	ST7735_data(0x00U);
	ST7735_data(0x00U);
	ST7735_data(0x02U);
	ST7735_data(0x10U);
	
	ST7735_cmd(0x13); // Partial mode off
	ST7735_data(0x00U);
	ST7735_cmd(0x29); // Display on
	ST7735_data(0x00U);
//	
//	ST7735_cmd(0x3a);   // Interface pixel format
////	ST7735_data(0x03);  // 12-bit/pixel RGB 4-4-4 (4k colors)
//	ST7735_data(0x05);  // 16-bit/pixel RGB 5-6-5 (65k colors)
////	ST7735_data(0x06);  // 18-bit/pixel RGB 6-6-6 (256k colors)
//	ST7735_cmd(0x20);
//	//if(COLOR_MODE != COLOR_MODE_INVERT)	ST7735_cmd(0x20);   // Display inversion off
//	//else ST7735_cmd(0x21);   // Display inversion on
//
//
//
//	ST7735_cmd(0x13);   // Partial mode off
//
//	ST7735_cmd(0x26);   // Gamma curve set:
//	ST7735_data(0x01);  //   Gamma curve 1 (G2.2) or (G1.0)
//	ST7735_cmd(0x29);   // Display on

	LCD_CS_SET;

	//ST7735_Orientation(scr_CW);
	ST7735_Clear(BLUE);
}
#endif
