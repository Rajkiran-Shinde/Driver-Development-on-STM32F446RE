#include <stdint.h>

//configuring the pll
#define RCC_BASE_ADDR 0x40023800UL

//OUr adc is on the APB2 bus periferal so get the address of it
#define RCC_CFGR 0x08UL
#define RCC_CFGR_ADDR ((RCC_BASE_ADDR)+ (RCC_CFGR))

int main(void)
{
	uint32_t *pRCC_CFGR_REG = (uint32_t*)RCC_CFGR_ADDR;

	//Clear the bit 21 and 22 for the MCO1
	*pRCC_CFGR_REG &= ~(0x3<<21);
    /* Loop forever */
	for(;;);
}
