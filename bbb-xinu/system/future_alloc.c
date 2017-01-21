/* future_alloc.c - future_alloc */

#include "future.h"

/*------------------------------------------------------------------------
 *  future_alloc - Used to initialize a future object
 *------------------------------------------------------------------------
 */

future* future_alloc(int future_flag)
{
        intmask mask;
        mask=disable();
	if(future_flag==FUTURE_EXCLUSIVE)
	{
		future *f=(future* )getmem(sizeof(future));
		f->state=FUTURE_EMPTY;
		f->flag=future_flag;
		return f;
	}
	else if(future_flag==FUTURE_SHARED)
	{
		future *f=(future* )getmem(sizeof(future));
		f->state=FUTURE_EMPTY;
		f->flag=future_flag;
                int j=queue_init(&(f->get_queue),20);
		if(j==-1)
		{
		printf("Queue creation failed\n");
		return NULL;
		}
		return f;
	}
	else if(future_flag==FUTURE_QUEUE)
	{
		future *f=(future* )getmem(sizeof(future));
                f->state=FUTURE_EMPTY;
                f->flag=future_flag;
		int k=queue_init(&(f->get_queue),20);
                int z=queue_init(&(f->set_queue),20);
		if(k==-1||z==-1)
		{
		printf("Queue creation failed\n");
                return NULL;
		}
                return f;
	}
	else
	{
		printf("Future Allocation failed\n");
		return NULL;
	}
        restore(mask);
}
