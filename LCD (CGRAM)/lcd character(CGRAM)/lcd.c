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
void CGRAM_WRITE(unsigned char);
const unsigned char CGRAM_LUT[]={0x17,0x14,0x14,0x1f,0x05,0x05,0x1d,0x0,0x10,0x18,0x1c,0x1f,0x1e,0x1c,0x18,0x00};
//const unsigned char CGRAM_LIP[]={0x17,0x14,0x14,0x1f,0x05,0x05,0x1d};
int main()
{
LCD_INIT();

	
		CGRAM_WRITE(16);
    LCD_CMD(0x80);
		//LCD_DATA(0);
		//CGRAM_WRITE(8);
		LCD_CMD(0x81);
		LCD_DATA(1);


	
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
void CGRAM_WRITE(unsigned char nBYTE)
{
	char i;
	LCD_CMD(0x48);
	for(i=0;i<nBYTE;i++)
	LCD_DATA(CGRAM_LUT[i]);
//	LCD_CMD(0X48);
//	for(i=0;i<nBYTE;i++)
//	LCD_DATA(CGRAM_LIP[i]);
}