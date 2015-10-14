#include <ctype.h>

#include <future.h>

int n;                 //Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/
sid32 produced, consumed;

shellcmd xsh_prodcons(int nargs, char *args[])
{	
	int count = 2000; 
      	/*int i,len,j,k=1;*/
	int digit,k=1,j,v=0,len;	
	int exit=0;

	produced = semcreate(0);
	consumed = semcreate(1);
	//Argument verifications and validations

	if (nargs > 2) 
	{
		printf("Too many arguments\n");
		return 1;
	}
	if(nargs==2)
     	{
		if(strcmp(args[1],"-f")==0)
		{
			printf("Yes");

			future *f1, *f2, *f3;

			f1 = future_alloc(FUTURE_EXCLUSIVE);
			f2 = future_alloc(FUTURE_EXCLUSIVE);
			f3 = future_alloc(FUTURE_EXCLUSIVE);

			resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
			resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
			resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
			resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
			resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
			resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
			
			future_free(f1);
			future_free(f2);
			future_free(f3);

			return 1;
		}
      		len=strlen(args[1]);
      		for(j=len-1;j>=0;j--)
       		{
        		digit=args[1][j]-'0';
        		if(digit<0 || digit>9)
        		{
        			printf("Invalid Arguments");
				return 1;
        		}
        		v=v+k*digit;
        		k=k*10;
       		}
      		count=v;
      		printf("Value of Count is %d \n",count);
    	}        
	
	//local varible to hold count

	//check args[1] if present assign value to count

	//create the process producer and consumer and put them in ready queue.
	//Look at the definations of function create and resume in exinu/system folder for reference.      
	
	resume( create(producer, 1024, 20, "producer", 1, count));
  	resume( create(consumer, 1024, 20, "consumer", 1, count));

	return 1;
}
