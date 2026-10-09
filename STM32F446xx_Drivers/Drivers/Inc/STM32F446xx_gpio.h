#ifndef INC_STM32F446XX_GPIO_H_
#define INC_STM32F446XX_GPIO_H_

#include "STM32F446xx.h"

//Macros for the GPIO Registers

//GPIO Pin Numbers
#define GPIO_PIN_0 		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_PIN_8		8
#define GPIO_PIN_9		9
#define GPIO_PIN_10		10
#define GPIO_PIN_11		11
#define GPIO_PIN_12		12
#define GPIO_PIN_13		13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15


//GPIO Mode Macros
#define GPIO_MODE_IN  0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3
//Interupt modes
#define GPIO_MODE_IR_FT 4 //Falling edge
#define GPIO_MODE_IR_RT 5 //RISING EDGE
#define GPIO_MODE_IR_RFT 6 //Rising and Falling edge detection

//GPIO OUTPUT Types
#define GPIO_OUT_PUSH_PULL 0
#define GPIO_OUT_OPEN_DRAIN 1

//GPIO OUTPUT SPEED REG
#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MID 1
#define GPIO_SPEED_FAST 2
#define GPIO_SPEED_HIGH 3

//GPIO Pull up pull down
#define GPIO_NO_PUPD 0
#define GPIO_PIN_PU 1
#define GPIO_PIN_PD 2


/*
 * This is a handle Structure for a GPIO pin
 */
typedef struct {
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPd;
	uint8_t GPIO_PinOPtype;
	uint8_t GPIO_PinAltFun;
}GPIO_PINCONFIG_t;

typedef struct {
	//Pointers to hold the base address of the gpio peripheral
	GPIO_REG_DEF *pGPIOx; //This holds the base address of the GPIO port to which the pin belongs
	GPIO_PINCONFIG_t GPIO_PinConfig;
}GPIO_HANDLE_t;


//GPIO Driver Specific Modes


/*========================================================
 *                      GPIO API
 =========================================================*/

//GPIO Controll API
void GPIO_INIT (GPIO_HANDLE_t *pGPIOHandle); 		//Initilise The GPIO port
void GPIO_DEINIT (GPIO_REG_DEF *PGPIOx);		//Desable the GPIO Port

//GPIO Clock Controll
void GPIO_CLK_CR (GPIO_REG_DEF *pGPIOx, uint8_t EN_OR_DIS);	// GPIO Peripheral clock control

//GPIO Input pin And PORT mode
uint8_t GPIO_MOD_IN (GPIO_REG_DEF *pGPIOx, uint8_t PinNumber);	//GPIO Read input pin
uint16_t GPIO_MOD_IN_PORT (GPIO_REG_DEF *pGPIOx);	//GPIO Read input port

//GPIO OUTPUT PIN AND PORT MODE
void GPIO_MOD_OT (GPIO_REG_DEF *pGPIOx, uint8_t PinNumber, uint8_t Value); 	//GPIO Write Output pin
void GPIO_MOD_OT_PORT (GPIO_REG_DEF *pGPIOx, uint16_t Value); 	//GPIO Write Output port

//GPIO TOGGLE OUTPUT API
void GPIO_TOGGLE_OT(GPIO_REG_DEF *pGPIOx, uint8_t PinNumber);		//Toggling the GPIO Output pin

//GPIO IRQ HANDLING AND CONFIG
void GPIO_IRQ_IT_CFG (uint8_t IRQNumber, uint8_t EN_OR_DIS);		//Configure the GPIO Interrupt
void GPIO_IRQ_PRY_CFG(uint8_t IRQNumber,uint8_t IRQPriority);
void GPIO_IRQ_HND(uint8_t PinNumber); 		//Interrupt Handling





#endif /* INC_STM32F446XX_GPIO_H_ */
