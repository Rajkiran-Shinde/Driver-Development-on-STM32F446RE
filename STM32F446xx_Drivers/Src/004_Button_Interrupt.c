#include"STM32F446xx.h"
#include"STM32F446xx_gpio.h"

#define BUTTON_PRESS 0
#define BUTTON_RELEASE 1

void delay (void){
	for (uint32_t i=0; i<500000; i++);
}

void delay_debounce (void){
	for (uint32_t i=0; i<500000/4; i++);
}

int main(void)
{
    GPIO_HANDLE_t gpioLed, gpioButton;

    // LED Config
    gpioLed.pGPIOx = GPIOA;
    GPIO_CLK_CR(GPIOA, ENABLE);
    gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    gpioLed.GPIO_PinConfig.GPIO_PinOPtype = GPIO_OUT_PUSH_PULL;
    gpioLed.GPIO_PinConfig.GPIO_PinPuPd = GPIO_NO_PUPD;

    GPIO_INIT(&gpioLed);


    // Button Config
    gpioButton.pGPIOx = GPIOA;
    GPIO_CLK_CR(GPIOA, ENABLE);
    gpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
    gpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IR_FT;
    gpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    gpioButton.GPIO_PinConfig.GPIO_PinOPtype = GPIO_OUT_PUSH_PULL;
    gpioButton.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_PU;

    GPIO_INIT(&gpioButton);


    // IRQ Config
    GPIO_IRQ_PRY_CFG(IRQ_EXTI9_5, 15);

    GPIO_IRQ_IT_CFG(IRQ_EXTI9_5, ENABLE);


    while(1);
}

void EXTI9_5_IRQHandler(void){
	GPIO_IRQ_HND(GPIO_PIN_6);

	delay_debounce();

	GPIO_TOGGLE_OT(GPIOA, GPIO_PIN_5);
}
