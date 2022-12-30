#include "stm32f103x6.h"
#include "delay.h"
#include "usblib.h"
#include "gpio.h"

#define USB_DM PA11
#define USB_DP PA12
#define USB_EN PA10

#define LED_R PB13
#define LED_B PB14
#define LED_G PB15

volatile bool EVENT_1HZ = false;
volatile bool EVENT_10HZ = false;
volatile bool EVENT_100HZ = false;
volatile bool EVENT_1000HZ = false;
volatile bool EVENT_TIMEOUT = false;

/* USB setup */
void usb_setup(void)
{	
	// PA11 as DM, PA12 as DP
	gpio_mode(USB_DM, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTERNATE_OPEN_DRAIN);
	gpio_mode(USB_DP, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_ALTERNATE_OPEN_DRAIN);
	
	// PA10 as controllable 1k5 pull-up at DP line for enumeration control
	gpio_mode(USB_EN, GPIO_MODE_OUTPUT_2MHZ, GPIO_CNF_OUTPUT_GENERAL_PUSH_PULL);
	gpio_write(USB_EN, 0);
  USBLIB_Init();
	gpio_write(USB_EN, 1);
}


/*
HSI frequency RC osc: 8MHz
PLL (x12) -> MCU frequency is (8MHz / 2) * 12 = 48 MHz
*/
void rcc_init(void)
{
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	// Change System Clock to HSI
	RCC->CFGR &= ~RCC_CFGR_SW;
  while ((RCC->CFGR & RCC_CFGR_SWS) != 0);
		
	// Turn on external clock (HSE)
	//RCC->CR |= RCC_CR_HSEON;
	//while ((RCC->CR & RCC_CR_HSERDY) == 0);
	
	// Set flash memory access latency to 2 cycles + enable prefetch buffer
	FLASH->ACR = FLASH_ACR_LATENCY_2 | FLASH_ACR_PRFTBE;
	
	// PLL input clock (4MHz) x 12
	RCC->CFGR |= RCC_CFGR_PLLMUL12;
	
	// HSE as PLL input clock
	//RCC->CFGR |= RCC_CFGR_PLLSRC; 
	
	// Clock for APB1 divided 2x (to get 24MHz)
	RCC->CFGR |= RCC_CFGR_PPRE1_2;
	
	// USB clock not divided by 1.5x
	RCC->CFGR |= RCC_CFGR_USBPRE;
	
	// Turn on PLL
	RCC->CR |= RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) == 0);
	
	// Change main clock to PLL
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	
	// Disable internal clock to save power
	//RCC->CR &= ~RCC_CR_HSION;
	
	// Disable LSE clock
	RCC->BDCR &= ~RCC_BDCR_LSEON;
}

int main(void)
{
	rcc_init();
	gpio_init();
	stk_init();
	usb_setup();
	
	gpio_mode(LED_R, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_GENERAL_PUSH_PULL);
	gpio_mode(LED_B, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_GENERAL_PUSH_PULL);
	gpio_mode(LED_G, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_GENERAL_PUSH_PULL);
	
	gpio_write(LED_R, 1);
	gpio_write(LED_B, 0);
	gpio_write(LED_G, 0);
	
	int i = 0;
	while(1) {		
		if (EVENT_10HZ) {
			EVENT_10HZ = false;
		}
		
		if (EVENT_1HZ) {
			EVENT_1HZ = false;
		}
	}
}

void uUSBLIB_DataReceivedHandler(uint16_t *Data, uint16_t Length)
{
	// simple echo
	USBLIB_Transmit(Data, Length);
}
