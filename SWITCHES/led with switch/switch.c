#include<lpc21xx.h>
#define LED 1<<8
#define sw 3
int main()
{
IODIR0 = LED;
while(1)
if(((IOPIN0 >>3)&1)==0)
{
IOCLR0 = LED;	
}
else
{
	IOSET0 = LED;
}
}
