#include"STM32F446xx.h"
#include"STM32F446xx_gpio.h"

#define BUTTON_PRESS 0
#define BUTTON_RELEASE 1

void delay (void){
	for (uint32_t i=0; i<500000; i++);
}

void delay_debounce (void){
	for (uint32_t i=0; i<500000/2; i++);
}


int main(void){


	GPIO_HANDLE_t gpioLed, gpioButton;

	gpioLed.pGPIOx = GPIOA;// Select the gpio port

	GPIO_CLK_CR(GPIOA, ENABLE); //Enable the clck of gpio peripheral

	gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5; ///GPIO PIN selection

	gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT; //GPIO PIB mode OUTPUT

	gpioLed.GPIO_PinConfig.GPIO_PinOPtype = GPIO_OUT_PUSH_PULL;

	gpioLed.GPIO_PinConfig.GPIO_PinPuPd = GPIO_NO_PUPD;

	GPIO_INIT(&gpioLed);

	//Button Config
	gpioButton.pGPIOx = GPIOC; //User Button is on PC13 and 0 when Press

	GPIO_CLK_CR(GPIOC, ENABLE);

	gpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;

	gpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;

	gpioButton.GPIO_PinConfig.GPIO_PinPuPd = GPIO_NO_PUPD;

	GPIO_INIT(&gpioButton);

	while(1){
		if (GPIO_MOD_IN(GPIOC, GPIO_PIN_13) == BUTTON_PRESS){

		//delay_debounce();

		GPIO_TOGGLE_OT(GPIOA, GPIO_PIN_5);

		}

	}

	return 0;
}
