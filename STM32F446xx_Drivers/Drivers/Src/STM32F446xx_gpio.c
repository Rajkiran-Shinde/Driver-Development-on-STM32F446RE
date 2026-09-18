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

void GPIO_INIT(GPIO_HANDLE_t *pGPIOHandle)
{
	//This will hold the mask
	uint32_t temp=0;

	//We are only configuing for the non interrupt mode, so we are limiting it for just 4 modes
	//as input, output, alternate, and analog.
	// Config Mode
	if (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){

		//This creates a mask
		temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));

		pGPIOHandle->pGPIOx->MODER &= ~(0x3 <<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber); //Clearing the bit

		//Applies the mask on actual register
		pGPIOHandle->pGPIOx->MODER |= temp;

	}
	else{
		//Interupt Mode
	}

	//Config the Speed
	//Clear the Temp value to use again,
	temp=0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<(2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDER &= ~(0x3 <<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber); //Clearing the Bit
	pGPIOHandle->pGPIOx->OSPEEDER |= temp;

	// Config pull up or down
	temp =0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPd << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 <<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber); //Clearing the Bit
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	//Config Output type
	temp =0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPtype << (pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 <<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber); //Clearing the Bit
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp =0;
	//Alternate func if requires

	if (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){

		uint32_t pinNum = pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber;
		uint32_t altfValue = pGPIOHandle -> GPIO_PinConfig.GPIO_PinAltFun;

		uint32_t div, rem;

		div = pinNum/8; //Gives 0 or 1
		rem = pinNum%8;

		pGPIOHandle->pGPIOx->AFR[div] &=~(0xf <<(4 * rem));
		pGPIOHandle->pGPIOx->AFR[div] |= altfValue<<(4 * rem);

	}

}

/*************************************************************************
 * @fn 							-GPIO_DEINIT
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
	if (pGPIOx == GPIOA){
		GPIOA_REG_RESET();
			}

			else if (pGPIOx == GPIOB){
				GPIOB_REG_RESET();
			}

			else if (pGPIOx == GPIOC){
				GPIOC_REG_RESET();
			}

			else if (pGPIOx == GPIOD){
				GPIOD_REG_RESET();
			}

			else if (pGPIOx == GPIOE){
				GPIOE_REG_RESET();
			}

			else if (pGPIOx == GPIOF){
				GPIOF_REG_RESET();
			}

			else if (pGPIOx == GPIOG){
				GPIOG_REG_RESET();
			}

			else if (pGPIOx == GPIOH){
				GPIOH_REG_RESET();
			}

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

/*************************************************************************
 * @fn 							-GPIO READ FROM INPUT
 *
 * @Brief  						-
 *
 * @param[in]					-
 * @param[in]					-
 * @param[in]					-
 *
 * @return 						-0 or 1
 *
 * @Note						-NA
 *
 *
 *************************************************************************/

// GPIO Input Pin and PORT Mode

uint8_t GPIO_MOD_IN(GPIO_REG_DEF *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;

	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);

	return value;
}

uint16_t GPIO_MOD_IN_PORT(GPIO_REG_DEF *pGPIOx)
{
	uint16_t value;

	value = (uint16_t) pGPIOx->IDR;

	return value;
}

/*************************************************************************
 * @fn 							-GPIO WRITE TO OUTPUT
 *
 * @Brief  						-
 *
 * @param[in]					-
 * @param[in]					-
 * @param[in]					-
 *
 * @return 						-0 or 1
 *
 * @Note						-NA
 *
 *
 *************************************************************************/
// GPIO Output Pin and PORT Mode

void GPIO_MOD_OT(GPIO_REG_DEF *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET){
		pGPIOx-> ODR |= (1<<PinNumber);
	}
	else{
		pGPIOx-> ODR &= ~(1<<PinNumber);
	}

}

void GPIO_MOD_OT_PORT(GPIO_REG_DEF *pGPIOx, uint16_t Value)
{
	pGPIOx-> ODR = Value;
}

// GPIO Toggle Output API

void GPIO_TOGGLE_OT(GPIO_REG_DEF *pGPIOx, uint8_t PinNumber)
{
	pGPIOx-> ODR ^=(1<<PinNumber);
}

// GPIO IRQ Handling and Configuration

void GPIO_IRQ_CFG(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EN_OR_DIS)
{

}

void GPIO_IRQ_HND(uint8_t PinNumber)
{

}
