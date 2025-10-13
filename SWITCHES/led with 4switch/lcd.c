#include<lpc21xx.h>
#define LCD_D 0xff
#define RS 1<<8
#define EN 1<<9  
void LCD_STRING(unsigned char *);
void delay_ms(unsigned int ms);
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_NUM(unsigned int);
void LCD_SUM(unsigned int);

int main()
{
	int num=123;
	unsigned char buf[50];
LCD_INIT();
	while(1)
	{
LCD_CMD(0x80);
sprintf(buf,"%d",num);
	}
}
void delay_ms(unsigned int ms)
{
T0PR=15000-1;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=0X03;
T0TCR=0X0;	
}
void LCD_INIT(void)
{
IODIR0=LCD_D|RS|EN;
LCD_CMD(0X01);
LCD_CMD(0X02);
LCD_CMD(0X0C);
LCD_CMD(0X38);
}
void LCD_CMD(unsigned char cmd)
{
IOCLR0=LCD_D;
IOSET0=cmd;
IOCLR0=RS;
IOSET0=EN;
delay_ms(2);
IOCLR0=EN;	
}
void LCD_DATA(unsigned char d)
{
IOCLR0=LCD_D;
IOSET0=d;
IOSET0=RS;
IOSET0=EN;
delay_ms(2);
IOCLR0=EN;	
	}
void LCD_STRING(unsigned char *s)
{
while(*s)
{
LCD_DATA(*s++);
}
}
void LCD_NUM(unsigned int num)
{
	int x,sum=0;
while(num!=0)
{
x=num%10;
	sum+=x;
	num=num/10;
}
LCD_SUM(sum);
}
void LCD_SUM(unsigned)