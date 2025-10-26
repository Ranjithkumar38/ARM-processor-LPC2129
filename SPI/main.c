#include<lpc21xx.h>
#include "lcd.c"
#define CCLK 60000000
#define SPI_SPEED 100000
#define PCLK (CCLK/4)
#define LOADVAL (PCLK/SPI_SPEED)
#define STF 7
#define CS 1<<1
#define M_EN 1<<5
#define MODE3 3<<3
unsigned char SPI_MASTER(unsigned char);
float SPI_READ_WITH_WRITE(unsigned char);
void SPI_INIT(void);

int main()
{
	float f;
	SPI_INIT();
	LCD_INIT();
	LCD_STRING("MCP3204--");
	IOSET0 |= CS;
	while(1)
	{
		f = SPI_READ_WITH_WRITE(0x00);
		delay_ms(1000);
		//temp = f/0.01;
		LCD_CMD(0xc0);
		LCD_FLOAT(f);
}
	}
void SPI_INIT(void)
{
	PINSEL0 |= 0x1500;
	S0SPCCR = LOADVAL;
	S0SPCR = (M_EN)|(MODE3);
	IODIR0 |= CS;
	
}
float SPI_READ_WITH_WRITE(unsigned char chan){
	int adcval;
	unsigned char  hbyte,nbyte;
	IOCLR0 |=CS;
SPI_MASTER(0X6);
nbyte=SPI_MASTER(chan<<6);
hbyte=SPI_MASTER(0x00);
IOSET0 |= CS;
adcval= (((nbyte&0x0f)<<8)|(hbyte));
return ((adcval*3.3)/4096);
}
unsigned char SPI_MASTER(unsigned char data)
{
	unsigned char temp;
	temp = S0SPSR;
	S0SPDR = data;
	while(((S0SPSR>>STF)&1)==0);
	return S0SPDR;
}

	
	
	
	
	

	

