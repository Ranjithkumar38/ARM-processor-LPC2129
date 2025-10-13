#include<lpc21xx.h>
#define LED 1<<8
#define sw 3
int main()
{
IODIR0 = LED|1<<9|1<<10|1<<21;
while(1)
if(((IOPIN0 >>3)&1)==0)
IOCLR0 = LED;
else if(((IOPIN0 >>4)&1)==0)
IOCLR0 = 1<<9;
else if (((IOPIN0 >>5)&1)==0)
IOCLR0 = 1<<10;
else if (((IOPIN0>>6)&1)==0)
IOCLR0 =1<<21; 
else
IOSET0 = LED|1<<9|1<<10|1<<21;
}
