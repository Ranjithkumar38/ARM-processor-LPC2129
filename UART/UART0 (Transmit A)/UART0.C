#include<lpc21xx.h>
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
int main()
{
	UART0_CONFIG();
	while(1)
	{
		UART0_TX('A');
	}
}
void UART0_CONFIG(void)
{
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0LCR = 0x03;
}
void UART0_TX(unsigned char ch)
{
	U0THR = ch;
while(((U0LSR>>5)&1)==0);
}
