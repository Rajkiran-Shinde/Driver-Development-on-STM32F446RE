#include "STM32F446xx.h"
#include "STM32F446xx_I2C.h"

uint16_t AHB_prescaler[8] = {2,8,16,32,64,128,256,512};
uint8_t APB1_prescaler[4] = {2,4,8,16};

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

	uint32_t tempreg = 0;

	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK;
	pI2CHandle ->pI2Cx->I2C_CR1 |= tempreg;

	//FREQ field of CR 2
	tempreg |= 0;
	tempreg (RCC_GET_PCLK()/1000000U);
	pI2CHandle->pI2Cx->I2C_CR2 |= (tempreg & 0x3F);

	//Own Address config
	tempreg = 0;
	tempreg |= 1<<14;
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress <<I2C_OAR1_ADD;
	pI2CHandle -> pI2Cx->I2C_OAR1 |= tempreg;

	//CCR Calck
	uint16_t CCR_Value = 0;
	tempreg = 0;
	if (pI2CHandle->I2C_Config.I2C_SCL_SPEED <= I2C_SCL_SPEED_SM){
		//Config for the Stander mode
		//Assuming that Thigh = Tlow so we can say Thigh+Tlow = 2CCR*TPCLK
		//converting everthing to frequency domain we can get the following logic
		CCR_Value= (RCC_GET_PCLK()/(2*pI2CHandle->I2C_Config.I2C_SCL_SPEED));
		tempreg |= (CCR_Value&0xFFF);
	}
	else{
		//Config for the Fast mode \
		//Enable the fast mode
		tempreg |= pI2CHandle->pI2Cx->I2C_CCR <<I2C_CCR_FS;
		tempreg |= pI2CHandle->I2C_Config.I2C_FMDutyCycle <<I2C_CCR_DUTY;

		if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2){
			//COnfig Duty 0 FM0
			CCR_Value = (RCC_GET_PCLK()/(3*pI2CHandle->I2C_Config.I2C_SCL_SPEED));
			tempreg |= (CCR_Value&0xFFF);
		}
		else{
			//Config Duty 1 FM1
			CCR_Value = (RCC_GET_PCLK()/(25*pI2CHandle->I2C_Config.I2C_SCL_SPEED));
			tempreg |= (CCR_Value&0xFFF);
		}
	}
	pI2CHandle->pI2Cx->I2C_CCR |= tempreg;
}

uint32_t RCC_GET_PCLK(void){
	uint32_t PCLCK;
	uint32_t SysClck;
	uint8_t CLCKSRC, HPRESRC, AHB_PRE, PPRE1SRC,APB1_PRE;

	//SYStem Clock as HSI, HSE, PLLP, PLLR
	CLCKSRC = (RCC->CFGR >> 2)& 0x3;

	if (CLCKSRC == 0){
		SysClck = 16000000;
	}
	else if (CLCKSRC == 1){
		SysClck = 8000000;
	}

	//AHB Prescaler
	HPRESRC = (RCC->CFGR>>4)&0xF;

	if (HPRESRC <= 8){
		AHB_PRE = AHB_prescaler[HPRESRC -8];
	}

	//APB1 Prescaler
	PPRE1SRC = (RCC->CFGR>>10)&0x7;
	if (PPRE1SRC <= 4){
		APB1_PRE = APB1_prescaler[PPRE1SRC - 4];
	}

	PCLCK = (SysClck / AHB_PRE)/APB1_PRE;

	return PCLCK;
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
