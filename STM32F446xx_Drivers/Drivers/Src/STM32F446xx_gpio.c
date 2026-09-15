#include"STM32F446xx_gpio.h"
#include "STM32F446xx.h"
/*
 * Peripheral Clock Setup
 */
/*************************************************************************
 * @fn 							-GPIO_INIT
 *
 * @Brief  						-
 *
 * @param[in]					-
 * @param[in]					-
 * @param[in]					-
 *
 * @return 						-NA
 *
 * @Note						-NA
 *
 *
 *************************************************************************/
// GPIO Control API

void GPIO_INIT(GPIO_HNADLE_t *pGPIOHandle)
{
	// Config Mode
	if (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){

	}
	else{
		//Interupt Mode
	}

	//Config the Speed

	// Config pull up or down

	//Config Output type

	//Alternate func if requires

}

/*************************************************************************
 * @fn 							-GPIO_INIT
 *
 * @Brief  						-
 *
 * @param[in]					-
 * @param[in]					-
 * @param[in]					-
 *
 * @return 						-NA
 *
 * @Note						-NA
 *
 *
 *************************************************************************/
void GPIO_DEINIT(GPIO_REG_DEF *pGPIOx)
{

}

/*
 * Peripheral Clock Setup
 */
/*************************************************************************
 * @fn 							-GPIO_CLK_CR
 *
 * @Brief  						-This function Enables or Disables the clock of the GPIO port
 *
 * @param[in]					- Base Address of GPIO Peripheral
 * @param[in]					- ENABLE or DISABLE macros
 * @param[in]					-
 *
 * @return 						-NA
 *
 * @Note						-NA
 *
 *
 *************************************************************************/

// GPIO Clock Control

void GPIO_CLK_CR(GPIO_REG_DEF *pGPIOx, uint8_t EN_OR_DIS)
{
	if (EN_OR_DIS == ENABLE){

		if (pGPIOx == GPIOA){
			GPIOA_CLK_EN();
		}

		else if (pGPIOx == GPIOB){
			GPIOB_CLK_EN();
		}

		else if (pGPIOx == GPIOC){
			GPIOC_CLK_EN();
		}

		else if (pGPIOx == GPIOD){
			GPIOC_CLK_EN();
		}

		else if (pGPIOx == GPIOE){
			GPIOC_CLK_EN();
		}

		else if (pGPIOx == GPIOF){
			GPIOC_CLK_EN();
		}

		else if (pGPIOx == GPIOG){
			GPIOC_CLK_EN();
		}

		else if (pGPIOx == GPIOH){
			GPIOH_CLK_EN();
		}

	}
	else {

		if (pGPIOx == GPIOA){
			GPIOA_CLK_DI();
		}

		else if (pGPIOx == GPIOB){
			GPIOB_CLK_DI();
		}

		else if (pGPIOx == GPIOC){
			GPIOC_CLK_DI();
		}

		else if (pGPIOx == GPIOD){
			GPIOC_CLK_DI();
		}

		else if (pGPIOx == GPIOE){
			GPIOC_CLK_DI();
		}

		else if (pGPIOx == GPIOF){
			GPIOC_CLK_DI();
		}

		else if (pGPIOx == GPIOG){
			GPIOC_CLK_DI();
		}

		else if (pGPIOx == GPIOH){
			GPIOH_CLK_DI();
		}

	}
}

// GPIO Input Pin and PORT Mode

uint8_t GPIO_MOD_IN(GPIO_REG_DEF *pGPIOx, uint8_t PinNumber)
{

}

uint16_t GPIO_MOD_IN_PORT(GPIO_REG_DEF *pGPIOx)
{

}

// GPIO Output Pin and PORT Mode

void GPIO_MOD_OT(GPIO_REG_DEF *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

}

void GPIO_MOD_OT_PORT(GPIO_REG_DEF *pGPIOx, uint16_t Value)
{

}

// GPIO Toggle Output API

void GPIO_TOGGLE_OT(GPIO_REG_DEF *pGPIOx, uint8_t PinNumber)
{

}

// GPIO IRQ Handling and Configuration

void GPIO_IRQ_CFG(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EN_OR_DIS)
{

}

void GPIO_IRQ_HND(uint8_t PinNumber)
{

}
