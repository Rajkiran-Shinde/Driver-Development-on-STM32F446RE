#ifndef INC_STM32F44XX_SPI_H_
#define INC_STM32F44XX_SPI_H_

#include "STM32F446xx.h"
/*
 * SPI Device Mode Master or Slave
 */
#define SPI_DEVICE_MASTER		1
#define SPI_DEVICE_SLAVE 		0

/*
 * SPI BUS Configurations
 */
#define SPI_BUS_FULL_DUP		1
#define SPI_BUS_HALF_DUP 		2
//#define SPI_BUS_SIMPL_TX		3
#define SPI_BUS_SIMPL_RX		4

/*
 * SPI CLOCK SPEED CONFIG
 */
#define SPI_CLK_SPD_DIV_2		0
#define SPI_CLK_SPD_DIV_4		1
#define SPI_CLK_SPD_DIV_8		2
#define SPI_CLK_SPD_DIV_16		3
#define SPI_CLK_SPD_DIV_32		4
#define SPI_CLK_SPD_DIV_64		5
#define SPI_CLK_SPD_DIV_128		6
#define SPI_CLK_SPD_DIV_256		7

/*
 * Data Frame format CONFIG
 */
#define SPI_DFF_8BIT			0
#define SPI_DFF_16BIT			1

/*
 * CPOL CPHA CONFIG
 */
#define SPI_CPOL_HIGH			1
#define SPI_CPOL_LOW			0

#define SPI_CPHA_HIGH			1
#define SPI_CPHA_LOW			0

/*
 *  Software slave management CONFIG
 */
#define SPI_SSM_EN				1
#define SPI_SSM_DI				0 //Default

/**************************************************
* Macros for the SPI_CR1 Resister
 *************************************************/
#define SPI_CR1_CPHA  			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15


/**************************************************
* Macros for the SPI_CR2 Resister
 *************************************************/
#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE    		7


/**************************************************
* Macros for the SPI_SR Resister
 *************************************************/
#define SPI_SR_RXNE 			0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8


/*
 * Macros to RESET the SPIx Peripherals
 */
#define SPI1_REG_RESET()			do{(RCC -> APB2RSTR |= (1<<12)) ; (RCC -> APB2RSTR &=~(1<<12));} while (0)
#define SPI2_REG_RESET()			do{(RCC -> APB1RSTR |= (1<<14)) ; (RCC -> APB1RSTR &=~(1<<14));} while (0)
#define SPI3_REG_RESET()			do{(RCC -> APB1RSTR |= (1<<15)) ; (RCC -> APB1RSTR &=~(1<<15));} while (0)
#define SPI4_REG_RESET()			do{(RCC -> APB2RSTR |= (1<<13)) ; (RCC -> APB2RSTR &=~(1<<13));} while (0)

/*
 * SPI FLAG STATUS related Definition
 */
#define SPI_TXE_FLAG 		(1<<SPI_SR_TXE)
#define SPI_RXNE_FLAG 		(1<<SPI_SR_RXNE)
#define SPI_BSY_FLAG		(1<<SPI_SR_BSY)

/*
 * Configuration Structure for the SPI
 */

typedef struct {
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SCLK_Speed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_CONFIG_t;

//Structure to Handle the SPI Peripheral
typedef struct {
	SPI_REG_DEF_t *pSPIx;
	SPI_CONFIG_t spiConfig;
}SPI_HANDLE_t;


//SPI INIT DEINIT API
void SPI_INIT (SPI_HANDLE_t *pSPIHandle); 		//Initilise The SPI port
void SPI_DEINIT (SPI_REG_DEF_t *pSPIx);		//Desable the SPI Port

//SPI Clock Controll
void SPI_PERI_CLK_CR (SPI_REG_DEF_t *pSPIx, uint8_t EN_OR_DIS);	// SPI Peripheral clock control

//Date Send and Receive
void SPI_SendData(SPI_REG_DEF_t *pSPIx, uint8_t *pTXBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_REG_DEF_t *pSPIx, uint8_t *pRXBuffer, uint32_t Len);

//IRQ Configuration and ISR handling

void SPI_IRQ_IT_CFG (uint8_t IRQNumber, uint8_t EN_OR_DIS);		//Configure the SPI Interrupt
void SPI_IRQ_PRY_CFG(uint8_t IRQNumber,uint8_t IRQPriority);
void SPI_IRQ_HND(SPI_HANDLE_t *pHandle); 		//Interrupt Handling

//SPI Other Peripheral Control Prototypes

//API to Enable or Disable the SPI PERIpheral
void SPI_PERI_Control(SPI_REG_DEF_t *pSPIx, uint8_t EN_or_DI);

void SPI_SSI_CONFIG(SPI_REG_DEF_t *pSPIx, uint8_t EN_or_DI);


#endif /* INC_STM32F44XX_SPI_H_ */
