#include<lpc21xx.h>
void delay_seconds(unsigned int sec)
{
	T0PR = 15000000-1;
	T0TCR = 0x01;
	while(T0TC<sec);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
void delay_milliseconds(unsigned int millisec)
{
	T0PR = 15000-1;
	T0TCR = 0x01;
	while(T0TC<millisec);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
void delay_microseconds(unsigned int microsec)
{
	T0PR = 15-1;
	T0TCR = 0x01;
	while(T0TC<microsec);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void delay_ms(int d)
{

	int i;
	for(;d>0;d--)
	for(i=12000;i>0;i--);
}