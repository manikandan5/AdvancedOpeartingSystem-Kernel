#include "prodcons.h"
#include "future.h"

int n;           
sid32 produced,consumed,fut_sem,f_qsem1,f_qsem2,f_qsem3;

shellcmd xsh_prodcons(int nargs, char *args[])
{
	int count=2000;
	int digit,k=1,j,v=0,len;
	produced=semcreate(1);
	consumed=semcreate(0);
	fut_sem=semcreate(0);
	f_qsem1=semcreate(1);
	f_qsem2=semcreate(1);
	f_qsem3=semcreate(1);
	if(nargs>2)
	{
		printf("Too many Arguements passed\n");
		return 1;
	}
	if(nargs==2 && strncmp(args[1], "-f", 3) == 0) 
	{
		future *f_exclusive, *f_shared, *f_queue;

		f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
		f_shared = future_alloc(FUTURE_SHARED);
		f_queue = future_alloc(FUTURE_QUEUE);

		resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
		resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );

		resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
		resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
		resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
		resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
		resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

		resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
		resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
		sleep(2);
		return 0;
	}
	if(nargs==2)
	{
		len=strlen(args[1]);
		for(j=len-1;j>=0;j--)
		{
			digit=args[1][j]-'0';
			if(digit<0 || digit>9)
			{
				printf("Invalid Arguement passed\n");
				return 1;
			}
			v=v+k*digit;
			k=k*10;
		}
		count=v;
		printf("Value of Count is %d \n",count);     
		resume(create(producer, 1024, 20, "producer", 1, count));
		resume(create(consumer, 1024, 20, "consumer", 1, count));
	}
	printf("\n");
	return 0;
}
