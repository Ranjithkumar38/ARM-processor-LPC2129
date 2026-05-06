#include <lpc21xx.h>

#define RTC_ADDR_WRITE 0xD0  // DS1307 I2C address + Write bit
#define RTC_ADDR_READ  0xD1  // DS1307 I2C address + Read bit

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char data);
unsigned char I2C_Read(unsigned char ack);
void RTC_SetTime(unsigned char sec, unsigned char min, unsigned char hour);
void RTC_GetTime(unsigned char *sec, unsigned char *min, unsigned char *hour);

unsigned char bcd_to_dec(unsigned char val) { return ((val >> 4) * 10) + (val & 0x0F); }
unsigned char dec_to_bcd(unsigned char val) { return ((val / 10) << 4) | (val % 10); }

int main(void) {
    unsigned char sec, min, hour;

    I2C_Init();
    
    // Example: Set time to 12:45:30
    RTC_SetTime(30, 45, 12);

    while (1) {
        RTC_GetTime(&sec, &min, &hour);
        // You can send time via UART or display on LCD
    }
}

void I2C_Init(void) {
    PINSEL0 |= 0x00000050;    // P0.2 = SCL0, P0.3 = SDA0
    I2C0SCLH = 75;            // For 100kHz at PCLK=15MHz (adjust as needed)
    I2C0SCLL = 75;
    I2C0CONSET = 0x40;        // Enable I2C
}

void I2C_Start(void) {
    I2C0CONSET = 0x20;        // Set start bit
    while (!(I2C0CONSET & 0x08)); // Wait for SI flag
}

void I2C_Stop(void) {
    I2C0CONSET = 0x10;        // Set stop bit
    I2C0CONCLR = 0x08;        // Clear SI
}

void I2C_Write(unsigned char data) {
    I2C0DAT = data;
    I2C0CONCLR = 0x28;        // Clear SI and STA
    while (!(I2C0CONSET & 0x08));
}

unsigned char I2C_Read(unsigned char ack) {
    if (ack)
        I2C0CONSET = 0x04;    // ACK
    else
        I2C0CONCLR = 0x04;    // NACK
    I2C0CONCLR = 0x08;        // Clear SI
    while (!(I2C0CONSET & 0x08));
    return I2C0DAT;
}

void RTC_SetTime(unsigned char sec, unsigned char min, unsigned char hour) {
    I2C_Start();
    I2C_Write(RTC_ADDR_WRITE);
    I2C_Write(0x00);                 // Start from register 0 (seconds)
    I2C_Write(dec_to_bcd(sec));
    I2C_Write(dec_to_bcd(min));
    I2C_Write(dec_to_bcd(hour));
    I2C_Stop();
}

void RTC_GetTime(unsigned char *sec, unsigned char *min, unsigned char *hour) {
    I2C_Start();
    I2C_Write(RTC_ADDR_WRITE);
    I2C_Write(0x00);                 // Start from register 0
    I2C_Start();
    I2C_Write(RTC_ADDR_READ);
    *sec  = bcd_to_dec(I2C_Read(1)); // ACK after seconds
    *min  = bcd_to_dec(I2C_Read(1)); // ACK after minutes
    *hour = bcd_to_dec(I2C_Read(0)); // NACK after hours
    I2C_Stop();
}

