#include "configure.h"
#include "global.h"
#include "displaylist.h"

#define NUMBER_OF_DISPLAY_LISTS 7

extern void Init_Display(SPI_LCD_HandleTypeDef* LcdHandler, uint8_t SpiIndex, color_mode_t colorMode);
extern void SetDisplayAddress(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE);
extern void SetDisplayOrientation(uint8_t orientation);
extern void ScreenClear(uint16_t color);
extern void DrawPixel(uint16_t X, uint16_t Y, uint16_t color);
extern void DrawHLine(uint16_t X1, uint16_t X2, uint16_t Y, uint16_t color);
extern void DrawVLine(uint16_t X, uint16_t Y1, uint16_t Y2, uint16_t color);
extern void DrawLine(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint16_t color);
extern void DrawRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
extern void FillRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
extern void DrawChar(uint16_t X, uint16_t Y, uint8_t chr, uint16_t color);
extern void DrawString(uint16_t X, uint16_t Y, char *str, uint16_t color);

void Format_Int(uint8_t row, void* info, uint16_t*);
void Format_Int16(uint8_t row, void* info, uint16_t*);
void Format_Hex8(uint8_t row, void* info, uint16_t*);
void Format_Hex16(uint8_t row, void* info, uint16_t*);
void Format_Hex32(uint8_t row, void* info, uint16_t*);
void Format_Ascii(uint8_t row, void* info, uint16_t*);
void Format_String(uint8_t row, void* info, uint16_t*);
void Format_Float3_3(uint8_t row, void* info, uint16_t*);
void Format_MemoryDumpAscii(uint8_t row, void* info, uint16_t*);
void Format_MemoryDumpHex(uint8_t row, void* info, uint16_t*);
void Format_Boolean(uint8_t row, void* info, uint16_t*);
void Format_Bar(uint8_t row, void* info, uint16_t*);
void Format_MemoryDumpAscii(uint8_t row, void* info, uint16_t*);

void WriteGuiBuffer(int row);
void UpdateScreen(SPI_LCD_HandleTypeDef*,LcdVariableInfo*);
void DisplayIndexIncrement();
void DisplayIndexDecrement();
