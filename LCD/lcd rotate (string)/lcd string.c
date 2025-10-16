#include <lpc21xx.h>

#define LCD_D 0xFF
#define RS (1 << 8)
#define EN (1 << 9)

void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INIT(void);
void LCD_STRING(unsigned char, char*);
void delay_ms(unsigned int);

char name[] = "RANJITH";

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

void LCD_INIT(void) {
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

int main() {
    char temp[17];
    int i, j, k;

    LCD_INIT();

    while (1) {
        // 1. SHIFT "RANJITH" from left (0x80) to right (0x88)
        for (i = 0; i <= (15 - 7); i++) {
            LCD_CMD(0x01);
            LCD_STRING(0x80 + i, name);
            delay_ms(100);
        }

        // 2. BUILD PATTERN: gradually prepend from end and shrink beginning
        for (i = 1; i <= 7; i++) {
            LCD_CMD(0x01);
            k = 0;

            // Append last i chars at start (reversed scrolling effect)
            for (j = 0; j < i; j++)
                temp[k++] = name[7 - i + j];

            // Add fixed spacing (simulate scroll gap)
            for (j = 0; j < 8; j++)
                temp[k++] = ' ';

            // Add first (7 - i) chars after space
            for (j = 0; j < 7 - i; j++)
                temp[k++] = name[j];

            temp[k] = '\0';

            LCD_STRING(0x80, temp);
            delay_ms(100);
        }
    }
}
