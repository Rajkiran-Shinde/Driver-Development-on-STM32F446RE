#include "STM32F446xx.h"
#include "STM32F44xx_spi.h"


/*
 * Function to Return the Flag Status,
 */

uint8_t SPI_FlagStatus(SPI_REG_DEF_t *pSPIx, uint32_t FlagName){

	if (pSPIx-> SPI_SR & FlagName){

		return FLAG_SET;
	}

	return FLAG_RESET;
}

/*
 * SPI Peripheral Clock Control
 */

void SPI_PERI_CLK_CR (SPI_REG_DEF_t *pSPIx, uint8_t EN_OR_DIS){

	if (EN_OR_DIS == ENABLE){

			if (pSPIx == SPI1){
				SPI1_CLK_EN();
			}

			else if (pSPIx == SPI2){
				SPI2_CLK_EN();
			}

			else if (pSPIx == SPI3){
				SPI3_CLK_EN();
			}

			else if (pSPIx == SPI4){
				SPI4_CLK_EN();
			}
	else{
			if (pSPIx == SPI1){
				SPI1_CLK_DI();
			}

			else if (pSPIx == SPI2){
				SPI2_CLK_DI();
			}

			else if (pSPIx == SPI3){
				SPI3_CLK_DI();
			}

			else if (pSPIx == SPI4){
				SPI4_CLK_DI();
			}

		}
	}

}

/*
 * SPI INIT
 */
/*************************************************************************
 * @fn 							-SPI_INIT
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
void SPI_INIT (SPI_HANDLE_t *pSPIHandle){

	//Configure the SPI_CR1 REG

	uint32_t tempreg =0;

	SPI_PERI_CLK_CR(pSPIHandle ->pSPIx, ENABLE);

	//Configure the Device mode
	tempreg |= pSPIHandle->spiConfig.SPI_DeviceMode<< SPI_CR1_MSTR; //Set to the master

	//CONFIG the BUS

	if (pSPIHandle->spiConfig.SPI_BusConfig == SPI_BUS_FULL_DUP){

		//BIDI mode is Clear
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);
	}
	else if (pSPIHandle->spiConfig.SPI_BusConfig == SPI_BUS_HALF_DUP){
		//BIDI mode is Set
		tempreg |= (1<<SPI_CR1_BIDIMODE);
	}
	else if (pSPIHandle->spiConfig.SPI_BusConfig == SPI_BUS_SIMPL_RX){
		//BIDI mode is clear
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);

		// RXONLY bit is set
		tempreg |= (1<<SPI_CR1_RXONLY);
	}

	// CONFIG the SPI Serial clock speed
	tempreg |= pSPIHandle->spiConfig.SPI_SCLK_Speed<<SPI_CR1_BR;

	// Configure the DFF
	tempreg |= pSPIHandle->spiConfig.SPI_DFF<<SPI_CR1_DFF;

	//CONFIG the CPOL
	tempreg |= pSPIHandle->spiConfig.SPI_CPOL<<SPI_CR1_CPOL;

	//CONFIG the CPHA
	tempreg |= pSPIHandle->spiConfig.SPI_CPHA<<SPI_CR1_CPHA;

	pSPIHandle->pSPIx->SPI_CR1 |= tempreg;

}

/*
 * SPI DEINIT
 */

/*************************************************************************
 * @fn 							-SPI_DEINIT
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
void SPI_DEINIT (SPI_REG_DEF_t *pSPIx){
	if (pSPIx == SPI1){
		SPI1_REG_RESET();
	}
	else if (pSPIx == SPI2){
		SPI2_REG_RESET();
	}
	else if (pSPIx == SPI3){
		SPI3_REG_RESET();
	}
	else if (pSPIx == SPI4){
		SPI4_REG_RESET();
	}

}

/*
 * SPI Send Data
 */

/*************************************************************************
 * @fn 							-SPI SEDN DATA
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

void SPI_SendData(SPI_REG_DEF_t *pSPIx, uint8_t *pTXBuffer, uint32_t Len){

	while (Len > 0){

		//Wait until TXE is set
		while ( SPI_FlagStatus(pSPIx , SPI_TXE_FLAG) == FLAG_RESET);

		//Check the DFF bit
		if (pSPIx->SPI_CR1 & (1<<SPI_CR1_DFF)){

			//16 Bit
			//Load the Data to the DR
			pSPIx->SPI_DR = *((uint16_t*)pTXBuffer);
			Len--;
			Len--;
			//Increamne the TX buffer
			(uint16_t*)pTXBuffer++;
		}
		else {
			//8 Bit
			//Load the Data to the DR
			pSPIx->SPI_DR = *pTXBuffer;
			Len--;
			//Increment the Tx Buffer
			pTXBuffer++;
		}
	}
}

//API to Enable or Disable the SPI PERIpheral
void SPI_PERI_Control(SPI_REG_DEF_t *pSPIx, uint8_t EN_or_DI){
	if (EN_or_DI == ENABLE){

		pSPIx->SPI_CR1 |= (1<<SPI_CR1_SPE);
	}
	else{
		pSPIx->SPI_CR1 &= ~(1<<SPI_CR1_SPE);
	}
}

void SPI_SSI_CONFIG(SPI_REG_DEF_t *pSPIx, uint8_t EN_or_DI){

	if (EN_or_DI == ENABLE){
		pSPIx->SPI_CR1 |= (1<<SPI_CR1_SSI);
	}
	else{
		pSPIx->SPI_CR1 &= ~(1<<SPI_CR1_SSI);
	}
}


void SPI_SSOE_CONFIG(SPI_REG_DEF_t *pSPIx, uint8_t EN_or_DI){

	if (EN_or_DI == ENABLE){
		pSPIx->SPI_CR2 |= (1<<SPI_CR2_SSOE);
	}
	else{
		pSPIx->SPI_CR2 &= ~(1<<SPI_CR2_SSOE);
	}
}


