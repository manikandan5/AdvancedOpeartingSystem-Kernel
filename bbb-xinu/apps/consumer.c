#include "prodcons.h"
#include <stddef.h>

void consumer(int count)
{
	int i;
	
	for(i=1; i<=count;i++)
	{
	        wait(produced);
		printf("Value of n- Consume side :\t%d\n",n);
		signal(consumed);
	}
}