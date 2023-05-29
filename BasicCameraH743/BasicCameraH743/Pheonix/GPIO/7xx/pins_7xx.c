#include "configure.h"
#if defined (H_743) || defined(FK_750)

uint16_t Home_X_Status=0;//setup the home status bits
uint16_t Home_Y_Status=0;//setup the home status bits
uint16_t Home_Z_Status=0;//setup the home status bits
uint16_t Home_A_Status=0;//setup the home status bits
uint16_t Home_B_Status=0;//setup the home status bits
uint16_t Home_C_Status=0;//setup the home status bits

uint16_t UserKey1_Status=1;
uint16_t UserKey2_Status=1;

GPIO_TypeDef *pinExtractPortPtr(pinType pin)
{   // return address pointer to this pin's port
	if (pin != PIN_UNDEFINED)
	{
		switch (pinExtractPortNum(pin))
		{
		case GPIO_PortSourceGPIOA : return(GPIOA);
		case GPIO_PortSourceGPIOB : return(GPIOB);
		case GPIO_PortSourceGPIOC : return(GPIOC);
		case GPIO_PortSourceGPIOD : return(GPIOD);
		case GPIO_PortSourceGPIOE : return(GPIOE);
		case GPIO_PortSourceGPIOF : return(GPIOF);
		case GPIO_PortSourceGPIOG : return(GPIOG);
		case GPIO_PortSourceGPIOH : return(GPIOH);
		case GPIO_PortSourceGPIOI : return(GPIOI);
		}
	}
	else
	{
		return(0);
	}
}

////////////////////////////////////////////////////////////////////////////////

void pinInit(pinType pin)
{   // init the pin using the ST provided routine (can be put inline and sped up
	// if needed

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = pinExtractPinMask(pin);
	  GPIO_InitStruct.Mode = pinExtractMode(pin);
	  GPIO_InitStruct.Pull = pinExtractPupd(pin);
	  GPIO_InitStruct.Speed = pinExtractSpeed(pin);
	  GPIO_InitStruct.Alternate = pinExtractAF(pin);

	  HAL_GPIO_Init(pinExtractPortPtr(pin), &GPIO_InitStruct);
}

////////////////////////////////////////////////////////////////////////////////

void pinClear(pinType pin)
{   // writing "1" to any bit in the UPPER 16 bits of the BSSR reg (BSSR[31:16]
	// will force the corresponding bit(s) on that port to be set to 0

	if (pin != PIN_UNDEFINED)
	{
		pinExtractPortPtr(pin)->BSRR = pinExtractPinMask(pin)<<16;


	}
}

////////////////////////////////////////////////////////////////////////////////

void pinSet(pinType pin)
{   // writing "1" to any bit in the LOWER 16 bits of the BSSR (ie, BSSR[15:0]
	// will force the corresponding bit(s) on that port to be set to 1

	if (pin != PIN_UNDEFINED)
	{
		pinExtractPortPtr(pin)->BSRR = pinExtractPinMask(pin);
	}
}

////////////////////////////////////////////////////////////////////////////////

void pinWrite(pinType pin, uint32_t value)
{   // use clear or set to force the output to the desired value
	// NO CHECKING is performed to make sure this is requested on an OUTPUT

	if (pin == PIN_UNDEFINED) return;

	if (value == 0)
		pinClear(pin);
	else
		pinSet(pin);
}

////////////////////////////////////////////////////////////////////////////////

uint32_t pinRead(pinType pin)
{   // grab the IDR for the port belong to the pin and shift results down to move
	// the desired bit position to the LBS and AND with 0x1 to make sure only
	// the value from the requested bit is return (returns a 0 or 1)

	if (pin == PIN_UNDEFINED) return(0);

	return((uint32_t)(pinExtractPortPtr(pin)->IDR >> pinExtractPinNum(pin)) & 0x1);

}

////////////////////////////////////////////////////////////////////////////////

uint32_t pinReadOutput(pinType pin)
{   // grab the IDR for the port belong to the pin and shift results down to move
	// the desired bit position to the LBS and AND with 0x1 to make sure only
	// the value from the requested bit is return (returns a 0 or 1)

	if (pin == PIN_UNDEFINED) return(0);

	return((uint32_t)(pinExtractPortPtr(pin)->ODR >> pinExtractPinNum(pin)) & 0x1);
}

////////////////////////////////////////////////////////////////////////////////

void pinToggleOutput(pinType pin)
{   // really used for driving the LA for debug....flip the output state of an output pin

	if (pin == PIN_UNDEFINED) return;

	pinWrite(pin, (~pinReadOutput(pin)) & 0x1);
}


////////////////////////////////////////////////////////////////////////////////
#endif
