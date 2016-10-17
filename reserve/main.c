

#define GPFSEL0 (*(volatile unsigned long*)0xF2200000)
#define GPSET0  (*(volatile unsigned long*)0xF220001C)


void delay()
{
	unsigned i,j;
	for(i=0;i<100;i++)
		for(j=0;j<100;j++);
}


int main(void)
{
	GPFSEL0 = 0x00000040;
	while(1)
	{
		GPSET0  = 0x00000004;
		delay();
		GPSET0  = 0x00000000;
		delay();
		
		
	}
	return 0;
	
}