#include<lpc21xx.h>
typedef struct can2
{
	unsigned int id;
	unsigned int rtr;
	unsigned int dlc;
	unsigned int byteA;
	unsigned int byteB;
}CAN2_MSG;
	
void delay_ms(int);
void can2_init(void);
void can2_tx(CAN2_MSG m1);
int main()
{
	CAN2_MSG m1;
	can2_init();
	//sending data frame
	m1.id = 0x1AF;
	m1.rtr = 0; //data frame
	m1.dlc = 4;
	m1.byteA = 0xDDCCBBAA;
	m1.byteB = 0;
	while(1){
		can2_tx(m1); //data frame
		delay_ms(1000);
	}
}

void can2_init(void){
	PINSEL1 |=0X14000;
	VPBDIV = 1;
	C2MOD = 0x1; //can2 in reset mode
	AFMR = 0x02; //accept all receiving message (data/remote)
	C2BTR = 0x001C001D; //pclk = 60MHZ
	C2MOD = 0x0; //can2 in normal mode
}

void can2_tx(CAN2_MSG m1){
	C2TID1 = m1.id;
	C2TFI1 = (m1.dlc<<16);
	if(m1.rtr==0) //data frame
	{
		C2TFI1 &= ~(1<<30); // RTR = 0
		C2TDA1 = m1.byteA; //lower bytes of data
		C2TDB1 = m1.byteB; //upper 4bytes of data
	}
	else{
		C2TFI1 = (1<<30); //RTR = 1
	}
	C2CMR = (1<<0)|(1<<5);
	while((C2GSR&(1<<3))==0);
}

void delay_ms(int n){
	T0PR = 15000-1;
	T0TC = T0PC=0;
	T0TCR = 0X1;
	while(T0TC<n);
	T0TCR = 0x0;
	
}

	
	
	

	