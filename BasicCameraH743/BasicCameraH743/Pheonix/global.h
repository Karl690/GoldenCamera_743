#pragma once
#include <stdio.h>
#include <stdint.h>
#define MAX_ADC 					0x0fff

#define CAN_DEV_HOST				0x40
#define CAN_HEAD_12					12
#define CAN_BROADCAST_ADDRESS		0xFF


//Common Defination
#define LED_ON_MAXCOUNT			0x0F

#define KARLS_PASSWORD ((uint32_t)666)
#define CHECKSUM_KEY 0x5555aaaa

#define EOT			0x04	//End of Transmission. we use this as the first byte of var pairs 's block
#define FOV			0x0A	//First byte of Var	pair
#define EOV			0x0D	//End byte of var pair
#define FOC			0xFF	//Formatted byte of Charactor

#define ACK		(uint8_t)6
#define NAK		(uint8_t)21
#define ENQ		(uint8_t)5

typedef int16_t temp_t; // temperature (s10.5 format - 1/32 degree resolution)
typedef uint32_t pinType;

typedef enum {
	FORETASK_IDLE = 0,
	FORETASK_ERASE_SOAPSTRING,
	FORETASK_WRITE_SOAPSTRING,
	FORETASK_READ_SOAPSTRING,
}ForeTaskFlag_t;

typedef enum {
	BOOT_NORMAL = 0,
	BOOT_SAFE 	= 0xFF, //boot by fault
}BootType_t;


typedef enum {
	COLOR_MODE_NORMAL,
	COLOR_MODE_INVERT,
}color_mode_t;