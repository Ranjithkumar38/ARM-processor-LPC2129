
#include<lpc21xx.h>
#define LCD_D 0xff00
#define En 1<<17
#define Rs 1<<16
void delay_ms(int ms)
{
	T0PR = 15000-1;
T0TCR = 0x01;
	while(T0TC<ms);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void LCD_CMD(unsigned char cmd)
{
	IOCLR0 = LCD_D;
	IOSET0 = cmd<<8;
	IOCLR0 = Rs;
	IOSET0 = En;
	delay_ms(2);
	IOCLR0 = En;
}


void LCD_INIT(void)
{
IODIR0 |= LCD_D|Rs|En;
LCD_CMD(0x01);
LCD_CMD(0x02);
LCD_CMD(0x38);
LCD_CMD(0x0c);
LCD_CMD(0x80);
	
}


void LCD_DATA(unsigned char d)
{
IOCLR0 = LCD_D;
IOSET0 = d<<8;
IOSET0 = Rs;
IOSET0 = En;
delay_ms(2);
IOCLR0 = En;
}
void LCD_STRING(unsigned char*s)
{
while(*s)
LCD_DATA(*s++);
}

void LCD_INTEGER(int n)
{
	char arr[5];
	int i=0;
	if(n==0)
	{
		LCD_DATA('0');
  }
	else
	{	
		if(n<0)
		{
			LCD_DATA('-');
			n=-n;
    }
	 while(n>0)
	 {
		 arr[i++] = n%10;
		 n=n/10;
   }
	 for(i=i-1;i>=0;i--)
	   LCD_DATA(arr[i]+48);
  }
}
void LCD_FLOAT(float f)
{
 int temp;
 temp=f;
 LCD_INTEGER(temp);
 LCD_DATA('.');
 temp=(f-temp)*100;
 LCD_INTEGER(temp);	
}

