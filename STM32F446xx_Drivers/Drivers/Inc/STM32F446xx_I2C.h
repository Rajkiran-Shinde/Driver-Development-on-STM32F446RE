#ifndef INC_STM32F446XX_I2C_H_
#define INC_STM32F446XX_I2C_H_

/*
 * I2C Speed Macros
 */
#define I2C_SCL_SPEED_SM		 100000 //100K Standard Mode
#define I2C_SCL_SPEED_FM0		 200000 // 200k Fast mode
#define I2C_SCL_SPEED_FM1		 400000 // 400K Fast mode

/*
 * I2C Ack Control
 */
#define I2C_ACK_ENABLE 	   		1
#define I2C_ACK_DISABLE 		0

/*
 * I2C FM Duty cycle
 */
#define I2C_FM_DUTY_2			0
#define I2C_FM_DUTY_16_9 		1

//Bit Position Macros For I2C Peripheral
/*
 * I2C Control Register  CR1
 */
#define I2C_CR1_PE 		   		0
#define I2C_CR1_SMBUS			1
#define I2C_CR1_SMTYPE			3
#define I2C_CR1_ENARP			4
#define I2C_CR1_ENPEC			5
#define I2C_CR1_ENGC			6
#define I2C_CR1_NOSTRETCH		7
#define I2C_CR1_START			8
#define I2C_CR1_STOP			9
#define I2C_CR1_ACK				10
#define I2C_CR1_POS				11
#define I2C_CR1_PEC				12
#define I2C_CR1_ALERT			13
#define I2C_CR1_SWRST			15

/*
 * I2C Control Register  CR2
 */
#define I2C_CR2_FREQ 		   	0
#define I2C_CR2_ITERREN			8
#define I2C_CR2_ITEVTEN			9
#define I2C_CR2_ITBUFEN			10
#define I2C_CR2_DMAEN			11
#define I2C_CR2_LAST			12

/*
 * I2C Status Register I2C_SR1
 */

#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RxNE		6
#define I2C_SR1_TxE			7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF 			10
#define I2C_SR1_OVR			11
#define I2C_SR1_PECERR		12
#define I2C_SR1_TIMEOUT		14
#define I2C_SR1_SMBALERT	15

/*
 * I2C Status Register I2C_SR2
 */
#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GENCALL		4
#define I2C_SR2_SMBDEFAULT	5
#define I2C_SR2_SMBHOST		6
#define I2C_SR2_DUALF		7


/*
 * Configuration Structure for I2Cx Peripheral
 */
typedef struct {
	uint32_t I2C_SCL_SPEED; //
	uint8_t  I2C_DeviceAddress;
	uint8_t  I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
}I2C_CONFIG_t;

typedef struct {
	I2C_REG_DEF_t *pI2Cx;
	I2C_CONFIG_t  I2C_Config;
}I2C_HANDLE_t;




//I2C INIT DEINIT API
void I2C_INIT (I2C_HANDLE_t *pI2CHandle); 		//Initilise The I2C port
void I2C_DEINIT (I2C_REG_DEF_t *pI2Cx);		//Desable the I2C Port

//I2C Clock Controll
void I2C_PERI_CLK_CR (I2C_REG_DEF_t *pI2Cx, uint8_t EN_OR_DIS);	// I2C Peripheral clock control


//IRQ Configuration and ISR handling

void I2C_IRQ_IT_CFG (uint8_t IRQNumber, uint8_t EN_OR_DIS);		//Configure the I2C Interrupt
void I2C_IRQ_PRY_CFG(uint8_t IRQNumber,uint8_t IRQPriority);


//I2C Other Peripheral Control Prototypes

//API to Enable or Disable the I2C PERIpheral
void I2C_PERI_Control(I2C_REG_DEF_t *pI2Cx, uint8_t EN_or_DI);
uint8_t I2C_FlagStatus(I2C_REG_DEF_t *pI2Cx, uint32_t FlagName);


#endif /* INC_STM32F446XX_I2C_H_ */
