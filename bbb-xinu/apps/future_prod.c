#include <future.h>

typedef unsigned int            uint;

uint future_prod(future *fut) 
{
	int i, j=0;
	for(i-0; i<100; i++)
	{
		j +=i;
	}
	future_set(fut, &j);
	return OK;
	/*j = (int)fut;
	for (i=0; i<1000; i++) 
	{
		j += i;
	}
	if(future_set(fut, j)==SYSERR)
	{
		printf("The already produced value is not consumed yet");
	}	
	return OK;*/
}
