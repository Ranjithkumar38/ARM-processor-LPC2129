#include <lpc21xx.h>

void UART0_CONFIG(void);
void UART0_TX(unsigned char);
void UART0_TX_STRING(const char *s);
void delay(void);

int main() {
    // Set P0.3–P0.6 as input (clear bits in IODIR0)
    IODIR0 &= ~(0x78);  // 01111000 -> P0.3 to P0.6

    UART0_CONFIG();

    unsigned int prev_state = IOPIN0 & 0x78;  // Initial switch state

    while (1) {
        unsigned int curr_state = IOPIN0 & 0x78;  // Read current switch state

        // Falling edge detection (previous HIGH, now LOW)
        if (((prev_state & (1 << 3)) != 0) && ((curr_state & (1 << 3)) == 0)) {
            UART0_TX_STRING("SW1 IS PRESSED\r\n");
        } else if (((prev_state & (1 << 4)) != 0) && ((curr_state & (1 << 4)) == 0)) {
            UART0_TX_STRING("SW2 IS PRESSED\r\n");
        } else if (((prev_state & (1 << 5)) != 0) && ((curr_state & (1 << 5)) == 0)) {
            UART0_TX_STRING("SW3 IS PRESSED\r\n");
        } else if (((prev_state & (1 << 6)) != 0) && ((curr_state & (1 << 6)) == 0)) {
            UART0_TX_STRING("SW4 IS PRESSED\r\n");
        }

        prev_state = curr_state;  // Update previous state
        delay();  // Debounce delay
    }
}

void UART0_CONFIG(void) {
    PINSEL0 |= 0x00000005;  // Enable UART0 TxD0 (P0.0) and RxD0 (P0.1)
    U0LCR = 0x83;           // 8-bit data, 1 stop bit, enable DLAB
    U0DLL = 97;             // Baud rate = 9600 for 15MHz PCLK
    U0LCR = 0x03;           // Disable DLAB
}

void UART0_TX(unsigned char ch) {
    while (!(U0LSR & (1 << 5)));  // Wait for THR to be empty
    U0THR = ch;
}

void UART0_TX_STRING(const char *s) {
    while (*s) {
        UART0_TX(*s++);
    }
}

void delay(void) {
    for (volatile int i = 0; i < 100000; i++);  // Basic software delay
}

