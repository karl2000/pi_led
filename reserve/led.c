#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(void)
{
	FILE *p=NULL;
	int i=0;
	p = fopen("/sys/class/gpio/export","w");
	fprintf(p,"%d",2);
	fclose(p);
	p = fopen("/sys/class/gpio/gpio2/direction","w");
	fprintf(p,"out");
	fclose(p);
	for(i=0;i<100;i++)
	{
		p = fopen("/sys/class/gpio/gpio2/value","w");
		fprintf(p,"%d",1);
		sleep(1);
		fclose(p);
		p = fopen("/sys/class/gpio/gpio2/value","w");
		fprintf(p,"%d",0);
		sleep(1);
		fclose(p);
	}
	p = fopen("/sys/class/gpio/unexport","w");
	fprintf(p,"%d",2);
	fclose(p);
	return 0;
}