#include<lpc21xx.h>
unsigned char UART0_RX(void);
void UART0_STR(unsigned char*);
void UART0_TX(unsigned char ch);
void UART0_CONFIG(void);
int main()
{
	unsigned char rxbyte;
	UART0_CONFIG();
	while(1)
	{
		rxbyte = UART0_RX();
		UART0_TX(rxbyte);
		UART0_TX('\n');
	}
}
unsigned char UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void UART0_STR(unsigned char *s)
{
	while(*s)
		UART0_TX(*s++);
}
void UART0_TX(unsigned char ch)
{
	U0THR = ch;
	while(((U0LSR>>5)&1)==0);
}
void UART0_CONFIG(void)
{
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0LCR = 0x03;
}

	
	