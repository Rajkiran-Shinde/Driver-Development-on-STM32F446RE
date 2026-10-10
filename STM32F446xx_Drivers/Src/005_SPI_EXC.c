#include"STM32F446xx.h"
#include"STM32F44xx_spi.h"
#include"STM32F446xx_gpio.h"

#include <string.h>

//SPI2 Pins
/*
 * Alternate Fun Block AF5
 * NSS PB9
 * SCL PB10
 * MISO PB14
 * MOSI PB15
 */
void SPI_GPIO_INIT(void){

	GPIO_HANDLE_t SPIpin;


	SPIpin.pGPIOx = GPIOB;
	SPIpin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIpin.GPIO_PinConfig.GPIO_PinAltFun = 5;
	SPIpin.GPIO_PinConfig.GPIO_PinOPtype = GPIO_OUT_PUSH_PULL;
	SPIpin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MID;
	SPIpin.GPIO_PinConfig.GPIO_PinPuPd = GPIO_NO_PUPD;

	//GPIO PIN num Config
	//SCLK
	SPIpin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
	GPIO_INIT(&SPIpin);

	//MISO
	//SPIpin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
	//GPIO_INIT(&SPIpin);

	//MOSI
	SPIpin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15;
	GPIO_INIT(&SPIpin);

	//NSS
	SPIpin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_9;
	GPIO_INIT(&SPIpin);

}

//Peripheral INIT
void SPI2_INIT(void){
	SPI_HANDLE_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.spiConfig.SPI_BusConfig = SPI_BUS_FULL_DUP; // Full duplex config
	SPI2handle.spiConfig.SPI_DFF = SPI_DFF_8BIT;
	SPI2handle.spiConfig.SPI_DeviceMode = SPI_DEVICE_MASTER;
	SPI2handle.spiConfig.SPI_SCLK_Speed = SPI_CLK_SPD_DIV_2; // SCLK CLK of 8 MHz
	SPI2handle.spiConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.spiConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.spiConfig.SPI_SSM = SPI_SSM_DI;

	SPI_INIT(&SPI2handle);

}

int main (void){

	char userData [] = "Hello STM";

	SPI_GPIO_INIT(); // Enable the GPIO pin as SPI

	SPI2_INIT(); // INIT the SPI24

	SPI_SSOE_CONFIG(SPI2, ENABLE);

	SPI_SSI_CONFIG(SPI2, ENABLE);
	//Enable the SPI2 Peripheral
	SPI_PERI_Control(SPI2, ENABLE);


	SPI_SendData(SPI2, (uint8_t*) userData, strlen (userData));

	SPI_PERI_Control(SPI2, DISABLE);

	while (1);

	return 0;

}
