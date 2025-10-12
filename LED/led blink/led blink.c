#include<lpc21xx.h>
void delay_ms(int d)
{

	int i;
	for(;d>0;d--)
	for(i=12000;i>0;i--);
}

int main()
{
	PINSEL0=0x00;
	IODIR0=0X01;
	while(1)
	{
		IOSET0 = 0x01;
		delay_ms(50);
		IOCLR0 = 0x01;
		delay_ms(50);
	}
}
	
	