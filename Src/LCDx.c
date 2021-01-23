#include "main.h"
#include "lcdx.h"
#include "st7735x.h"
#include "hyrel3d_logo_128x128.h"
void lcdx_init(void)
{
	ST7735X_Init();
	lcdx_displayonoff(true);
}
void lcdx_logo(void)
{
    // Display test image 128x128
    extern const uint16_t hyrel3d_logo_128x128[128][128];
    ST7735X_FillRectangle(0, 0, ST7735X_HEIGHT, ST7735X_WIDTH, ST7735X_YELLOW);
    //ST7735X_DrawImage(0, 0, ST7735X_HEIGHT, ST7735X_WIDTH, (uint16_t*)hyrel3d_logo_160x80);
}

void lcdx_displayonoff(bool OnOff) {
	if(OnOff == true)
		HAL_GPIO_WritePin(LCD_BK_GPIO_Port, LCD_BK_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_BK_GPIO_Port, LCD_BK_Pin, GPIO_PIN_RESET);
}
