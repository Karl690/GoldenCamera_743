#pragma once
#include "configure.h"

#ifdef H_743

//X motor definitions
#define X_STEP_PIN 				(PIN_PORT_E | PIN_NUM_04 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define X_STEP_PORT				GPIOE
#define X_STEP_SET       		GPIOE->BSRR = PIN_MASK_04 //index to the set bit register
#define X_STEP_CLR       		GPIOE->BSRR = (uint32_t)PIN_MASK_04 << 16 //index to the Clear bit register
//
#define X_DIR_PIN 				(PIN_PORT_E | PIN_NUM_05 | PIN_INIT_LOW | OUTPUT_PP_50MHZ)  //
#define X_DIR_PORT				GPIOE
#define X_DIR_SET 				GPIOE->BSRR = PIN_MASK_05 //index to the set bit register
#define X_DIR_CLR 				GPIOE->BSRR = (uint32_t)PIN_MASK_05 <<16 //index to the Clear bit register
//
#define X_HOME_PIN 				(PIN_PORT_E | PIN_NUM_01 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define X_HOME_MASK				1<<(X_HOME_PIN & 0x000f)
#define X_HOME_PORT				GPIOE
#define X_HOME_READ				Home_X_Status = (X_HOME_PORT->IDR) & (X_HOME_MASK);

//Y motor definitions
#define Y_STEP_PIN 				(PIN_PORT_E | PIN_NUM_08 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Y_STEP_PORT				GPIOE
#define Y_STEP_SET       		GPIOE->BSRR = PIN_MASK_08 //index to the set bit register
#define Y_STEP_CLR   			GPIOE->BSRR = (uint32_t)PIN_MASK_08 <<16 //index to the Clear bit register
//
#define Y_DIR_PIN 				(PIN_PORT_E | PIN_NUM_06 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Y_DIR_PORT				GPIOE
#define Y_DIR_SET 				GPIOE->BSRR = PIN_MASK_06 //index to the set bit register
#define Y_DIR_CLR 				GPIOE->BSRR = (uint32_t)PIN_MASK_06 <<16 //index to the Clear bit register
//
#define Y_HOME_PIN 				(PIN_PORT_E | PIN_NUM_03 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define Y_HOME_MASK				1<<(Y_HOME_PIN & 0x000f)
#define Y_HOME_PORT				GPIOE
#define Y_HOME_READ				Home_Y_Status= (Y_HOME_PORT->IDR) & (Y_HOME_MASK);

//
//
//Z motor definitions
#define Z_STEP_PIN 				(PIN_PORT_B | PIN_NUM_05 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Z_STEP_PORT				GPIOB
#define Z_STEP_SET       		GPIOB->BSRR = PIN_MASK_05 //index to the set bit register
#define Z_STEP_CLR       		GPIOB->BSRR = (uint32_t)PIN_MASK_05 <<16 //index to the Clear bit register
//
#define Z_DIR_PIN 				(PIN_PORT_D | PIN_NUM_15 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Z_DIR_PORT				GPIOD
#define Z_DIR_SET				GPIOD->BSRR = PIN_MASK_15 //index to the set bit register
#define Z_DIR_CLR 				GPIOD->BSRR = (uint32_t)Pin_Mask_15 <<16 //index to the Clear bit register
//
#define Z_HOME_PIN 				(PIN_PORT_E | PIN_NUM_00 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define Z_HOME_MASK				1<<(Z_HOME_PIN & 0x000f)
#define Z_HOME_PORT				GPIOE
#define Z_HOME_READ				Home_Z_Status= (Z_HOME_PORT->IDR) & (Z_HOME_MASK);

//A motor definitions
#define A_STEP_PIN 				(PIN_PORT_D | PIN_NUM_04 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define A_STEP_PORT				GPIOD
#define A_STEP_SET       		GPIOD->BSRR = PIN_MASK_04 //index to the set bit register
#define A_STEP_CLR       		GPIOD->BSRR = (uint32_t)PIN_MASK_04 << 16 //index to the Clear bit register
//
#define A_DIR_PIN 				(PIN_PORT_D | PIN_NUM_06 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define A_DIR_PORT				GPIOD
#define A_DIR_SET 				GPIOD->BSRR = PIN_MASK_06 //index to the set bit register
#define A_DIR_CLR 				GPIOD->BSRR = (uint32_t)PIN_MASK_06 << 16 //index to the Clear bit register
//
#define A_HOME_PIN 				(PIN_PORT_B | PIN_NUM_03 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define A_HOME_MASK				1<<(A_HOME_PIN & 0x000f)
#define A_HOME_PORT				GPIOB
#define A_HOME_READ				Home_A_Status= (A_HOME_PORT->IDR) & (A_HOME_MASK);

//B motor definitions
#define B_STEP_PIN 				(PIN_PORT_C | PIN_NUM_04 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define B_STEP_PORT				GPIOC
#define B_STEP_SET       		GPIOC->BSRR = PIN_MASK_04 //index to the set bit register
#define B_STEP_CLR       		GPIOC->BSRR = (uint32_t)PIN_MASK_04 << 16 //index to the Clear bit register
//
#define B_DIR_PIN 				(PIN_PORT_B | PIN_NUM_00 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define B_DIR_PORT				GPIOB
#define B_DIR_SET 				GPIOB->BSRR = PIN_MASK_00 //index to the set bit register
#define B_DIR_CLR 				GPIOB->BSRR = (uint32_t)PIN_MASK_00 << 16 //index to the Clear bit register
//
#define B_HOME_PIN 				(PIN_PORT_E | PIN_NUM_07 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define B_HOME_MASK				1<<(B_HOME_PIN & 0x000f)
#define B_HOME_PORT				GPIOE
#define B_HOME_READ				Home_B_Status= (B_HOME_PORT->IDR) & (B_HOME_MASK);
//
//generic I/O pin_port
//B motor definitions
#define HEARTBEAT_PIN			(PIN_PORT_E | PIN_NUM_03 | PIN_INIT_LOW | OUTPUT_PP_50MHZ)
#define HEARTBEAT_SET			GPIOE->BSRR = PIN_MASK_03                 //index to the set bit register
#define HEARTBEAT_CLR			GPIOE->BSRR = (uint32_t)PIN_MASK_03 << 16 //index to the Clear bit register

//adc pins
#define ADC2_15_PA3				(PIN_PORT_A | PIN_NUM_03 | PIN_INIT_NONE | ANALOG_FLOATING) //
#define ADC2_18_PA4				(PIN_PORT_A | PIN_NUM_04 | PIN_INIT_NONE | ANALOG_FLOATING)
#define ADC2_19_PA5				(PIN_PORT_A | PIN_NUM_05 | PIN_INIT_NONE | ANALOG_FLOATING)
#define ADC2_03_PA6				(PIN_PORT_A | PIN_NUM_06 | PIN_INIT_NONE | ANALOG_FLOATING) //feedrate override
#define ADC2_05_PB1				(PIN_PORT_B | PIN_NUM_01 | PIN_INIT_NONE | ANALOG_FLOATING)
#define ADC2_04_PC5				(PIN_PORT_C | PIN_NUM_05 | PIN_INIT_NONE | ANALOG_FLOATING)

#define CAN1_RX					(PIN_AF_CAN1      | PIN_PORT_D | PIN_NUM_00 | PIN_PUPPD_PULLUP)
#define CAN1_TX					(PIN_AF_CAN1      | PIN_PORT_D | PIN_NUM_01)

#define LED_CAN_TX				(OUTPUT_PP_50MHZ  | PIN_PORT_G | PIN_NUM_01)
#define LED_CAN_TX_ON			GPIOG->BSRR = PIN_MASK_01
#define LED_CAN_TX_OFF			GPIOG->BSRR = PIN_MASK_01 << 16

//Pnp Spi for feeders PnP_Rclk_Set
#define PNP_ENABLE				(PIN_PORT_A | PIN_NUM_09  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)
#define PNP_ENABLE_SET			GPIOA->BSRR = PIN_MASK_09                 //index to the set bit register
#define PNP_ENABLE_CLR			GPIOA->BSRR = PIN_MASK_09 << 16  //index to the Clear bit register

#define PNP_RCLK				(PIN_PORT_C | PIN_NUM_11  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)
#define PNP_RCLK_SET			GPIOC->BSRR = PIN_MASK_11                  //index to the set bit register
#define PNP_RCLK_CLR			GPIOC->BSRR = PIN_MASK_11 << 16 //index to the Clear bit register


#define USERKEY1_PIN 			(PIN_PORT_C | PIN_NUM_13  |INPUT_PULLUP )  //
#define USERKEY1_PORT			GPIOC
#define USERKEY1_READ			UserKey1_Status = (USERKEY1_PORT->IDR) & (PIN_MASK_13);

#define USERKEY2_PIN 			(PIN_PORT_C | PIN_NUM_09  |INPUT_PULLUP )  //
#define USERKEY2_PORT			GPIOC
#define USERKEY2_READ			UserKey2_Status= (USERKEY2_PORT->IDR) & (PIN_MASK_09);

#define SPI2_LCD_RST			(PIN_PORT_C | PIN_NUM_00 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI2_LCD_RS				(PIN_PORT_C | PIN_NUM_03 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI2_LCD_CS				(PIN_PORT_B | PIN_NUM_07 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI2_LCD_MOSI			(PIN_PORT_C | PIN_NUM_01 | PIN_AF_SPI2)
#define SPI2_LCD_SCK			(PIN_PORT_D | PIN_NUM_03 | PIN_AF_SPI2)

#define SPI3_LCD_RST			(PIN_PORT_A | PIN_NUM_09 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI3_LCD_RS				(PIN_PORT_C | PIN_NUM_11 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI3_LCD_CS				(PIN_PORT_A | PIN_NUM_04 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI3_LCD_MOSI			(PIN_PORT_C | PIN_NUM_12 | PIN_AF_SPI3)
#define SPI3_LCD_SCK			(PIN_PORT_C | PIN_NUM_10 | PIN_AF_SPI3)

#define SPI4_LCD_BLK			(PIN_PORT_E | PIN_NUM_10 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI4_LCD_RST			(PIN_PORT_E | PIN_NUM_10 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI4_LCD_RS				(PIN_PORT_E | PIN_NUM_13 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ);// for FK750M1-VBT6 V1.1(with internal LCD line), it is E15 
#define SPI4_LCD_CS				(PIN_PORT_E | PIN_NUM_11 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI4_LCD_MOSI			(PIN_PORT_E | PIN_NUM_14 | PIN_AF_SPI4)
#define SPI4_LCD_SCK			(PIN_PORT_E | PIN_NUM_12 | PIN_AF_SPI4)

#endif // #ifndef pinout_HEADER // prevent double dipping - MUST BE LAST LINE OF FILE
