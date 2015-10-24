#include <future.h>

syscall future_get(future *f, int* value)
{
	if(f->flag == FUTURE_EXCLUSIVE)
	{
		f->pid = getpid();
		if(f->state == FUTURE_EMPTY)
		{
			suspend(f->pid);
		}
		*value = f->value ;
		f->state = FUTURE_EMPTY;
	}
	else if(f->flag == FUTURE_SHARED)
	{
		if(f->state == FUTURE_EMPTY)
		{
		
			enqueueFuture(&(f->get_queue),getpid());
			suspend(getpid());
		}
		*value = f->value;
	}
	else if (f->flag == FUTURE_QUEUE)
	{
        	if(f->set_queue.size == 0)
		{
		    enqueueFuture(&(f->get_queue), getpid());
		    suspend(getpid());
		}
		else
		{
		    enqueueFuture(&(f->get_queue), getpid());
		    resume(dequeueFuture(&(f->set_queue)));
		    
		    while(f->state != FUTURE_VALID)
		    {
		        resched();
		    } 
		} 
        	*value = f->value;
        	f->state = FUTURE_EMPTY; 
    	}
	else
	{
		kprintf("Future State not recognized");
		return SYSERR;
	}
	return OK;
	/*if(f->state == FUTURE_VALID)
	{
		*value = f->value;
		f->state = FUTURE_EMPTY;
		return OK;	
	}
	else if(f->state == FUTURE_EMPTY)
	{
		f->state = FUTURE_WAITING;
		return OK;
	}
	return SYSERR;*/
}
