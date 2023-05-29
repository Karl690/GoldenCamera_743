#include "global.h"
#include "configure.h"
#include "display.h"
#include "lcddefinitions.h"
//#include "displaylist.h"
#include "gui.h"
#include "colortables.h"
#include "taskmanager.h"
//#include "Communication/messages.h"
//#include "Execution/cmdprocessor.h"
//#include "Execution/Sequencer.h"
//#include "Communication/serial.h"

char strTempVal[80] = {0};
uint16_t idx = 0;
LcdVariableInfo *varInfo  = NULL;
LcdVariableInfo CmdQuVars = {0};
char* tempstring2 = "karl is lucky";
void WriteGuiBuffer(int row)
{
#ifdef H_743
	FillRGBRect(0,0, LCD_WIDTH , LCD_HEIGHT , &GUI_BUF[0][0]);
#else
	FillRGBRect(row, LCD_HEIGHT, &GUI_BUF[0][0]);
#endif
}
void Format_Int32(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING,varInfo->Label, colorTable[varInfo->Color_1]);
	sprintf(strTempVal, "%d ", (int)(*((uint32_t*)varInfo->VariablePointer)));
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}
void Format_Int16(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING,varInfo->Label, colorTable[varInfo->Color_1]);
	sprintf(strTempVal, "%d ", (int)(*((uint16_t*)varInfo->VariablePointer)));
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

void Format_Hex8(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);
	sprintf(strTempVal, "0x%02x ", (uint8_t)(*((uint8_t*)varInfo->VariablePointer)));
	DrawString(LCD_WIDTH/2, PADDING, strTempVal, colorTable[varInfo->Color_2]);

}
void Format_Hex16(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);
	sprintf(strTempVal, "0x%04x ", (uint16_t)(*((uint16_t*)varInfo->VariablePointer)));
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);

}
void Format_Hex32(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);
	sprintf(strTempVal, "0x%08x ", (int)(*((uint32_t*)varInfo->VariablePointer)));
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

void Format_Ascii(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);//label?
	sprintf(strTempVal, "%s ", (uint8_t*)(uint32_t*)(varInfo->VariablePointer));
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

void Format_Float3_3(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING,varInfo->Label, colorTable[varInfo->Color_1]);//label
	sprintf(strTempVal, "%.3f ", (float)(*((float*)varInfo->VariablePointer)));
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}
void Format_Float_QueVar(uint8_t row, void* info, uint16_t* colorTable)
{
//	varInfo = (LcdVariableInfo*)info;
//	uint32_t addressOfVariableToDisplay = CmdQueDisplayOffset + varInfo->VariablePointer;
//
//	DrawString(LEFT_PADDING, PADDING,varInfo->Label, colorTable[varInfo->Color_1]);//label
//	sprintf(strTempVal, "%.3f ", (float)(*((float*)addressOfVariableToDisplay)));
//	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

//void Format_MemoryDumpAscii(uint8_t row, void* info)
//{
//	varInfo = (LcdVariableInfo*)info;
//	DrawString(LEFT_PADDING, PADDING + (row * LCD_LINESIZE), varInfo->Label, varInfo->Color_1);//label?
//	sprintf(strTempVal, "%s ", varInfo->VariablePointer);
//	DrawString(VALUE_POS, PADDING + (row * LCD_LINESIZE), strTempVal, varInfo->Color_2);
//}

void Format_MemoryDumpAscii(uint8_t row, void* info, uint16_t* colorTable)
{
	int index=0;
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);
	uint8_t* MemoryDumpPointer = 0;
	if(varInfo->Offset) MemoryDumpPointer = (uint8_t*)((uint32_t**)(varInfo->VariablePointer));
	else MemoryDumpPointer = (uint8_t*)(*((uint32_t**)(varInfo->VariablePointer)));

	if(!MemoryDumpPointer)  return;
	strTempVal[0]=' ';
	strTempVal[1]=' ';
	for (index=2;index<22;index++)
	{
		strTempVal[index] = *MemoryDumpPointer;
		if(strTempVal[index]<0x1f)strTempVal[index]=' ';
		MemoryDumpPointer++;
	}
	strTempVal[index+1]=0;
	DrawString(LCD_WIDTH/2, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}
void Format_MemoryDisplayAscii(uint8_t row, void* info, uint16_t* colorTable)
{
	int index=0;
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);
	uint8_t* MemoryDumpPointer = (uint8_t*)varInfo->VariablePointer;
//	if(varInfo->Offset) MemoryDumpPointer = varInfo->VariablePointer;
//	else MemoryDumpPointer = *((uint32_t**)(varInfo->VariablePointer));

	if(!MemoryDumpPointer)  return;
	strTempVal[0]=' ';
	strTempVal[1]=' ';
	for (index=2;index<22;index++)
	{
		strTempVal[index] = *MemoryDumpPointer;
		if(strTempVal[index]<0x1f)strTempVal[index]=' ';
		MemoryDumpPointer++;
	}
	strTempVal[index+1]=0;
	DrawString(LCD_WIDTH/2, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}


void Format_MemoryDisplayAsciiHex(uint8_t row, void* info, uint16_t* colorTable)
{
	int index = 0;	
	char workChar = 0;
	char workstring[9] = "        "; //dummy empty string
	uint8_t* MemoryDumpPointer = (uint8_t*)varInfo->VariablePointer;
	char* temp = strTempVal;
	memset(strTempVal, 0, 40);
	for (int count = 0; count < 8; count++)
	{
		//if (*MemoryDumpPointer > 0x20)
		workChar = *(MemoryDumpPointer + count);
		if ((workChar <= '~')&&(workChar >= ' '))
		{
			workstring[count] = workChar;	
		}
		else
		{
			workstring[count] = '-';	
		}
		sprintf(temp, "%02X ", workChar);
		temp += 3;
		
	}
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, workstring, colorTable[varInfo->Color_2]);

	DrawString(LCD_WIDTH * 0.33f, PADDING, strTempVal, colorTable[varInfo->Color_2]);
	
}
void Format_MemoryDumpHex(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	memset(strTempVal, 0, 40);
	char* temp = strTempVal;
	uint8_t* soapHex = (uint8_t*)(varInfo->VariablePointer + varInfo->Offset);
	for(idx = 0; idx < 8; idx ++) {
		sprintf(temp, "%02X ", soapHex[idx]);
		temp += 3;
	}
	DrawString(LEFT_PADDING, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

void Format_Boolean(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING,varInfo->Label, colorTable[varInfo->Color_1]);
	sprintf(strTempVal, "%s ", (*(uint8_t*)varInfo->VariablePointer) == 0?"False":"True");
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}
void Format_Bar_Dutty(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t val = *(uint16_t*)varInfo->VariablePointer;
	uint32_t Divisor = *(uint32_t*)varInfo->Offset; //get the scaler part
	if(Divisor)val/=Divisor;//use the Offset for a way to scale the value to 0-100
	if(val > 100) val = 100;
	float percentON = (float)(val * 0.01) ;//lets see how much ON time we have
	/*   |=====60%==|==40%==| */
	/*   X1========X2====X3*/

	DrawString(LEFT_PADDING, PADDING,varInfo->Label, colorTable[varInfo->Color_1]);

	uint16_t X1 = VALUE_POS;
	uint16_t X2 = VALUE_POS + percentON * (LCD_WIDTH - VALUE_POS - RIGHT_PADDING); //Screen Width -Left padding - Right Padding
	uint16_t X3 = LCD_WIDTH - RIGHT_PADDING;
	if(X2 > X1)	FillRect(X1, PADDING, X2, LCD_LINESIZE-PADDING, colorTable[varInfo->Color_2]);
	if(X3 > X2) FillRect(X2, PADDING, X3, LCD_LINESIZE-PADDING, colorTable[COLOR_GRAY]);
	sprintf(strTempVal, "%d%s", val, "%");
	DrawString((X1 + X3)/2, PADDING, strTempVal, colorTable[varInfo->Color_1]);

}
void Format_Bar_Status(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	uint8_t val = *(uint8_t*)varInfo->VariablePointer;
	DrawString(LEFT_PADDING, PADDING,varInfo->Label, colorTable[varInfo->Color_1]);
	uint16_t X1 = VALUE_POS;
	uint16_t X2 = LCD_WIDTH - RIGHT_PADDING;
	if(val) {
		FillRect(X1, PADDING, X2, LCD_LINESIZE-PADDING, colorTable[varInfo->Color_2]);
	}else {
		FillRect(X1, PADDING, X2, LCD_LINESIZE-PADDING, colorTable[COLOR_GRAY]);
	}
	sprintf(strTempVal, "%d", val);
	DrawString((X1 + X2)/2, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

void Format_Bar_Float(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	float val = *(float*)varInfo->VariablePointer;
	float max = *(float*)varInfo->Offset;
	if(val > max) val = max;
	float percentON = val / max ;//lets see how much ON time we have
	/*   |=====60%==|==40%==| */
	/*   X1========X2====X3*/
	uint16_t X1 = VALUE_POS;
	uint16_t X2 = VALUE_POS + percentON * (LCD_WIDTH - VALUE_POS - RIGHT_PADDING); //Screen Width -Left padding - Right Padding
	uint16_t X3 = LCD_WIDTH - RIGHT_PADDING;

	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);

	if(X2 > X1)	FillRect(X1, PADDING, X2, LCD_LINESIZE-PADDING, colorTable[varInfo->Color_2]);
	if(X3 > X2) FillRect(X2, PADDING, X3, LCD_LINESIZE-PADDING, colorTable[COLOR_GRAY]); //BLACK);//

	sprintf(strTempVal, "%.3f", val);
	DrawString((X1 + X3)/2 - 10, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

void Format_SoapStringWithIndex(uint8_t row, void* info, uint16_t* colorTable)
{
	varInfo = (LcdVariableInfo*)info;
	uint8_t* soap = (uint8_t*)varInfo->VariablePointer;
	uint16_t index = varInfo->Offset;
	uint16_t k = 0, p = 0;
	uint16_t delimeter_cnt = 0;
	memset(strTempVal, 0, 40);
	while(soap[k] != 0 && soap[k] != 0xff) //loop until end of string
	{
		if(delimeter_cnt == index && (soap[k] != ',' && soap[k] != '\n') )
		{
			strTempVal[p] = soap[k];
			p ++;
		}
		if(soap[k] == ',' || soap[k] == '\n') delimeter_cnt ++;
		if(delimeter_cnt > index) break;
		k ++;
	}
	varInfo = (LcdVariableInfo*)info;
	DrawString(LEFT_PADDING, PADDING, varInfo->Label, colorTable[varInfo->Color_1]);//label?
	DrawString(VALUE_POS, PADDING, strTempVal, colorTable[varInfo->Color_2]);
}

/////////////////////////////////////////////////////////////////////////////////
void UpdateScreen(SPI_LCD_HandleTypeDef* LcdHandler, LcdVariableInfo* InfoToDisplay)
{
	uint16_t row = 0;
	uint8_t isValid = 1;
	uint16_t* colorTable = LcdHandler->ColorTable;

	ResetGuiBuffer(RED); //Reset the GUI Buffer with Background color
//	
//	for(uint16_t i = 0; i <= LCD_HEIGHT; i += LCD_LINESIZE)
//	{
//		ResetGuiBuffer(colorTable[COLOR_BLACK]);  //Reset the GUI Buffer with Background color
//		if(isValid && InfoToDisplay[row].VariablePointer > 0)
//		{
//			switch(InfoToDisplay[row].FuncType)
//			{
//			case FUNC_INT32: 		Format_Int32(row, &InfoToDisplay[row], colorTable); 						break;
//			case FUNC_INT16: 		Format_Int16(row, &InfoToDisplay[row], colorTable);							break;
//			case FUNC_FLOAT: 		Format_Float3_3(row, &InfoToDisplay[row], colorTable);						break;
//			case FUNC_FLOAT_QUEVAR: Format_Float_QueVar(row, &InfoToDisplay[row], colorTable);					break;
//			case FUNC_HEX8: 		Format_Hex8(row, &InfoToDisplay[row], colorTable);							break;
//			case FUNC_HEX16: 		Format_Hex16(row, &InfoToDisplay[row], colorTable);							break;
//			case FUNC_HEX32: 		Format_Hex32(row, &InfoToDisplay[row], colorTable);							break;
//			case FUNC_ASCII: 		Format_Ascii(row, &InfoToDisplay[row], colorTable);							break;
//			case FUNC_BOOLEAN: 		Format_Boolean(row, &InfoToDisplay[row], colorTable);						break;
//			case FUNC_BAR_STATUS: 	Format_Bar_Status(row, &InfoToDisplay[row], colorTable);					break;
//			case FUNC_BAR_DUTTY: 	Format_Bar_Dutty(row, &InfoToDisplay[row], colorTable);						break;
//			case FUNC_BAR_FLOAT: 	Format_Bar_Float(row, &InfoToDisplay[row], colorTable);						break;
//			case FUNC_MEMHEX_64:    Format_MemoryDumpHex(row, &InfoToDisplay[row], colorTable);   				break;
//			case FUNC_MEMDUMPASCII: Format_MemoryDumpAscii(row, &InfoToDisplay[row], colorTable);   			break;
//			case FUNC_MEMDUMPHEX:   Format_MemoryDumpHex(row,&InfoToDisplay[row], colorTable);     				break;
//			case FUNC_MEMDISPASCII: Format_MemoryDisplayAscii(row,&InfoToDisplay[row], colorTable);				break;
//			case FUNC_MEMDISPASCIIHEX: Format_MemoryDisplayAsciiHex(row, &InfoToDisplay[row], colorTable); break;
//			case FUNC_ASCI_SOAP: 	Format_SoapStringWithIndex(row,&InfoToDisplay[row], colorTable);			break;
//
//			}
//		}else {
//			isValid = 0;
//		}
//		WriteGuiBuffer(row); //write the gui buffer to SPI.
//		row ++;
//	}
	WriteGuiBuffer(0);
}

void UpdateScreenMemoryHex(SPI_LCD_HandleTypeDef* LcdHandler, uint8_t* label, uint8_t* data, uint16_t size)
{
	uint16_t row = 0, col = 0, cnt = 0;
	ResetGuiBuffer(ColorNormalTable[COLOR_BLACK]);
	DrawString(LEFT_PADDING, PADDING, label, ColorNormalTable[COLOR_RED]);
	WriteGuiBuffer(row);
	row ++;

	uint8_t* temp = data;
	uint8_t isValid = 1;
	for(uint16_t i = 1; i <= LCD_HEIGHT; i += LCD_LINESIZE)
	{
		ResetGuiBuffer(ColorNormalTable[COLOR_BLACK]);  //Reset the GUI Buffer with Background color
		memset(strTempVal, 0, 40);
		if(isValid) {
			char* temp = strTempVal;
			for(col = 0; col < 8; col ++) {
				if(cnt >= size) break;
				sprintf(temp, "%02X ", data[cnt]);
				temp += 3;
				cnt ++;
			}
			if(cnt >= size) isValid = 0;
		}else {
			isValid = 0;
		}

		DrawString(LEFT_PADDING, PADDING, strTempVal, ColorNormalTable[COLOR_WHITE]);

		WriteGuiBuffer(row);

		row ++;
	}
}

void UpdateScreenMemoryText(SPI_LCD_HandleTypeDef* LcdHandler, uint8_t* label, uint8_t* data, uint16_t size)
{
	uint16_t row = 0, col = 0, cnt = 0;
	ResetGuiBuffer(ColorNormalTable[COLOR_BLACK]);
	DrawString(LEFT_PADDING, PADDING, label, ColorNormalTable[COLOR_RED]);
	WriteGuiBuffer(row);
	row ++;

	uint8_t* temp = data;
	uint8_t isValid = 1;
	for(uint16_t i = 1; i <= LCD_HEIGHT; i += LCD_LINESIZE)
	{
		ResetGuiBuffer(ColorNormalTable[COLOR_BLACK]);  //Reset the GUI Buffer with Background color
		memset(strTempVal, 0, 40);
		if(isValid) {
			char* temp = strTempVal;
			for(col = 0; col < 27; col ++) {
				if(cnt >= size) break;
				sprintf(temp, "%c", data[cnt]);
				temp ++;
				cnt ++;
			}
			if(cnt >= size) isValid = 0;
			DrawString(LEFT_PADDING, PADDING, strTempVal, ColorNormalTable[COLOR_WHITE]);
		}else {
			isValid = 0;
		}
		WriteGuiBuffer(row);

		row ++;
	}
}

void DisplayIndexIncrement()
{
	DisplayIndex++;	if(DisplayIndex > NUMBER_OF_DISPLAY_LISTS) DisplayIndex = 0;
}

void DisplayIndexDecrement()
{
	DisplayIndex--;	if(DisplayIndex < 0) DisplayIndex = NUMBER_OF_DISPLAY_LISTS;
}

