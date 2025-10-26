#include<lpc21xx.h>
#define LED 1<<0
#define EINT0 14
void FIQ_isr(void) __irq
{
EXTINT = 0X01;
IOSET0 = LED;
IOCLR0 = LED;
}
int main()
{
unsigned int count = 0;
PINSEL1 |=0X01;
IODIR0 = LED;
EXTMODE = 0X00;
EXTPOLAR = 0X00;
VICIntSelect |=(1<<EINT0);
VICIntEnable |=(1<<EINT0);
while(1){
count++;
}
}
