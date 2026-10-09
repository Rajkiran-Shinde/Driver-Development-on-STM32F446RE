#include"STM32F446xx_gpio.h"
#include "STM32F446xx.h"

//Function to get the Port code for the EXTI
static inline uint16_t GPIO_PORT_CODE (GPIO_REG_DEF *PGPIOx){

	if (PGPIOx == GPIOA){
		return 0;
	}
	else if (PGPIOx == GPIOB){
		return 1;
	}
	else if (PGPIOx == GPIOC){
		return 2;
	}
	else if (PGPIOx == GPIOD){
		return 3;
	}
	else if (PGPIOx == GPIOE){
		return 4;
	}
	else if (PGPIOx == GPIOF){
		return 5;
	}
	else if (PGPIOx == GPIOG){
		return 6;
	}
	else if (PGPIOx == GPIOH){
		return 7;
	}

	return 0;

}

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

	//Enable the Peripheral ClCK
	GPIO_CLK_CR(pGPIOHandle -> pGPIOx, ENABLE);

	//We are only configuing for the non interrupt mode, so we are limiting it for just 4 modes
	//as input, output, alternate, and analog.
	// Config Mode
	if (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){

		//This creates a mask
		temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));

		pGPIOHandle->pGPIOx->MODER &= ~(0x3 <<2* pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber); //Clearing the bit

		//Applies the mask on actual register
		pGPIOHandle->pGPIOx->MODER |= temp;

	}

	else{
		//Interrupt MODE Falling and Rising Edge
		if (pGPIOHandle-> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IR_FT){
			//CONFIG of the FTSR register
			EXTI->EXTI_FTSR |= (1<<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
			//Clear the Currosponding RTSR bit
			EXTI->EXTI_RTSR &= ~(1<<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
		}

		else if (pGPIOHandle-> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IR_RT){
			//CONFIG of the RTSR register
			EXTI->EXTI_RTSR |= (1<<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
			//Clear the Currosponding FTSR bit
			EXTI->EXTI_FTSR &= ~(1<<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
		}

		else if (pGPIOHandle-> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IR_RFT){
			//CONFIG of the RTSR register
			EXTI->EXTI_RTSR |= (1<<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
			//Set the Currosponding FTSR bit
			EXTI->EXTI_FTSR |= (1<<pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
		}

		// Config The GPIO Port Selection in SYSCFG_EXTICR
		uint32_t temp1 = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber/4); //Gives the register to choose

		uint32_t temp2 = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber%4); //Gives the section to Add the bits

		uint32_t portCode = GPIO_PORT_CODE (pGPIOHandle->pGPIOx);

		//Enable the clock for the SYSCFG
		SYSCFG_CLK_EN();
		//Clearing the Register before setting them
		SYSCFG->SYSCFG_EXTICR[temp1] &= ~(portCode << (temp2 * 4));

		SYSCFG->SYSCFG_EXTICR[temp1] |= (portCode << (temp2 * 4));

		//Enable the EXTI interrupt delivery using Interrupt mask register
		EXTI->EXTI_IMR |= (1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
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

void GPIO_IRQ_IT_CFG(uint8_t IRQNumber, uint8_t EN_OR_DIS)
{
	if (EN_OR_DIS == ENABLE){
		if (IRQNumber <= 31){
			//ISER0
			*NVIC_ISER0 |= (1<<IRQNumber);
		}
		else if (IRQNumber >= 32 && IRQNumber <= 63){
			//ISER1
			*NVIC_ISER1 |= (1<<IRQNumber%32);
		}
		else if (IRQNumber >= 64 && IRQNumber <= 96){
			//ISER 2
			*NVIC_ISER2 |= (1<<IRQNumber%64);
		}
	}
	else {
		if (IRQNumber <= 31){
				//ICER0
			*NVIC_ICER0 &= ~(1<<IRQNumber);
		}
		else if (IRQNumber >= 32 && IRQNumber <= 63){
				//ICER1
			*NVIC_ICER1 &= ~(1<<IRQNumber%32);
		}
		else if (IRQNumber >= 64 && IRQNumber <= 96){
				//ICER 2
			*NVIC_ICER2 &= ~(1<<IRQNumber%32);
		}

	}

}

void GPIO_IRQ_PRY_CFG(uint8_t IRQNumber,uint8_t IRQPriority){
	uint8_t IPRx = IRQNumber/4; //This gives the Register which We have to config among the 0 to 59
	uint8_t IPRx_Section = IRQNumber%4; //This gives the section of that specific register
	uint8_t shiftAmount = ((IPRx_Section*8)+(8-NO_OF_BITS_IMPLEMENTED));

	*(NVIC_IPR_BASE_ADDER + IPRx) &= ~(0xF << shiftAmount);
	*(NVIC_IPR_BASE_ADDER + IPRx) |= (IRQPriority<<shiftAmount);
}

void GPIO_IRQ_HND(uint8_t PinNumber)
{
	if (EXTI->EXTI_PR & (1<< PinNumber)){

		//Clear the pending register, to do that we have to set the 1 value
		EXTI->EXTI_PR |= (1<<PinNumber);
	}
}
