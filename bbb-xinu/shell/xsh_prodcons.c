#include <xinu.h>
#include "prodcons.h"

int n;                 //Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/

shellcmd xsh_prodcons(int nargs, char *args[])
{	
	int count = 2000; 
      	int i;	
	//Argument verifications and validations
	if (nargs > 2) {
		printf("Too many arguments\n");
		return 1;
	}
	else if (nargs ==2)
	{
		printf("Hello World\n");
		count=0;
		int dgt=1;
		for(i=strlen(args[1])-1;i>=0;i--)
		{
			count=count + (args[1][i]-'0')*dgt;
			dgt=dgt*10;
		}
		 
	}          
	
	 //local varible to hold count

		//check args[1] if present assign value to count

		//create the process producer and consumer and put them in ready queue.
		//Look at the definations of function create and resume in exinu/system folder for reference.      
		resume( create(producer, 1024, 20, "producer", 1, count) );
		resume( create(consumer, 1024, 20, "consumer", 1, count) );
	
	return 1;
}
