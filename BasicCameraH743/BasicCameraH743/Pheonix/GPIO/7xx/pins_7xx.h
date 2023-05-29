#pragma once
#include "configure.h"
#if defined (H_743) || defined(FK_750)

typedef uint32_t pinType;


#define PIN_NUM_SHIFT          0        // pin[3:0]
#define PIN_PORT_NUM_SHIFT     4        // pin[7:4]
#define PIN_MODE_SHIFT         8        // pin[9:8]
#define PIN_OSPEED_SHIFT       10       // pin[11:10]
#define PIN_INIT_VAL_SHIFT     12       // pin[12]
#define PIN_INIT_EN_SHIFT      13       // pin[13]
#define PIN_PUPPD_SHIFT        14       // pin[15:14]
#define PIN_AF_SHIFT           16       // pin[19:16]
#define PIN_OTYPE_SHIFT        20       // pin[20]
#define PIN_LOCK_SHIFT         21       // pin[21]


#define GPIO_PortSourceGPIOA       ((uint8_t)0x00)
#define GPIO_PortSourceGPIOB       ((uint8_t)0x01)
#define GPIO_PortSourceGPIOC       ((uint8_t)0x02)
#define GPIO_PortSourceGPIOD       ((uint8_t)0x03)
#define GPIO_PortSourceGPIOE       ((uint8_t)0x04)
#define GPIO_PortSourceGPIOF       ((uint8_t)0x05)
#define GPIO_PortSourceGPIOG       ((uint8_t)0x06)
#define GPIO_PortSourceGPIOH       ((uint8_t)0x07)
#define GPIO_PortSourceGPIOI       ((uint8_t)0x08)

#define PIN_NUM_00             (0x0 << PIN_NUM_SHIFT)
#define PIN_NUM_01             (0x1 << PIN_NUM_SHIFT)
#define PIN_NUM_02             (0x2 << PIN_NUM_SHIFT)
#define PIN_NUM_03             (0x3 << PIN_NUM_SHIFT)
#define PIN_NUM_04             (0x4 << PIN_NUM_SHIFT)
#define PIN_NUM_05             (0x5 << PIN_NUM_SHIFT)
#define PIN_NUM_06             (0x6 << PIN_NUM_SHIFT)
#define PIN_NUM_07             (0x7 << PIN_NUM_SHIFT)
#define PIN_NUM_08             (0x8 << PIN_NUM_SHIFT)
#define PIN_NUM_09             (0x9 << PIN_NUM_SHIFT)
#define PIN_NUM_10             (0xa << PIN_NUM_SHIFT)
#define PIN_NUM_11             (0xb << PIN_NUM_SHIFT)
#define PIN_NUM_12             (0xc << PIN_NUM_SHIFT)
#define PIN_NUM_13             (0xd << PIN_NUM_SHIFT)
#define PIN_NUM_14             (0xe << PIN_NUM_SHIFT)
#define PIN_NUM_15             (0xf << PIN_NUM_SHIFT)

#define PIN_PORT_A      ((uint32_t)(GPIO_PortSourceGPIOA) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_B      ((uint32_t)(GPIO_PortSourceGPIOB) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_C      ((uint32_t)(GPIO_PortSourceGPIOC) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_D      ((uint32_t)(GPIO_PortSourceGPIOD) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_E      ((uint32_t)(GPIO_PortSourceGPIOE) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_F      ((uint32_t)(GPIO_PortSourceGPIOF) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_G      ((uint32_t)(GPIO_PortSourceGPIOG) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_H      ((uint32_t)(GPIO_PortSourceGPIOH) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_I      ((uint32_t)(GPIO_PortSourceGPIOI) << PIN_PORT_NUM_SHIFT)
#define PIN_PORT_NONE   (0xf << PIN_PORT_NUM_SHIFT)

#define PIN_UNDEFINED   (0xffffffff)

#define PIN_MASK_00  0x0001
#define PIN_MASK_01  0x0002
#define PIN_MASK_02  0x0004
#define PIN_MASK_03  0x0008
#define PIN_MASK_04  0x0010
#define PIN_MASK_05  0x0020
#define PIN_MASK_06  0x0040
#define PIN_MASK_07  0x0080
#define PIN_MASK_08  0x0100
#define PIN_MASK_09  0x0200
#define PIN_MASK_10  0x0400
#define PIN_MASK_11  0x0800
#define PIN_MASK_12  0x1000
#define PIN_MASK_13  0x2000
#define PIN_MASK_14  0x4000
#define PIN_MASK_15  0x8000

////////////////////////////////////////////////////////////////////////////////
//  Public Methods available in pin
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef union {
	uint32_t u32;
	struct {
		unsigned pinNum     : 4;    // shift 0
		unsigned portNum    : 4;    // shift 4
		unsigned mode       : 2;    // shift 8
		unsigned speed      : 2;    // shift 10
		unsigned initVal    : 1;    // shift 11
		unsigned initEn     : 1;    // shift 12
		unsigned pupd       : 2;    // shift 14
		unsigned af         : 4;    // shift 16
		unsigned otype      : 1;    // shift 20
		unsigned lock       : 1;    // shift 21
	} b;
} pinUnion_t;

////////////////////////////////////////////////////////////////////////////////
#define pinExtractPinMask(pin)      (1 << (uint32_t)(((pinUnion_t)pin).b.pinNum))
#define pinExtractPinNum(pin)       ((uint32_t)(((pinUnion_t)pin).b.pinNum))
#define pinExtractPortNum(pin)      ((uint32_t)(((pinUnion_t)pin).b.portNum))
#define pinExtractMode(pin)         ((GPIOMode_TypeDef)(((pinUnion_t)pin).b.mode))
#define pinExtractSpeed(pin)        ((GPIOSpeed_TypeDef)(((pinUnion_t)pin).b.speed))
#define pinExtractInitVal(pin)      ((uint32_t)(((pinUnion_t)pin).b.initVal))
#define pinExtractInitEn(pin)       ((uint32_t)(((pinUnion_t)pin).b.initEn))
#define pinExtractPupd(pin)         ((GPIOPuPd_TypeDef)(((pinUnion_t)pin).b.pupd))
#define pinExtractAF(pin)           ((uint32_t)(((pinUnion_t)pin).b.af))
#define pinExtractOType(pin)        ((GPIOOType_TypeDef)(((pinUnion_t)pin).b.otype))
#define pinExtractLock(pin)         ((uint32_t)(((pinUnion_t)pin).b.lock))
#define pinExtractPortChar(pin)     ((char)(((pinUnion_t)pin).b.portNum) + 'A')


#define BIT_BAND(addr, bitnum)		((addr & 0xF0000000)+0x02000000+((addr & 0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  			*((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)		MEM_ADDR(BIT_BAND(addr, bitnum))


#define PIN_PORT_NUM(pin) 			(((pin>>PIN_PORT_NUM_SHIFT)&0xf)*0x400)
#define PIN_NUM(pin)				((pin>>PIN_NUM_SHIFT)&0xf)
#define PIN_MASK(pin)				(1<<PIN_NUM(pin))

#define ODR_OFS			0x14
#define IDR_OFS			0x10

#define GPIOA_ODR_ADDR    (GPIOA_BASE+ODR_OFS)
#define GPIOB_ODR_ADDR    (GPIOB_BASE+ODR_OFS)
#define GPIOC_ODR_ADDR    (GPIOC_BASE+ODR_OFS)
#define GPIOD_ODR_ADDR    (GPIOD_BASE+ODR_OFS)
#define GPIOE_ODR_ADDR    (GPIOE_BASE+ODR_OFS)
#define GPIOF_ODR_ADDR    (GPIOF_BASE+ODR_OFS)
#define GPIOG_ODR_ADDR    (GPIOG_BASE+ODR_OFS)

#define GPIOA_IDR_ADDR    (GPIOA_BASE+IDR_OFS)
#define GPIOB_IDR_ADDR    (GPIOB_BASE+IDR_OFS)
#define GPIOC_IDR_ADDR    (GPIOC_BASE+IDR_OFS)
#define GPIOD_IDR_ADDR    (GPIOD_BASE+IDR_OFS)
#define GPIOE_IDR_ADDR    (GPIOE_BASE+IDR_OFS)
#define GPIOF_IDR_ADDR    (GPIOF_BASE+IDR_OFS)
#define GPIOG_IDR_ADDR    (GPIOG_BASE+IDR_OFS)

typedef enum
{
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog Mode */
}GPIOMode_TypeDef;
/**
  * @brief  GPIO Output type enumeration
  */
typedef enum
{
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;
#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))


/**
  * @brief  GPIO Output Maximum frequency enumeration
  */
typedef enum
{
  GPIO_Speed_2MHz   = 0x00, /*!< Low speed */
  GPIO_Speed_25MHz  = 0x01, /*!< Medium speed */
  GPIO_Speed_50MHz  = 0x02, /*!< Fast speed */
  GPIO_Speed_100MHz = 0x03  /*!< High speed on 30 pF (80 MHz Output max speed on 15 pF) */
}GPIOSpeed_TypeDef;

/**
  * @brief  GPIO Configuration PullUp PullDown enumeration
  */
typedef enum
{
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
}GPIOPuPd_TypeDef;
#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))

//
// these define the values for the various fields (and most just match the spec defined register values
//

#define PIN_INIT_NONE          (0 << PIN_INIT_EN_SHIFT)
#define PIN_INIT_LOW           ((1 << PIN_INIT_EN_SHIFT) | (0 << PIN_INIT_VAL_SHIFT))
#define PIN_INIT_HIGH          ((1 << PIN_INIT_EN_SHIFT) | (1 << PIN_INIT_VAL_SHIFT))
#define PIN_INIT_PLDN   		((1 << PIN_INIT_EN_SHIFT) | (2 << PIN_INIT_VAL_SHIFT))   // lsb 0
#define PIN_INIT_PLUP   		((1 << PIN_INIT_EN_SHIFT) | (3 << PIN_INIT_VAL_SHIFT))   // lsb 1
#define PIN_INIT_HIZ    		((1 << PIN_INIT_EN_SHIFT) | (4 << PIN_INIT_VAL_SHIFT))   // lsb 0

#define PIN_MODE_IN            (GPIO_Mode_IN  << PIN_MODE_SHIFT)
#define PIN_MODE_OUT           (GPIO_Mode_OUT << PIN_MODE_SHIFT)
#define PIN_MODE_AF            (GPIO_Mode_AF  << PIN_MODE_SHIFT)
#define PIN_MODE_ANALOG        (GPIO_Mode_AN  << PIN_MODE_SHIFT)

#define PIN_OTYPE_PUSHPULL     (GPIO_OType_PP << PIN_OTYPE_SHIFT)
#define PIN_OTYPE_OPENDRAIN    (GPIO_OType_OD << PIN_OTYPE_SHIFT)

#define PIN_OSPEED_2MHZ        (GPIO_Speed_2MHz   << PIN_OSPEED_SHIFT)
#define PIN_OSPEED_25MHZ       (GPIO_Speed_25MHz  << PIN_OSPEED_SHIFT)
#define PIN_OSPEED_50MHZ       (GPIO_Speed_50MHz  << PIN_OSPEED_SHIFT)
#define PIN_OSPEED_100MHZ      (GPIO_Speed_100MHz << PIN_OSPEED_SHIFT)

#define PIN_PUPPD_NONE         (GPIO_PuPd_NOPULL << PIN_PUPPD_SHIFT)
#define PIN_PUPPD_PULLUP       (GPIO_PuPd_UP     << PIN_PUPPD_SHIFT)
#define PIN_PUPPD_PULLDOWN     (GPIO_PuPd_DOWN   << PIN_PUPPD_SHIFT)

#define PIN_LOCK_UNLOCKED      (0 << PIN_LOCK_SHIFT)
#define PIN_LOCK_LOCKED        (1 << PIN_LOCK_SHIFT)

////////////////////////////////////////////////////////////////////////////////

/**
  * @brief   AF 0 selection
  */
#define GPIO_AF_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping */
#define GPIO_AF_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping */
#define GPIO_AF_TAMPER        ((uint8_t)0x00)  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
#define GPIO_AF_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping */
#define GPIO_AF_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF_TIM1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping */
#define GPIO_AF_TIM9          ((uint8_t)0x03)  /* TIM9 Alternate Function mapping */
#define GPIO_AF_TIM10         ((uint8_t)0x03)  /* TIM10 Alternate Function mapping */
#define GPIO_AF_TIM11         ((uint8_t)0x03)  /* TIM11 Alternate Function mapping */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping */
#define GPIO_AF_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF_SPI3          ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF_SPI4          ((uint8_t)0x05)  /* SPI4/I2S3 Alternate Function mapping */
/**
  * @brief   AF 6 selection
  */


/**
  * @brief   AF 7 selection
  */
#define GPIO_AF_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping */
#define GPIO_AF_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping */
#define GPIO_AF_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping */
#define GPIO_AF_I2S3ext       ((uint8_t)0x07)  /* I2S3ext Alternate Function mapping */
#define GPIO_AF_USART6        ((uint8_t)0x07)  /* USART6 Alternate Function mapping */
/**
  * @brief   AF 8 selection
  */
#define GPIO_AF_UART4         ((uint8_t)0x08)  /* UART4 Alternate Function mapping */
#define GPIO_AF_UART5         ((uint8_t)0x08)  /* UART5 Alternate Function mapping */



/**
  * @brief   AF 9 selection
  */
#define GPIO_AF_CAN1          ((uint8_t)0x09)  /* CAN1 Alternate Function mapping */
#define GPIO_AF_CAN2          ((uint8_t)0x09)  /* CAN2 Alternate Function mapping */
#define GPIO_AF_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping */
#define GPIO_AF_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping */
#define GPIO_AF_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF_OTG_FS         ((uint8_t)0xA)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF_OTG_HS         ((uint8_t)0xA)  /* OTG_HS Alternate Function mapping */

/**
  * @brief   AF 11 selection
  */
#define GPIO_AF_ETH             ((uint8_t)0x0B)  /* ETHERNET Alternate Function mapping */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF_FSMC            ((uint8_t)0xC)  /* FSMC Alternate Function mapping */
#define GPIO_AF_OTG_HS_FS       ((uint8_t)0xC)  /* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF_SDIO            ((uint8_t)0xC)  /* SDIO Alternate Function mapping */

/**
  * @brief   AF 13 selection
  */
#define GPIO_AF_DCMI          ((uint8_t)0x0D)  /* DCMI Alternate Function mapping */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

/**
  * @}
  */

/** @defgroup GPIO_Legacy
  * @{
  */

#define GPIO_Mode_AIN           GPIO_Mode_AN

#define GPIO_AF_OTG1_FS         GPIO_AF_OTG_FS
#define GPIO_AF_OTG2_HS         GPIO_AF_OTG_HS
#define GPIO_AF_OTG2_FS         GPIO_AF_OTG_HS_FS

////////////////////////////////////////////////////////////////////////////////
//
// these define all of the legal Alternate Function mappings
// it's up to the coder to made sure a given pin supports the requested mapping
//

#define PIN_AF_CAN1            (PIN_MODE_AF | (GPIO_AF_CAN1      << PIN_AF_SHIFT))    // CAN1 Alternate Function
#define PIN_AF_CAN2            (PIN_MODE_AF | (GPIO_AF_CAN2      << PIN_AF_SHIFT))    // CAN2 Alternate Function
#define PIN_AF_DCMI            (PIN_MODE_AF | (GPIO_AF_DCMI      << PIN_AF_SHIFT))    // DCMI Alternate Function
#define PIN_AF_ETH             (PIN_MODE_AF | (GPIO_AF_ETH       << PIN_AF_SHIFT))    // ETHERNET Alternate Function
#define PIN_AF_EVENTOUT        (PIN_MODE_AF | (GPIO_AF_EVENTOUT  << PIN_AF_SHIFT))    // EVENTOUT Alternate Function
#define PIN_AF_FSMC            (PIN_MODE_AF | (GPIO_AF_FSMC      << PIN_AF_SHIFT))    // FSMC Alternate Function
#define PIN_AF_I2C1            (PIN_MODE_AF | (GPIO_AF_I2C1      << PIN_AF_SHIFT))    // I2C1 Alternate Function
#define PIN_AF_I2C2            (PIN_MODE_AF | (GPIO_AF_I2C2      << PIN_AF_SHIFT))    // I2C2 Alternate Function
#define PIN_AF_I2C3            (PIN_MODE_AF | (GPIO_AF_I2C3      << PIN_AF_SHIFT))    // I2C3 Alternate Function
#define PIN_AF_I2S3ext         (PIN_MODE_AF | (GPIO_AF_I2S3ext   << PIN_AF_SHIFT))    // I2S3ext Alternate Function
#define PIN_AF_MCO             (PIN_MODE_AF | (GPIO_AF_MCO       << PIN_AF_SHIFT))    // MCO (MCO1 and MCO2) Alternate Function
//#define PIN_AF_OTG_FS          (PIN_MODE_AF | (GPIO_AF_OTG_FS    << PIN_AF_SHIFT))    // OTG_FS Alternate Function
#define PIN_AF_OTG_FS          (PIN_MODE_AF | PIN_OSPEED_100MHZ | (GPIO_AF_OTG_FS    << PIN_AF_SHIFT))    // OTG_FS Alternate Function
//#define PIN_AF_OTG_HS          (PIN_MODE_AF | PIN_OSPEED_100MHZ | (GPIO_AF_OTG_HS    << PIN_AF_SHIFT))    // OTG_HS Alternate Function
//#define PIN_AF_OTG_HS_FS       (PIN_MODE_AF | PIN_OSPEED_100MHZ | (GPIO_AF_OTG_HS_FS << PIN_AF_SHIFT))    // OTG HS configured in FS, Alternate Function
#define PIN_AF_RTC_50Hz        (PIN_MODE_AF | (GPIO_AF_RTC_50Hz  << PIN_AF_SHIFT))    // RTC_50Hz Alternate Function
#define PIN_AF_SDIO            (PIN_MODE_AF | (GPIO_AF_SDIO      << PIN_AF_SHIFT))    // SDIO Alternate Function
#define PIN_AF_SPI1            (PIN_MODE_AF | (GPIO_AF_SPI1      << PIN_AF_SHIFT))    // SPI1 Alternate Function
#define PIN_AF_SPI2            (PIN_MODE_AF | (GPIO_AF_SPI2      << PIN_AF_SHIFT))    // SPI2/I2S2 Alternate Function
#define PIN_AF_SPI3            (PIN_MODE_AF | (GPIO_AF_SPI3      << PIN_AF_SHIFT))    // SPI3/I2S3 Alternate Function
#define PIN_AF_SPI4            (PIN_MODE_AF | (GPIO_AF_SPI4      << PIN_AF_SHIFT))    // SPI3/I2S3 Alternate Function
#define PIN_AF_SWJ             (PIN_MODE_AF | (GPIO_AF_SWJ       << PIN_AF_SHIFT))    // SWJ (SWD and JTAG) Alternate Function
#define PIN_AF_TAMPER          (PIN_MODE_AF | (GPIO_AF_TAMPER    << PIN_AF_SHIFT))    // TAMPER (TAMPER_1 and TAMPER_2) Alternate Function
#define PIN_AF_TIM1            (PIN_MODE_AF | (GPIO_AF_TIM1      << PIN_AF_SHIFT))    // TIM1 Alternate Function
#define PIN_AF_TIM10           (PIN_MODE_AF | (GPIO_AF_TIM10     << PIN_AF_SHIFT))    // TIM10 Alternate Function
#define PIN_AF_TIM11           (PIN_MODE_AF | (GPIO_AF_TIM11     << PIN_AF_SHIFT))    // TIM11 Alternate Function
#define PIN_AF_TIM12           (PIN_MODE_AF | (GPIO_AF_TIM12     << PIN_AF_SHIFT))    // TIM12 Alternate Function
#define PIN_AF_TIM13           (PIN_MODE_AF | (GPIO_AF_TIM13     << PIN_AF_SHIFT))    // TIM13 Alternate Function
#define PIN_AF_TIM14           (PIN_MODE_AF | (GPIO_AF_TIM14     << PIN_AF_SHIFT))    // TIM14 Alternate Function
#define PIN_AF_TIM2            (PIN_MODE_AF | (GPIO_AF_TIM2      << PIN_AF_SHIFT))    // TIM2 Alternate Function
#define PIN_AF_TIM3            (PIN_MODE_AF | (GPIO_AF_TIM3      << PIN_AF_SHIFT))    // TIM3 Alternate Function
#define PIN_AF_TIM4            (PIN_MODE_AF | (GPIO_AF_TIM4      << PIN_AF_SHIFT))    // TIM4 Alternate Function
#define PIN_AF_TIM5            (PIN_MODE_AF | (GPIO_AF_TIM5      << PIN_AF_SHIFT))    // TIM5 Alternate Function
#define PIN_AF_TIM8            (PIN_MODE_AF | (GPIO_AF_TIM8      << PIN_AF_SHIFT))    // TIM8 Alternate Function
#define PIN_AF_TIM9            (PIN_MODE_AF | (GPIO_AF_TIM9      << PIN_AF_SHIFT))    // TIM9 Alternate Function
#define PIN_AF_TRACE           (PIN_MODE_AF | (GPIO_AF_TRACE     << PIN_AF_SHIFT))    // TRACE Alternate Function
#define PIN_AF_UART4           (PIN_MODE_AF | (GPIO_AF_UART4     << PIN_AF_SHIFT))    // UART4 Alternate Function
#define PIN_AF_UART5           (PIN_MODE_AF | (GPIO_AF_UART5     << PIN_AF_SHIFT))    // UART5 Alternate Function
#define PIN_AF_USART1          (PIN_MODE_AF | (GPIO_AF_USART1    << PIN_AF_SHIFT))    // USART1 Alternate Function
#define PIN_AF_USART2          (PIN_MODE_AF | (GPIO_AF_USART2    << PIN_AF_SHIFT))    // USART2 Alternate Function
#define PIN_AF_USART3          (PIN_MODE_AF | (GPIO_AF_USART3    << PIN_AF_SHIFT))    // USART3 Alternate Function
#define PIN_AF_USART6          (PIN_MODE_AF | (GPIO_AF_USART6    << PIN_AF_SHIFT))    // USART6 Alternate Function
//
// common definitions for basic IO
//
	


#define AF_OUT_PP_2MHZ    (PIN_MODE_AF | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_2MHZ)
#define AF_OUT_PP_25MHZ   (PIN_MODE_AF | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_25MHZ)
#define AF_OUT_PP_50MHZ   (PIN_MODE_AF | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_50MHZ)
#define AF_OUT_PP_100MHZ  (PIN_MODE_AF | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_100MHZ)

#define AF_OUT_OD_2MHZ    (PIN_MODE_AF | PIN_OTYPE_OPENDRAIN  | PIN_OSPEED_2MHZ)
#define AF_OUT_OD_25MHZ   (PIN_MODE_AF | PIN_OTYPE_OPENDRAIN  | PIN_OSPEED_25MHZ)
#define AF_OUT_OD_50MHZ   (PIN_MODE_AF | PIN_OTYPE_OPENDRAIN  | PIN_OSPEED_50MHZ)
#define AF_OUT_OD_100MHZ  (PIN_MODE_AF | PIN_OTYPE_OPENDRAIN  | PIN_OSPEED_100MHZ)

#define OUTPUT_PP_2MHZ    (PIN_MODE_OUT | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_2MHZ)
#define OUTPUT_PP_25MHZ   (PIN_MODE_OUT | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_25MHZ)
#define OUTPUT_PP_50MHZ   (PIN_MODE_OUT | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_50MHZ)
#define OUTPUT_PP_100MHZ  (PIN_MODE_OUT | PIN_OTYPE_PUSHPULL  | PIN_OSPEED_100MHZ)

#define OUTPUT_OD_2MHZ    (PIN_MODE_OUT | PIN_OTYPE_OPENDRAIN | PIN_OSPEED_2MHZ)
#define OUTPUT_OD_25MHZ   (PIN_MODE_OUT | PIN_OTYPE_OPENDRAIN | PIN_OSPEED_25MHZ)
#define OUTPUT_OD_50MHZ   (PIN_MODE_OUT | PIN_OTYPE_OPENDRAIN | PIN_OSPEED_50MHZ)
#define OUTPUT_OD_100MHZ  (PIN_MODE_OUT | PIN_OTYPE_OPENDRAIN | PIN_OSPEED_100MHZ)

#define AF_IN_FLOATING    (PIN_MODE_IN | PIN_PUPPD_NONE)
#define AF_IN_PULLUP      (PIN_MODE_IN | PIN_PUPPD_PULLUP)
#define AF_IN_PULLDOWN    (PIN_MODE_IN | PIN_PUPPD_PULLDOWN)

#define INPUT_FLOATING    (PIN_MODE_IN | PIN_PUPPD_NONE)
#define INPUT_PULLUP      (PIN_MODE_IN | PIN_PUPPD_PULLUP)
#define INPUT_PULLDOWN    (PIN_MODE_IN | PIN_PUPPD_PULLDOWN)

#define ANALOG_FLOATING   (PIN_MODE_ANALOG | PIN_PUPPD_NONE)
#define ANALOG_PULLUP     (PIN_MODE_ANALOG | PIN_PUPPD_PULLUP)
#define ANALOG_PULLDOWN   (PIN_MODE_ANALOG | PIN_PUPPD_PULLDOWN)

#define PAout(n)   BIT_ADDR(GPIOA_ODR_ADDR,n)
#define PAin(n)    BIT_ADDR(GPIOA_IDR_ADDR,n)

#define PBout(n)   BIT_ADDR(GPIOB_ODR_ADDR,n)
#define PBin(n)    BIT_ADDR(GPIOB_IDR_ADDR,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_ADDR,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_ADDR,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_ADDR,n)
#define PDin(n)    BIT_ADDR(GPIOD_IDR_ADDR,n)

#define PEout(n)   BIT_ADDR(GPIOE_ODR_ADDR,n)
#define PEin(n)    BIT_ADDR(GPIOE_IDR_ADDR,n)

#define PFout(n)   BIT_ADDR(GPIOF_ODR_ADDR,n)
#define PFin(n)    BIT_ADDR(GPIOF_IDR_ADDR,n)

#define PGout(n)   BIT_ADDR(GPIOG_ODR_ADDR,n)
#define PGin(n)    BIT_ADDR(GPIOG_IDR_ADDR,n)


extern uint16_t Home_X_Status;
extern uint16_t Home_Y_Status;
extern uint16_t Home_Z_Status;
extern uint16_t Home_A_Status;
extern uint16_t Home_B_Status;
extern uint16_t Home_C_Status;

extern uint16_t UserKey1_Status;
extern uint16_t UserKey2_Status;

extern GPIO_TypeDef *pinExtractPortPtr(pinType);
extern void pinInit(pinType);
extern void pinClear(pinType);
extern void pinSet(pinType);
extern void pinWrite(pinType, uint32_t);
extern uint32_t pinRead(pinType);
extern uint32_t pinReadOutput(pinType);
extern void pinToggleOutput(pinType);
extern void Update_Home_Status(void);
////////////////////////////////////////////////////////////////////////////////
#endif
