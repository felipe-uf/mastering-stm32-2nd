typedef unsigned long uint32_t;

/* memory and peripheral start addresses */
#define FLASH_BASE      0x08000000
#define SRAM_BASE       0x20000000
#define PERIPH_BASE     0x40000000
#define IO_BASE		    0x50000000

/* Work out end of RAM address as initial stack pointer */
#define SRAM_SIZE       20*1024     // STM32L073RZ has 20 KB of RAM
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)

/* RCC peripheral addresses applicable to GPIOA */
#define RCC_BASE        (PERIPH_BASE + 0x21000)
#define RCC_IOPENR      ((uint32_t*)(RCC_BASE + 0x2C))

/* GPIOA peripheral addresses */
#define GPIOA_BASE      (IO_BASE + 0x0)
#define GPIOA_MODER     ((uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       ((uint32_t*)(GPIOA_BASE + 0x14))

/* User functions */
int main(void);
void delay(uint32_t count);

/* Minimal vector table */
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)SRAM_END,   // initial stack pointer
    (uint32_t *)main        // main as Reset_Handler
};

int main() {
    /* enable clock on GPIOA peripheral */
    *RCC_IOPENR = 0x1;
    *GPIOA_MODER = 0x400; // Sets MODER[11:10] = 0x1

    while(1) {
    	*GPIOA_ODR = 0x20;
        delay(100000);
    	*GPIOA_ODR = 0x0;
        delay(100000);
    }
}

void delay(uint32_t count) {
    while(count--);
}
