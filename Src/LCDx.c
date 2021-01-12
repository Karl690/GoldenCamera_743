#include "main.h"
#include "lcd.h"
#include "st7735x.h"
#include "hyrel3d_logo_128x128.h"
void LCDx_Init(void)
{
	ST7735x_Init();
	LCDx_DisplayOnOf(true);
}
void LCDx_Hyrellogo(void)
{
    // Display test image 128x128
    extern const uint16_t hyrel3d_logo_128x128[128][128];
    ST7735x_FillRectangle(0, 0, 128, 128, ST7735X_BLUE);
    //ST7735x_DrawImage(0, 0, ST7735X_WIDTH, ST7735X_HEIGHT, (uint16_t*)hyrel3d_logo_128x128);
}

void LCDx_DisplayOnOf(bool OnOff) {
	if(OnOff == true)
		SetPinStatus(LCD2_GPIO_BKLT_GPIO_Port, LCD2_GPIO_BKLT_Pin, GPIO_PIN_SET);
	else
		SetPinStatus(LCD2_GPIO_BKLT_GPIO_Port, LCD2_GPIO_BKLT_Pin, GPIO_PIN_RESET);
}
