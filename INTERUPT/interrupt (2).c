#include<lpc21xx.h>
#define EXINT_num 14
#define LED 1<<0
void non_vect_isr(void) __irq
{
EXTINT = 0X01;
IOSET0 = LED;
IOCLR0 = LED;
VICVectAddr = 0;
}
int main()
{
unsigned int count = 0;
PINSEL1|= 0X01;
IODIR0 = LED;
VICIntSelect = 0;
VICDefVectAddr = (int)non_vect_isr;
EXTMODE = 0X01;
EXTPOLAR = 0X00;
VICIntEnable = 1<<EXINT_num;
while(1)
{
count++;
}
}
