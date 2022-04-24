//This file is experimenting the concept of BareMetal building using the full registers address, how can it be done first you'll need the 
//user reference manual and afterword you will be able to construct the memory map, no C include libraries and no using HAL abstractions.
//The LED is at port A pin 5 

#define PERIPHERAL_BASE_ADDRESS  	0x40000000UL//Thats the address from where of the peripherals registers addresses are located 
#define AHB1_PERIPHERAL_OFFSET    0x00020000UL//The offset from the base address, in order to reach to the address of the AHB1 bus register which Enables the AHB1 bus in 
//order to control the operation of the LED
#define AHB1_PERIPHERAL_BASE		  (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define RCC_OFFSET			          (0x00001000UL)//
#define RCC_BASE			            (AHB1_PERIPHERAL_BASE +RCC_OFFSET)

#define AHB2_PERIPHERAL_OFFSET	 (0x08000000UL)
#define AHB2_PERIPHERAL_BASE    (PERIPHERAL_BASE_ADDRESS + AHB2_PERIPHERAL_OFFSET)
#define GPIOA_OFFSET            (0x00000000UL)
#define GPIOA_BASE		          (AHB2_PERIPHERAL_BASE + GPIOA_OFFSET)

#define RCC_AHBEN_REGISTER_OFFSET	 (0x14UL)
#define RCC_AHBEN_REGISTER			   (*(volatile unsigned int *)(RCC_BASE +	RCC_AHBEN_REGISTER_OFFSET))

#define GPIOA_MODE_REGISTER_OFFSET (0x00UL)
#define GPIOA_MODE_REGISTER		     (*(volatile unsigned int *)(GPIOA_BASE +  GPIOA_MODE_R_OFFSET))

#define GPIOA_OD_REGISTER_OFFSET	  (0x14UL)
#define GPIOA_OD_REGISTER		        (*(volatile unsigned int *)(GPIOA_BASE +  GPIOA_OD_R_OFFSET))


#define GPIOAEN					      (1U<<17)    // 0b 0000 0000 0000 0010 0000 0000 0000 0000
#define LED       		        (1U<<5)


int main(void)
{
	/*Enable clock access to gpioa*/
	RCC_AHBEN_REGISTER |=  GPIOAEN;

	/*Set PA5 as output pin*/
	GPIOA_MODE_REGISTER |= (1U<<10);
	GPIOA_MODE_REGISTER &=~(1U<<11);


	while(1)
	{
		/*Toggle the LED*/
		GPIOA_OD_R ^= USER_LED;
		for(int i=0;i<14500000;i++){} //for 8MHz clock aprrox. 1 sec

	}
}
