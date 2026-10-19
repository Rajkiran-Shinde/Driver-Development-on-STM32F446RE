#include "STM32F446xx.h"
#include "STM32F446xx_I2C.h"

//Implementation of the I2C peripheral Clock Control
void I2C_PERI_CLK_CR (I2C_REG_DEF_t *pI2Cx, uint8_t EN_OR_DIS){
	if (EN_OR_DIS == ENABLE){
		if (pI2Cx == I2C1){
			I2C1_CLK_EN();
		}
		else if (pI2Cx == I2C2){
			I2C2_CLK_EN();
		}
		else if (pI2Cx == I2C3){
			I2C3_CLK_EN();
		}
	else {
		if (pI2Cx == I2C1){
			I2C1_CLK_DI();
		}
		else if (pI2Cx == I2C2){
			I2C2_CLK_DI();
		}
		else if (pI2Cx == I2C3){
			I2C3_CLK_DI();
		}

		}
	}
}

//Api for the INIT of the I2C
void I2C_INIT (I2C_HANDLE_t *pI2CHandle){

}

// API for the Disable the I2C Peripheral.
void I2C_DEINIT (I2C_REG_DEF_t *pI2Cx){
	if (pI2Cx == I2C1){
		I2C1_CLK_DI();
	}
	else if (pI2Cx == I2C2){
		I2C2_CLK_DI();
	}
	else if (pI2Cx == I2C3){
		I2C3_CLK_DI();
	}
}

//API to Enable or Disable the I2C PERIpheral
void I2C_PERI_Control(I2C_REG_DEF_t *pI2Cx, uint8_t EN_or_DI){
	if (EN_or_DI== ENABLE){
		pI2Cx->I2C_CR1 |= (1<< I2C_CR1_PE);
	}
	else{
		pI2Cx->I2C_CR1 &= ~(1<< I2C_CR1_PE);
	}
}
