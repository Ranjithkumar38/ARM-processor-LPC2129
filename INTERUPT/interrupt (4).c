#include<lpc21xx.h>
#define EXINT0_num 14
#define EXINT1_num 15
#define LED 1<<0
void non_vect_isr(void) __irq
{
if((VICIRQStatus>>14)&1)
{
EXTINT = 0X01;
IOSET0 = LED;
IOCLR0 = LED;

}
else if((VICIRQStatus>>15)&1)
{
EXTINT = 0X02;
IOSET0 = LED;
IOCLR0 = LED;

}

VICVectAddr = 0;
}

int main()
{
unsigned int count = 0;
PINSEL1|= 0X01;
PINSEL0|= 1<<29;
IODIR0 = LED;
VICIntSelect = 0;
VICDefVectAddr = (int)non_vect_isr;
EXTMODE = 0X03;
EXTPOLAR = 0X00;
VICIntEnable = 1<<EXINT0_num|1<<EXINT1_num;
while(1)
{
count++;
}
}
