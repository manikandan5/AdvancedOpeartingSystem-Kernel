/* future_get.c - future_get */

#include "future.h"

/*------------------------------------------------------------------------
 *  future_get - Used to retrieve a future value to a operation
 *------------------------------------------------------------------------
 */

syscall future_get(future *f, int* value)
{
        intmask mask;
        mask=disable();
	if(f->flag==FUTURE_EXCLUSIVE)
	{
	 if(f->state==FUTURE_WAITING)
	 {
		return SYSERR;
	 }
	 else if(f->state==FUTURE_VALID)
	 {
	 	*value=f->value;
                f->state=FUTURE_EMPTY;
                return OK;
	 }
	 else if(f->state==FUTURE_EMPTY)
	 {
		f->state=FUTURE_WAITING;
		wait(fut_sem);
		*value=f->value;
		printf("\nConsumed:%d",*value);
		return OK;
	 }
	}
	else if(f->flag==FUTURE_SHARED)
	{
		if(f->state==FUTURE_EMPTY)
		{
		enqueueFut(&(f->get_queue), getpid());
		suspend(getpid());
		}
		*value=f->value;
	 	printf("\nConsumed value: %d", *value);
        }
	else if(f->flag==FUTURE_QUEUE)
	{
	 if(f->set_queue.size==0)
         {
		wait(f_qsem2);
         	enqueueFut(&(f->get_queue), getpid());
		signal(f_qsem2);
         	suspend(getpid());
         }
	 else
	 {
		wait(f_qsem2);
		resume(dequeueFut(&(f->set_queue)));
		signal(f_qsem2);
	 }
	 *value=f->value;
	 sleep(1);
	 printf("\nConsuming value: %d", value);
	}
        restore(mask);
	return OK;
}
