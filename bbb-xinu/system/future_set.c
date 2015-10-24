#include <future.h>

syscall future_set(future *f, int* value)
{
	f->value = *value;
	f->state = FUTURE_VALID;
	if(f->flag == FUTURE_EXCLUSIVE)
	{
		f->value = *value;
		f->state = FUTURE_VALID;
		resume(f->pid);
	}
	else if (f->flag == FUTURE_SHARED)
	{
		if(f->state == FUTURE_VALID)
		{
			return SYSERR;
		}
		f->value = *value;
		f->state = FUTURE_VALID;
		
		int i;
		for(i=0; i<f->get_queue.size; i++)
		{
			resume(f->get_queue.p[i]);
		}
	}
	else if(f->flag == FUTURE_QUEUE)
	{
		if(f->get_queue.size ==0)
		{
			enqueueFuture(&(f->set_queue), getpid());
			suspend(getpid());
		}
		
		while(f->state == FUTURE_VALID)
		{
			resched();
		}
		f->value = *value;
		f->state = FUTURE_VALID;
		resume(dequeueFuture(&f->get_queue));
	}
	return OK;
}
