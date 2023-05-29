#pragma once

typedef struct
{
	uint32_t SYSCLK_Frequency; /*!<  SYSCLK clock frequency expressed in Hz */
	uint32_t HCLK_Frequency; /*!<  HCLK clock frequency expressed in Hz   */
	uint32_t PCLK1_Frequency; /*!<  PCLK1 clock frequency expressed in Hz  */
	uint32_t PCLK2_Frequency; /*!<  PCLK2 clock frequency expressed in Hz  */
}RCC_ClocksTypeDef;


void Init_RCC();
void Delay_ms(uint32_t ms);
void Delay_us(uint32_t us);