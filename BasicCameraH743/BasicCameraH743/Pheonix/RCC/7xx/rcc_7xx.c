#include "configure.h"
#if defined (H_743) || defined(FK_750)
#include "main.h"
#include <RCC/7xx/rcc_7xx.h>
#include "taskmanager.h"
volatile uint32_t usTicks=0;

void Init_RCC()
{
    //Enable All GPIOs clock
	uint32_t rcc = (uint32_t)(RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN |
							RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_GPIODEN | RCC_AHB4ENR_GPIOEEN |
							RCC_AHB4ENR_GPIOFEN | RCC_AHB4ENR_GPIOGEN |
							RCC_AHB4ENR_GPIOIEN | RCC_AHB4ENR_GPIOJEN |
							RCC_AHB4ENR_GPIOKEN);
	RCC->AHB4ENR |= (rcc);
	RCC->AHB4RSTR &= ~(rcc);

	//Enable Timer Clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2RSTR &= ~RCC_APB2ENR_TIM1EN;

	rcc = RCC_APB1LENR_TIM2EN | RCC_APB1LENR_TIM3EN | RCC_APB1LENR_TIM4EN;//enable clocks for timers
	RCC->APB1LENR |= rcc;
	RCC->AHB1RSTR &= ~(rcc);
}


void Delay_ms(uint32_t ms) {
	//	SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_MS);
	//	usTicks = ms + 1;
	//	while (usTicks != 0);
	for (int i = 0; i < ms; i++)
	{
		Delay_us(1000);
	}
}

// Do delay for nSecs microseconds
void Delay_us(uint32_t us) {
	//	SysTick_Config(SystemCoreClock / DELAY_TICK_FREQUENCY_US);
	//	usTicks = us + 1;
	//	while (usTicks != 0);
	for (int a = 0; a < 1000; a++)
	{
		a++;
		a--;
	}
}

#endif
