#include<lpc21xx.h>
#include"delay.h"
int main()
{
	PINSEL0 = 0x00;
	IODIR0 =0xff;
	
	while(1)
	{
		
		
		IOSET0 = 0x81;
		delay_ms(50);
		IOCLR0 = 0x81;
		delay_ms(50);
		IOSET0=0x42;
		delay_ms(50);
		IOCLR0=0x42;
		delay_ms(50);
		IOSET0=0x24;
		delay_ms(50);
		IOCLR0=0x24;
		delay_ms(50);
		IOSET0=0x18;
		delay_ms(50);
		IOCLR0=0x18;
		delay_ms(50);
}
	}