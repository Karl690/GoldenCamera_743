#include "lcd.h"
//SPI��ʾ���ӿ�
#define TFT96
//LCD_RST
//#define LCD_RST_SET     
//#define LCD_RST_RESET  
//LCD_RS//dc  
//#define LCD_RS_SET      HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_SET)//PC4 
//#define LCD_RS_RESET    HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_RESET)
//LCD_CS  
//#define LCD_CS_SET      HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET)
//#define LCD_CS_RESET    HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET)
//SPI Driver
//#define SPI spi4
//#define SPI_Drv (&hspi4)
#define delay_ms HAL_Delay
#define get_tick HAL_GetTick
//LCD_Brightness timer
//#define LCD_Brightness_timer &htim1
//#define LCD_Brightness_channel TIM_CHANNEL_2

static int32_t lcd_init(void);
static int32_t lcd_gettick(void);
static int32_t lcd_writereg(uint8_t reg,uint8_t* pdata,uint32_t length);
static int32_t lcd_readreg(uint8_t reg,uint8_t* pdata);
static int32_t lcd_senddata(uint8_t* pdata,uint32_t length);
static int32_t lcd_recvdata(uint8_t* pdata,uint32_t length);

ST7735_IO_t st7735_pIO = {
	lcd_init,
	NULL,
	NULL,
	lcd_writereg,
	lcd_readreg,
	lcd_senddata,
	lcd_recvdata,
	lcd_gettick
};

ST7735_Object_t st7735_pObj;
uint32_t 		st7735_id;

void LCD_Test(void)
{
	uint8_t text[20];
	
	#ifdef TFT96
	ST7735Ctx.Orientation = ST7735_ORIENTATION_LANDSCAPE_ROT180;
	ST7735Ctx.Panel = HannStar_Panel;
	ST7735Ctx.Type = ST7735_0_9_inch_screen;
	#elif TFT18
	ST7735Ctx.Orientation = ST7735_ORIENTATION_PORTRAIT;
	ST7735Ctx.Panel = BOE_Panel;
	ST7735Ctx.Type = ST7735_1_8_inch_screen;
	#else
	printf("Unknown Screen");
	
	#endif
	
	ST7735_RegisterBusIO(&st7735_pObj,&st7735_pIO);
	ST7735_LCD_Driver.Init(&st7735_pObj,ST7735_FORMAT_RBG565,&ST7735Ctx);
	ST7735_LCD_Driver.ReadID(&st7735_pObj,&st7735_id);
	
	#ifdef TFT96
	//extern unsigned char WeActStudiologo_160_80[];
	extern unsigned char Hyrel3Dlogo_160_80[];
	ST7735_LCD_Driver.DrawBitmap(&st7735_pObj,0,0,Hyrel3Dlogo_160_80);
	#elif TFT18
	extern unsigned char WeActStudiologo_128_160[];
	ST7735_LCD_Driver.DrawBitmap(&st7735_pObj,0,0,WeActStudiologo_128_160);
	#endif
//	int timeout = 2000;
//	uint32_t tick = get_tick();
//	while (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) != GPIO_PIN_SET)
//	{
//		delay_ms(10);
//
//		if (get_tick() - tick <= 1000)
//			LCD_SetBrightness((get_tick() - tick) * 100 / 1000);
//		else if (get_tick() - tick <= timeout)
//		{
//			sprintf((char *)&text, "%03d", (get_tick() - tick - 1000) / 10);
//			LCD_ShowString(ST7735Ctx.Width - 30, 1, ST7735Ctx.Width, 16, 16, text);
//			ST7735_LCD_Driver.FillRect(&st7735_pObj, 0, ST7735Ctx.Height - 3, (get_tick() - tick - 1000) * ST7735Ctx.Width / (timeout-1000), 3, 0xFFFF);
//		}
//		else if (get_tick() - tick > timeout)
//			break;
//	}
//	LCD_Light(600, 300);
}

void lcd_fillRect(int xpos, int ypos, int width, int height, uint8_t *buf)
{
	ST7735_LCD_Driver.FillRGBRect(&st7735_pObj, xpos, ypos, buf, width, height);
}
	
uint16_t POINT_COLOR=0xFFFF;
uint16_t BACK_COLOR=BLACK;


static int32_t lcd_init(void)
{
	int32_t result = ST7735_OK;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	return result;
}

static int32_t lcd_gettick(void)
{
	return HAL_GetTick();
}

static int32_t lcd_writereg(uint8_t reg,uint8_t* pdata,uint32_t length)
{
	int32_t result;
	LCD_CS_CLR;
	LCD_RS_CLR;
	result = HAL_SPI_Transmit(SPI_Drv,&reg,1,100);
	LCD_RS_SET;
	if(length > 0)
		result += HAL_SPI_Transmit(SPI_Drv,pdata,length,500);
	LCD_CS_SET;
	//result /= -result;
	return result;
}

static int32_t lcd_readreg(uint8_t reg,uint8_t* pdata)
{
	int32_t result;
	LCD_CS_CLR;
	LCD_RS_CLR;
	
	result = HAL_SPI_Transmit(SPI_Drv,&reg,1,100);
	LCD_RS_SET;
	result += HAL_SPI_Receive(SPI_Drv,pdata,1,500);
	LCD_CS_SET;
	//result /= -result;
	return result;
}

static int32_t lcd_senddata(uint8_t* pdata,uint32_t length)
{
	int32_t result;
	LCD_CS_CLR;
	//LCD_RS_SET;

#ifdef ST7735_USE_DMA
	result = HAL_SPI_Transmit_DMA(SPI_Drv, pdata, length);
	while(SPI_Drv->State == HAL_SPI_STATE_BUSY_TX);
#else
	//HAL_SPI_Transmit(&ST7735X_SPI_PORT, buff, buff_size, HAL_MAX_DELAY);
	result =HAL_SPI_Transmit(SPI_Drv,pdata,length,100);
#endif

	LCD_CS_SET;
	//result /= -result;
	return result;
}

static int32_t lcd_recvdata(uint8_t* pdata,uint32_t length)
{
	int32_t result;
	LCD_CS_CLR;
	//LCD_RS_SET;
	result = HAL_SPI_Receive(SPI_Drv,pdata,length,500);
	LCD_CS_SET;
	//result /= -result;
	return result;
}

