#include<lpc21xx.h>
//#include"delay.h"
#include"lcd_header.h"
char count=0;
void delay(int n){
	TOPR = 15000000-1;
	TOTCR = 0x01;
	while(TOTC<2);
	TOTCR = 0X03;
	TOTCR = 0X00;
}
void ext_int0_isr(void) __irq
{
	

	EXTINT=0x01;
	lcd_cmd(0xc1);
	if(T0PC==0)
	a=6;
	else
	a=T0PC;
	lcd_integer(a);
	count++;
	lcd_cmd(0xC9);
	lcd_integer(count);
	delay(100);
	lcd_cmd(0X80);
	VICVectAddr=0;	   
}  
int main()
{
		
	  PINSEL1=0x1;
	  IOSET0=0x1;
	  VICIntSelect=0;

	  VICVectCntl0=0x20|14;
	  VICVectAddr0=(unsigned long)ext_int0_isr;

	  EXTMODE=0x00;
	  EXTPOLAR=0x00;
	  
	  VICIntEnable=1<<14;
	  

	  lcd_init();
	  lcd_integer(count);
	  	 while(1){
		 T0PR=6-1;
		 T0TCR=0x01;	
		 //T0TCR=0x03;
		T0TCR=0x00;
	  lcd_cmd(0x80);
	  lcd_string("DICE    COUNT");
	  }
}
