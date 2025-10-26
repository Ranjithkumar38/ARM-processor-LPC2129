#include<lpc21xx.h>

#define IRQ_slot_en 0x20

#define EINT0_num 14

#define LED 1<<0

void config_EINT0(void);

void ext_int0_isr(void) __irq

{

EXTINT = 0x01;

IOSET0 = LED;

IOCLR0 = LED;

VICVectAddr = 0;

}


int main()

{

unsigned int count=0;

PINSEL1|= 0x01;

IODIR0 = LED;

config_EINT0();

EXTMODE = 0x00;

EXTPOLAR = 0x00;

VICIntEnable = 1<<EINT0_num;

while(1)
{

count++;

}

}

void config_EINT0(void)

{

VICIntSelect = 0;

VICVectCntl0 = IRQ_slot_en|EINT0_num;

VICVectAddr0 = (int)ext_int0_isr;

}