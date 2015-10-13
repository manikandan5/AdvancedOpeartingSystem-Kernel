#include <ctype.h>
#include "prodcons.h"

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
    	}        
	
	//local varible to hold count

	//check args[1] if present assign value to count

	//create the process producer and consumer and put them in ready queue.
	//Look at the definations of function create and resume in exinu/system folder for reference.      
	
	resume( create(producer, 1024, 20, "producer", 1, count) );
	resume( create(consumer, 1024, 20, "consumer", 1, count) );
	
	return 1;
}
