volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;
volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_IDR   = (volatile unsigned int *)0x40020010;
volatile unsigned int *GPIOA_ODR   = (volatile unsigned int *)0x40020014;

void delay(void) {
    for (volatile int i = 0; i < 100000; i++);
}

void rcc() {
    *RCC_AHB1ENR |= (1 << 0); // Enable GPIOA clock
}

void general(void) {
    // PA0 input
    *GPIOA_MODER &= ~(3 << (0 * 2));

    // PA2 output
    *GPIOA_MODER &= ~(3 << (2 * 2));
    *GPIOA_MODER |=  (1 << (2 * 2));
}

void led_blink(void) {
    if ((*GPIOA_IDR & (1 << 0)) != 0) { // PA0 HIGH
        *GPIOA_ODR |=  (1 << 2); // LED ON
        delay();
        *GPIOA_ODR &= ~(1 << 2); // LED OFF
        delay();
    } else {
        *GPIOA_ODR &= ~(1 << 2); // LED OFF
        delay();
    }
}

int main() {
    rcc();
    general();
    while (1) {
        led_blink();
    }
}
