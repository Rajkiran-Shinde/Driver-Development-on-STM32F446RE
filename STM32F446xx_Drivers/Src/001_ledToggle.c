#include"STM32F446xx.h"
#include"STM32F446xx_gpio.h"

void delay (void){
	for (uint32_t i=0; i<500000; i++);

}
int main(void){


	GPIO_HANDLE_t gpioLed;

	gpioLed.pGPIOx = GPIOA;// Select the gpio port

	GPIO_CLK_CR(GPIOA, ENABLE); //Enable the clck of gpio peripheral

	gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5; ///GPIO PIN selection

	gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT; //GPIO PIB mode OUTPUT

	gpioLed.GPIO_PinConfig.GPIO_PinOPtype = GPIO_OUT_OPEN_DRAIN;

	gpioLed.GPIO_PinConfig.GPIO_PinPuPd = GPIO_NO_PUPD;


	GPIO_INIT(&gpioLed);


	while(1){
		GPIO_TOGGLE_OT(GPIOA, GPIO_PIN_5);
		delay();
	}

	return 0;
}
