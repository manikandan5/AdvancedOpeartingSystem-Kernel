/* future_free.c - future_free */

#include "future.h"

/*------------------------------------------------------------------------
 *  future_free - Used to free the space assigned to a Future
 *------------------------------------------------------------------------
 */

syscall future_free(future* f)
{
        intmask mask;
        mask=disable();
	syscall sig=freemem((char *)f,sizeof(f));
        restore(mask);
	return sig;
}
