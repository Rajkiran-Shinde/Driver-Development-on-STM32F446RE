#include"STM32F446xx.h"
#include"STM32F446xx_I2C.h"
#include"STM32F446xx_gpio.h"

#include <string.h>

/*
 * PB6 SCL
 * PB9 -> SDA
 */

I2C_HANDLE_t  I2C1handle;

//I2C Receive Buffer
uint8_t rcv_buff[32];

#define MyAddr 0x61
#define SlaveAddr  0x68

void delay_debounce (void){
	for (uint32_t i=0; i<500000/2; i++);
}


void I2C1_GPIO_INIT(void){
	GPIO_HANDLE_t iicpins;
	iicpins.pGPIOx=GPIOB;
	iicpins.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_ALTFN;
	iicpins.GPIO_PinConfig.GPIO_PinOPtype = GPIO_OUT_OPEN_DRAIN;
	iicpins.GPIO_PinConfig.GPIO_PinPuPd = GPIO_PIN_PU;
	iicpins.GPIO_PinConfig.GPIO_PinAltFun = 4;
	iicpins.GPIO_PinConfig.GPIO_PinSpeed= GPIO_SPEED_FAST;

	//SCl PIN
	iicpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
	GPIO_INIT(&iicpins);

	//SDA PIN
	iicpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_9;
	GPIO_INIT(&iicpins);

}

void I2C1_INIT(void){

	I2C1handle.pI2Cx = I2C1;
	I2C1handle.I2C_Config.I2C_ACKControl = ENABLE;
	I2C1handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1handle.I2C_Config.I2C_SCL_SPEED = I2C_SCL_SPEED_SM;

	I2C_INIT(&I2C1handle);
}



int main (){
	uint8_t cmdcode;

	I2C1_GPIO_INIT();

	I2C1_INIT();

	I2C_PERI_Control(I2C1, ENABLE);

	while(1){

		while(! GPIO_MOD_IN(GPIOA, GPIO_PIN_0));

		delay_debounce();

		cmdcode = 0x51;
		I2C_SEND_DATA(&I2C1handle, &cmdcode, 1, SlaveAddr, I2C_REP_START);

		I2C_RECEIVE_DATA(&I2C1handle, &LEN, 1, SlaveAddr, I2C_REP_START);

		cmdcode = 0x52;
		I2C_SEND_DATA(&I2C1handle, &cmdcode, 1, SlaveAddr, I2C_REP_START);
		I2C_RECEIVE_DATA(&I2C1handle, rcv_buff, &LEN, SlaveAddr, I2C_NO_REP_START);
	}


}
