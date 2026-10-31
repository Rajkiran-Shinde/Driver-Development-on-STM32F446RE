#include "STM32F446xx.h"
#include "STM32F446xx_I2C.h"

uint16_t AHB_prescaler[8] = {2,8,16,32,64,128,256,512};
uint8_t APB1_prescaler[4] = {2,4,8,16};

static  void I2C_START_COND (I2C_REG_DEF_t *pI2Cx);
static void I2C__IMPLE_ADDR_PHASE(I2C_REG_DEF_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_CLEAR_ADDR_FLAG(I2C_REG_DEF_t *pI2Cx);
static void I2C_STOP_COND(I2C_REG_DEF_t *pI2Cx);

uint32_t RCC_GET_PCLK(void);

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
	uint8_t trise;

	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK;
	pI2CHandle ->pI2Cx->I2C_CR1 |= tempreg;

	//FREQ field of CR 2
	tempreg |= 0;
	tempreg |= (RCC_GET_PCLK()/1000000U);
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
		//Config for the Fast mode
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

	//Trise Configurations

	if (pI2CHandle->I2C_Config.I2C_SCL_SPEED <= I2C_SCL_SPEED_SM){
		// Mode is STandard mode

		trise = (RCC_GET_PCLK()/1000000U)+1;
	}
	else{
		//Mode if FS
		trise = ((RCC_GET_PCLK()*300)/1000000000U)+1;
	}

	pI2CHandle->pI2Cx->I2C_TRISE |= trise & 0x3F; //Masking bits from 6 to 15,
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


/*
 * I2C send DATA Register
 */
void I2C_SEND_DATA(I2C_HANDLE_t *pI2CHandle, uint8_t *pTXBuffer, uint32_t LEN, uint8_t SlaveAddr){

	//Generate the Start condition
	I2C_START_COND(pI2CHandle->pI2Cx);

	//Confirm The start condition by checking the SB flag in the SR1
	//To clear the SB We have to read from the SR1 and then write to DR
	while (! I2C_FlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

	// Send the address of the slave with R/W bit to W0 total 8 bits
	I2C__IMPLE_ADDR_PHASE(pI2CHandle->pI2Cx,SlaveAddr);

	//Confirm the Address phase is completed by checking the ADDR flag in SR1
	while (! I2C_FlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

	//Clear the ADDR flag according to the Software sequence,
	//Until the addr is cleared the SCL will be stretched
	I2C_CLEAR_ADDR_FLAG(pI2CHandle->pI2Cx);

	//Send Data until len become 0
	while (LEN>0){
		while (! I2C_FlagStatus (pI2CHandle->pI2Cx, I2C_FLAG_TXE));
		pI2CHandle -> pI2Cx ->I2C_DR = *pTXBuffer;
		pTXBuffer++;
		LEN--;
	}

	//When LEN becoms zero wait until TXE 1 and BTF 1 before generating the stop condition
	//BTF 1 SCL will be stretched
	while (! I2C_FlagStatus (pI2CHandle->pI2Cx, I2C_FLAG_TXE));

	while (! I2C_FlagStatus (pI2CHandle->pI2Cx, I2C_FLAG_BTF));

	//Generate the Stop confition
	I2C_STOP_COND(pI2CHandle->pI2Cx);


}

//Helper Function for Starting a Start Condition
static  void I2C_START_COND (I2C_REG_DEF_t *pI2Cx){
	pI2Cx->I2C_CR1 |= (1<<I2C_CR1_START);
}

//Function to get the Flag Status
uint8_t I2C_FlagStatus(I2C_REG_DEF_t *pI2Cx, uint32_t FlagName){

	if (pI2Cx->I2C_SR1 & FlagName){

		return FLAG_SET;
	}

	return FLAG_RESET;
}

// Address phase implementation by writing address followed by the Read and Write bit at LSB
static void I2C__IMPLE_ADDR_PHASE(I2C_REG_DEF_t *pI2Cx, uint8_t SlaveAddr){
	SlaveAddr = SlaveAddr<<1;
	SlaveAddr &= ~(1);
	pI2Cx->I2C_DR |= SlaveAddr;
}

//Helper function to clear the I2C flag
void I2C_CLEAR_ADDR_FLAG(I2C_REG_DEF_t *pI2Cx){
	uint32_t dummyread = pI2Cx ->I2C_SR1;
	dummyread = pI2Cx ->I2C_SR2;
	(void)dummyread;
}

// Helper function to STOP condition
static void I2C_STOP_COND(I2C_REG_DEF_t *pI2Cx){
	pI2Cx->I2C_CR1 |= (1<<I2C_CR1_STOP);
}



