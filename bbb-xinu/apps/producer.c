#include "prodcons.h"
#include <stddef.h>

void producer(int count)
{
	int i;
	
	for(i=1; i<=count; i++)
	{
		wait(consumed);
		n++;
		printf("Value of n- Produce side :\t%d\n",n);
		//printf("Value of n- Produce side :\t%d\n",n);
		//n++;
		signal(produced);
	}
}
