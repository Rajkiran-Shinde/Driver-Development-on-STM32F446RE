#ifndef INC_STM32F446XX_H_ //THis is what a Include Guard is, It helps to not add the same heder file twice
//If not Defined then Execute if Defined then dont execute anything and move away
#define INC_STM32F446XX_H_

#include<stdint.h> // This gives us the fixed width interger types,

//Generic Macros
#define ENABLE 				1
#define DISABLE 			0
#define SET 				ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET 		RESET

#define __vo volatile

//Simple Memory Map
#define FLASH_BASEADDR		 		0x08000000U //This is the Flash Base Address
#define SRAM1_BASEADDR 		 		0x20000000U  //112KB SRAM 1 Base Address
#define SRAM2_BASEADDR 		 		0x2001C000U  //16KB SRAM2 Base Address
#define ROM 				 		0x1FFF0000U  //System memory of 30KB base Address
#define SRAM_BASEADDR 				SRAM1_BASEADDR //This is the Base address of SRAM as SRAM1 starts from here only

/*
 * AHBx and APBx peripheral base Address
 */

#define PERIPH_BASEADDR				0x40000000U
#define APB1_PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2_PERIPH_BASEADDR 		0x40010000U
#define AHB1_PERIPH_BASEADDR 		0x40020000U
#define AHB2_PERIPH_BASEADDR 		0x50000000U

/*
 * Define The Base Address on the AHB1 Peripherals
 */
#define GPIOA_BASEADDR 				0x40020000U
#define GPIOB_BASEADDR 				0x40020400U
#define GPIOC_BASEADDR				0x40020800U
#define GPIOD_BASEADDR				0x40020C00U
#define GPIOE_BASEADDR				0x40021000U
#define GPIOF_BASEADDR				0x40021400U
#define GPIOG_BASEADDR				0x40021800U
#define GPIOH_BASEADDR				0x40021C00U

/*
 * Define the base Address on the APB1 bus Peripherals
 */

//I2C Base Address
#define I2C1_BASEADDR				0x40005400U
#define I2C2_BASEADDR				0x40005800U
#define I2C3_BASEADDR				0x40005C00U

//SPI Base Addess
#define SPI2_BASEADDR 				0x40003800U
#define SPI3_BASEADDR 				0x40003C00U

//USART Base Address
#define USART2_BASEADDR 			0x40004400U
#define USART3_BASEADDR 			0x40004800U

//UART Base Address
#define UART4_BASEADDR				0x40004C00U
#define UART5_BASEADDR				0x40005000U

//RCC BASE address
#define RCC_BASEADDR 				0x40023800U

/*
 * Define the base Address on the APB2 bus Peripherals
 */

//SPI Base ad
#define SPI1_BASEADDR 				0x40013000U

//USART Base Address
#define USART1_BASEADDR 			0x40011000U
#define USART6_BASEADDR 			0x40011400U


//External Interrupt/Event Controller
#define EXTI_BASEADDR 				0x40013C00U

#define SYSCFG_BASEADDR 			0x40013800U

/*
 * We are Creating a Structure for each of the registers of the peripherals,
 */

//Structure for the GPIO Registers
typedef struct {
	//Add volatile so that it should not optimize and work well
	__vo uint32_t MODER; //Mode Select Register
	__vo uint32_t OTYPER; //GPIO port output type register  Push pull, or Open drain
	__vo uint32_t OSPEEDER; //Output Speed Select Register
	__vo uint32_t PUPDR; //Pull up pull down Reg
	__vo uint32_t IDR; //Input Data Regitser
	__vo uint32_t ODR; //Output Data Register
	__vo uint32_t BSRR; //GPIO port bit set/reset register
	__vo uint32_t LCKR;// GPIO port configuration lock register
	__vo uint32_t AFR[2]; //Array for the AFRL and AFRH
	//Alternate Function low Reg (0-7) and lternate Function High Reg (8-15)  as 0 means low and 1 means High
}GPIO_REG_DEF;

//Structure for the RCC Registers
typedef struct {
	__vo uint32_t CR; //RCC control Reg
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	__vo uint32_t RESERVED1;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t RESERVED2[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	__vo uint32_t RESERVED3;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t RESERVED4[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	__vo uint32_t RESERVED5;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	__vo uint32_t RESERVED6[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t RESERVED7[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	__vo uint32_t PLLSAICFGR;
	__vo uint32_t DCKCFGR;
	__vo uint32_t CKGATENR;
	__vo uint32_t DCKCFGR2;
}RCC_REG_DEF;

/*
 * Peripheral Definitions, Peripherals Bus address typecasted to the xxxx_REG_DEF
 */

#define GPIOA ((GPIO_REG_DEF*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_REG_DEF*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_REG_DEF*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_REG_DEF*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_REG_DEF*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_REG_DEF*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_REG_DEF*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_REG_DEF*)GPIOH_BASEADDR)

//Peripheral Deff for RCC
#define RCC ((RCC_REG_DEF*)RCC_BASEADDR)


//*****************Enable Clock *****************//

/*
 * Clock Enable Macro For GPIOx
 */

#define GPIOA_CLK_EN() (RCC-> AHB1ENR |= (1<<0))
#define GPIOB_CLK_EN() (RCC-> AHB1ENR |= (1<<1))
#define GPIOC_CLK_EN() (RCC-> AHB1ENR |= (1<<2))
#define GPIOD_CLK_EN() (RCC-> AHB1ENR |= (1<<3))
#define GPIOE_CLK_EN() (RCC-> AHB1ENR |= (1<<4))
#define GPIOF_CLK_EN() (RCC-> AHB1ENR |= (1<<5))
#define GPIOG_CLK_EN() (RCC-> AHB1ENR |= (1<<6))
#define GPIOH_CLK_EN() (RCC-> AHB1ENR |= (1<<7))

/*
 * Clock Enable for I2C Peri
 */
#define I2C1_CLK_EN() (RCC-> APB1ENR |= (1<<21))
#define I2C2_CLK_EN() (RCC-> APB1ENR |= (1<<22))
#define I2C3_CLK_EN() (RCC-> APB1ENR |= (1<<23))

/*
 * Clock Enable for SPI Peripheral
 */
#define SPI1_CLK_EN() (RCC-> APB2ENR |= (1<<12)) //SPI 1 is on the APB2
#define SPI2_CLK_EN() (RCC-> APB1ENR |= (1<<14))
#define SPI3_CLK_EN() (RCC-> APB1ENR |= (1<<15))

/*
 * Clock Enable For UART Peripheral
 */
#define UART4_CLK_EN() (RCC-> APB1ENR |= (1<<19))
#define UART5_CLK_EN() (RCC-> APB1ENR |= (1<<20))

/*
 * Clock Enable for USART Peripheral
 */
#define USART2_CLK_EN() (RCC-> APB1ENR |= (1<<17))
#define USART3_CLK_EN() (RCC-> APB1ENR |= (1<<18))

#define USART1_CLK_EN() (RCC-> APB2ENR |= (1<<4))
#define USART6_CLK_EN() (RCC-> APB2ENR |= (1<<5))

//SYSCFG clock Enable
#define SYSCFG_CLK_EN() (RCC-> APB2ENR |= (1<<14))

//*****************Disable Clock *****************//
/*
 * Clock Disable Macro For GPIOx
 */

#define GPIOA_CLK_DI()    (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_CLK_DI()    (RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_CLK_DI()    (RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_CLK_DI()    (RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_CLK_DI()    (RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_CLK_DI()    (RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_CLK_DI()    (RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_CLK_DI()    (RCC->AHB1ENR &= ~(1<<7))


/*
 * Clock Disable For I2C Peripheral
 */

#define I2C1_CLK_DI()     (RCC->APB1ENR &= ~(1<<21))
#define I2C2_CLK_DI()     (RCC->APB1ENR &= ~(1<<22))
#define I2C3_CLK_DI()     (RCC->APB1ENR &= ~(1<<23))


/*
 * Clock Disable For SPI Peripheral
 */

#define SPI1_CLK_DI()     (RCC->APB2ENR &= ~(1<<12))
#define SPI2_CLK_DI()     (RCC->APB1ENR &= ~(1<<14))
#define SPI3_CLK_DI()     (RCC->APB1ENR &= ~(1<<15))


/*
 * Clock Disable For UART Peripheral
 */

#define UART4_CLK_DI()    (RCC->APB1ENR &= ~(1<<19))
#define UART5_CLK_DI()    (RCC->APB1ENR &= ~(1<<20))


/*
 * Clock Disable For USART Peripheral
 */

#define USART1_CLK_DI()   (RCC->APB2ENR &= ~(1<<4))
#define USART2_CLK_DI()   (RCC->APB1ENR &= ~(1<<17))
#define USART3_CLK_DI()   (RCC->APB1ENR &= ~(1<<18))
#define USART6_CLK_DI()   (RCC->APB2ENR &= ~(1<<5))


/*
 * SYSCFG Clock Disable
 */

#define SYSCFG_CLK_DI()   (RCC->APB2ENR &= ~(1<<14))

/*
 * Macros to Reset the GPIOx Peripherals
 */
#define GPIOA_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<0)) ; (RCC -> AHB1RSTR &=~(1<<0));} while (0)
#define GPIOB_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<1)) ; (RCC -> AHB1RSTR &=~(1<<1));} while (0)
#define GPIOC_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<2)) ; (RCC -> AHB1RSTR &=~(1<<2));} while (0)
#define GPIOD_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<3)) ; (RCC -> AHB1RSTR &=~(1<<3));} while (0)
#define GPIOE_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<4)) ; (RCC -> AHB1RSTR &=~(1<<4));} while (0)
#define GPIOF_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<5)) ; (RCC -> AHB1RSTR &=~(1<<5));} while (0)
#define GPIOG_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<6)) ; (RCC -> AHB1RSTR &=~(1<<6));} while (0)
#define GPIOH_REG_RESET()			do{(RCC -> AHB1RSTR |= (1<<7)) ; (RCC -> AHB1RSTR &=~(1<<7));} while (0)


#endif /* INC_STM32F446XX_H_ */
