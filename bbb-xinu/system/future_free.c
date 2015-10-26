#include<future.h>

syscall future_free(future* f)
{
	int status;
	
	status=freemem((char*) f,sizeof(future));
	if (status< 1)
		return SYSERR;
	return OK;
}
