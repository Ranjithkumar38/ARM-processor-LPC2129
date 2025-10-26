#include<lpc21xx.h>
#define green 1<<7
#define red 1<<8
#define SA 0x50
#define DWA 0x00
#define CLK 60000000
#define PCLK (CLK/4)
#define speed 100000
#define loadval ((PCLK/speed)/2)
#define SI_BIT 3
#define START 5
#define STOP 4
#define ENABLE 6
void i2c_start();
void i2c_configure();
void i2c_stop();
void i2c_write(unsigned char);
unsigned char i2c_nack();
void i2c_restart();
void eeprom_write(unsigned char,unsigned char,unsigned char);
unsigned char eeprom_read(unsigned char,unsigned char);
void delay_ms(int);
int main(){
	unsigned char t;
	i2c_configure();
	delay_ms(1000);
	IODIR0 = red|green;
	eeprom_write(SA,DWA,'A');
	delay_ms(2000);
	t=eeprom_read(SA,DWA);
	delay_ms(2000);
	if(t=='A'){
		IOSET0 |= green;
	}
	else{
		IOSET0 |= red;
	}
	while(1);
}

void delay_ms(int n){
	T0PR = 15000-1;
	T0TCR = 0X01;
	while(T0TC<n);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
unsigned char i2c_nack(){
	I2CONSET = 0x00;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	return I2DAT;
}

void eeprom_write(unsigned char S_A,unsigned char D_A,unsigned char DT){
	i2c_start();
	i2c_write(S_A<<1);
	i2c_write(D_A);
	i2c_write(DT);
	i2c_stop();
	delay_ms(10);
}

unsigned char eeprom_read(unsigned char RSA,unsigned char RDA){
	unsigned char x;
	i2c_start();
	i2c_write(RSA<<1);
	i2c_write(RDA);
	i2c_restart();
	i2c_write(RSA<<1|1);
	x = i2c_nack();
	i2c_stop();
	delay_ms(2000);
	return x;
}

void i2c_configure(){
	PINSEL0 |=0x50;
	I2SCLL = loadval;
	I2SCLH = loadval;
	I2CONSET = 1<<ENABLE;
}

void i2c_start(){
	I2CONSET = 1<<START;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR = 1<<START;
}

void i2c_write(unsigned char p){
	I2DAT = p;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
}

void i2c_stop(){
	I2CONSET = 1<<STOP;
	I2CONCLR = 1<<SI_BIT;
}

void i2c_restart(){
	I2CONSET = 1<<START;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR = 1<<START;
}
	