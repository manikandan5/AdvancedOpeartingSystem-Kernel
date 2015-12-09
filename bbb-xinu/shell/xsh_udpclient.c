#include <future.h>
#include <stdio.h>
#include <string.h>


future *f_exclusive;

shellcmd xsh_udpclient(int nargs, char *args[])
{
	
	f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
	
	resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
  	resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
}
