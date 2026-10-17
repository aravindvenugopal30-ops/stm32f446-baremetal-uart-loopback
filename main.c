#include <stdint.h>
#define PERIPH_BASE                 (0x40000000UL)

// RCC
#define RCC                         (0x40023800UL)

#define AHB1_OFFSET                 (0x20000UL)
#define AHB1_BASE                   (PERIPH_BASE + AHB1_OFFSET)

#define GPIOA_OFFSET                (0x0000UL)
#define GPIOA_BASE                  (AHB1_BASE + GPIOA_OFFSET)

#define AHB1ENR_OFFSET              (0x30UL)
#define RCC_AHB1                    (*(volatile unsigned int *)(AHB1ENR_OFFSET + RCC))

#define MODER_OFFSET                (0x00)
#define GPIOA_MODER                 (*(volatile unsigned int *)(MODER_OFFSET + GPIOA_BASE))

#define APB1_OFFSET                 (0x0000UL)
#define APB1_BASE                   (PERIPH_BASE + APB1_OFFSET)

#define USART2_OFFSET               (0x4400UL)
#define USART2_BASE                 (APB1_BASE + USART2_OFFSET)

#define APB1ENR_OFFSET              (0x40UL)
#define RCC_APB1ENR                 (*(volatile unsigned int *)(RCC + APB1ENR_OFFSET))

#define AFRL_OFFSET                 (0x20UL)
#define GPIOA_AFRL                  (*(volatile unsigned int *)(GPIOA_BASE + AFRL_OFFSET))

#define BRR_OFFSET                  (0x08UL)
#define USART2_BRR                  (*(volatile unsigned int *)(USART2_BASE + BRR_OFFSET))

#define CR1_OFFSET                  (0x0CUL)
#define USART2_CR1                  (*(volatile unsigned int *)(USART2_BASE + CR1_OFFSET))

#define DR_OFFSET                   (0x04UL)
#define USART2_DR                   (*(volatile unsigned int *)(DR_OFFSET + USART2_BASE))

#define SR_OFFSET                   (0x00UL)
#define USART2_SR                   (*(volatile unsigned int *)(USART2_BASE + SR_OFFSET))


#define UARTENR                     (1U<<17)
#define GPIOAENR                    (1U<<0)

#define SYS_FR                      16000000
#define APB1_CLK                    SYS_FR
#define UART_BAUDRATE               115200

#define CR1_TE                      (1U<<3)
#define UASRT_EN                    (1U<<13)
#define SR_TXE                      (1<<7)
#define SR_RXNE                     (1<<5)


static void uart_set_baudrate(uint32_t periphclk, uint32_t BaudRate);
static uint16_t compute_uart_div(uint32_t periphclk, uint32_t BaudRate);
void uar2_tx_init(void);
void uart2_write(int ch);
void uart2_write_string(char *str);
char uart2_read(void);

void uart_rx_init();

int main(){

    uar2_tx_init();
    uart_rx_init();

    while (1)
    {

     char recive_char=uart2_read();

     uart2_write(recive_char);

}
}

void uar2_tx_init(void){
    RCC_AHB1 |= GPIOAENR;

    GPIOA_MODER &= ~(1U << 4);
    GPIOA_MODER |= (1U << 5);

    GPIOA_AFRL |= (1U << 8);
    GPIOA_AFRL |= (1U << 9);
    GPIOA_AFRL |= (1U << 10);
    GPIOA_AFRL &= ~(1U << 11);

    RCC_APB1ENR |= UARTENR;

    uart_set_baudrate(APB1_CLK, UART_BAUDRATE);

    USART2_CR1 = CR1_TE;
    USART2_CR1 |= UASRT_EN;
}


void uart2_write(int ch){
    while(!(USART2_SR & SR_TXE));
    USART2_DR = (ch & 0XFF);
}


void uart2_write_string(char *str) {
    while (*str) {
        uart2_write(*str);
        str++;
    }
}

static void uart_set_baudrate(uint32_t periphclk, uint32_t BaudRate)
{
    USART2_BRR = compute_uart_div(periphclk, BaudRate);
}

static uint16_t compute_uart_div(uint32_t periphclk, uint32_t BaudRate)
{
    return ((periphclk + (BaudRate / 2U)) / BaudRate);
}

void uart_rx_init(){

	 RCC_AHB1 |= GPIOAENR;

	 GPIOA_MODER &=~(1U<<5);
	 GPIOA_MODER |=(1U<<6);

	 GPIOA_AFRL |=(1U<<12);
	 GPIOA_AFRL |=(1U<<13);
	 GPIOA_AFRL |=(1U<<14);
	 GPIOA_AFRL &=~(1U<<15);

	  RCC_APB1ENR |= UARTENR;


	    uart_set_baudrate(APB1_CLK, UART_BAUDRATE);

	    USART2_CR1 |=(1U<<2);
	    USART2_CR1 |=(1U<<13);


}

char uart2_read(void)
{

    while (!(USART2_SR & SR_RXNE));
    return (char)(USART2_DR & 0xFF);
}





