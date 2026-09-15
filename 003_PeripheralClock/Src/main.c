
#include <stdint.h>

#define adc_base_add  0x40012000UL
#define adc_Control_reg_offset 0x04UL
#define adc_Ctrl_Reg_Address  ((adc_base_add)+ (adc_Control_reg_offset))

//configuring the pll
#define RCC_BASE_ADDR 0x40023800UL
//OUr adc is on the APB2 bus periferal so get the address of it
#define APB2_OFFSET 0x44UL
#define APB2_ADDRESS ((RCC_BASE_ADDR)+ (APB2_OFFSET))


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	//Turn the Periferal clack
	uint32_t *pAPB2_ADDR = (uint32_t*)APB2_ADDRESS;
	*pAPB2_ADDR |= (1<<8);

	uint32_t *pADC_CR1_Add = (uint32_t*)adc_Ctrl_Reg_Address;
	*pADC_CR1_Add |= (1<<8);
	//this won't work untill you configure the clock, as periferal clock must be enabled

    /* Loop forever */
	for(;;);
}
