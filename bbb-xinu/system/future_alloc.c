#include <future.h>

future* future_alloc(int future_flag)
{
	future* obj = (future* )getmem(sizeof(future));
	if((char*)obj == (char *)SYSERR)
	{
		kprintf("Future cannot be created");
		return NULL;
	}
	obj->flag = future_flag;
	
	int status1 = initializeQueue(&(obj->set_queue), 100);
	int status2 = initializeQueue(&(obj->get_queue), 100);
	
	if(status1 == -1 || status2 == -1)
	{
		freemem((char*)obj, sizeof(obj));
		kprintf("Queue cannot be created");
		return NULL;
	}
	obj->state = FUTURE_EMPTY;
	return obj;
	/*future *f;
	f= (future *)getmem(sizeof(future));
	f->flag = future_flag;
	f->state = FUTURE_EMPTY;
	return f;*/
}
