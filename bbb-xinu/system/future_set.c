/* future_set.c - future_set */

#include "future.h"

/*------------------------------------------------------------------------
 *  future_set - Used to set a value to the future
 *------------------------------------------------------------------------
 */

syscall future_set(future *f, int *a)
{
        intmask mask;
        mask=disable();
	if(f->state==FUTURE_VALID&&f->flag!=FUTURE_QUEUE)
	{
		return SYSERR;
	}
	else
	{
	if(f->flag==FUTURE_EXCLUSIVE)
	{
		f->value=*a;
               	if(f->state==FUTURE_WAITING)
		{
			signal(fut_sem);
		}
		f->state=FUTURE_VALID;
		return OK;
	}
	else if(f->flag==FUTURE_SHARED)
	{
		int i;
		f->value=*a;
		f->state=FUTURE_VALID;
		if(f->get_queue.size!=0)
		{
		for(i=0; i<f->get_queue.size; i++)
		{
			resume(f->get_queue.p[i]);
		}
		}
	}
	else if(f->flag==FUTURE_QUEUE)
	{
		if(f->get_queue.size==0)
		{
			wait(f_qsem1);
			enqueueFut(&(f->set_queue), getpid());
			signal(f_qsem1);
			suspend(getpid());
			f->value=*a;
			f->state=FUTURE_VALID;
		}
		else
		{
			f->value=*a;
                        f->state=FUTURE_VALID;
			wait(f_qsem1);
			resume(dequeueFut(&(f->get_queue)));
			signal(f_qsem1);
		}
	}
	}
        restore(mask);
	return OK;
}
