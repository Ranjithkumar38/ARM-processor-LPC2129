#include <lpc21xx.h>
#define LCD_D 0xFF
#define RS (1 << 8)
#define EN (1 << 9)

void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INIT(void);
void LCD_STRING(unsigned char, char*);
void delay_ms(unsigned int);

//char name[] = "RANJITH";

void delay_ms(unsigned int ms) {
    T0PR = 15000 - 1;
    T0TC = 0;
    T0TCR = 1;
    while (T0TC < ms);
    T0TCR = 0;
	
}

void LCD_CMD(unsigned char cmd) {
    IOCLR0 = LCD_D;
    IOSET0 = cmd;
    IOCLR0 = RS;
    IOSET0 = EN;
    delay_ms(2);
    IOCLR0 = EN;
}

void LCD_DATA(unsigned char data) {
    IOCLR0 = LCD_D;
    IOSET0 = data;
    IOSET0 = RS;
    IOSET0 = EN;
    delay_ms(2);
    IOCLR0 = EN;
}

void LCD_INIT(void) 
	
{
    IODIR0 = LCD_D | RS | EN;
    LCD_CMD(0x38);  // 8-bit, 2 lines
    LCD_CMD(0x0C);  // Display ON, cursor OFF
    LCD_CMD(0x01);  // Clear
    LCD_CMD(0x06);  // Auto increment
    delay_ms(2);
}

void LCD_STRING(unsigned char pos, char *s) {
    LCD_CMD(pos);
    while (*s)
        LCD_DATA(*s++);
}


