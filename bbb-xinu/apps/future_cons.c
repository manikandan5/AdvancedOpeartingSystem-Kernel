#include <future.h>

typedef unsigned int            uint;

uint future_cons(future *fut) 
{

	int i, status;
	status = future_get(fut, &i);
	if(status<1)
	{
		//printf("future_get failed\n");
		return -1;
	}
	printf("it consumed %d\n",i);
	return OK;
}
/*	while(TRUE)
	{
		status = future_get(fut, &i);
		
		if (status == OK && fut->state==FUTURE_EMPTY)
		{
			printf("Value consumed %x\n", i);
			break;
		}
		else if(status ==  OK)
		{
			continue;
		}
		if (status == SYSERR) 
		{
			continue;
		}
	}	
	
	return OK;
}*/
