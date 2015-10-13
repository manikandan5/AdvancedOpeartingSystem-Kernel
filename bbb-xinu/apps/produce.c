#include "prodcons.h"
#include <stddef.h>

void producer(int count)
{
	int i;
	
	for(i=1; i<=count; i++)
	{
		wait(consumed);
<<<<<<< HEAD
		n++;
		printf("Value of n- Produce side :\t%d\n",n);
=======
		printf("Value of n- Produce side :\t%d\n",n);
		n++;
>>>>>>> 9aea085949db6ce230f5560a515d2ed582a569e0
		signal(produced);
	}
}
