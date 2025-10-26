#include<lpc21xx.h>
unsigned char UART0_RX(void);
void UART0_STR(unsigned char*);
void UART0_TX(unsigned char ch);
void UART0_CONFIG(void);
void delay_ms(int d)
{
    int i;
    for (; d > 0; d--)
        for (i = 12000; i > 0; i--); // Empty loop body ends with semicolon
}


int main()
{
	unsigned char rxbyte;
	unsigned int i,j;
	IODIR0 = 0XFF0000;
	
	UART0_CONFIG();
	while(1)
	{
		rxbyte = UART0_RX();
		UART0_TX(rxbyte);
		switch(rxbyte){
			case '1':
			for (i = 16; i <= 23; i++) {
        IOSET0 = 1 << i;
        delay_ms(50);
        IOCLR0 = 1 << i;
			}
				break;
				
			  
		 case '2':
		 for(i=23;i>=16;i--){
				IOSET0 =1<<i;
				delay_ms(50);
				IOCLR0 = 1<<i;
		 } 
				break;
				
		 case '3':
		 for(i = 23, j = 16; i >= 20 && j <= 19; i--, j++) {
    IOSET0 = (1 << i) | (1 << j);
    delay_ms(50);
    IOCLR0 = (1 << i) | (1 << j);
				
		}
				break;
		
	}
}
unsigned char UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}

void UART0_TX(unsigned char ch)
{
	U0THR = ch;
	while(((U0LSR>>5)&1)==0);
}
void UART0_CONFIG(void)
{
	PINSEL0 |= 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0LCR = 0x03;
}
