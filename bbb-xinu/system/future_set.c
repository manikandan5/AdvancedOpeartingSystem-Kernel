#include<future.h>

syscall future_set(future* f, int* value){
	intmask mask;
	pid32 process_id;
	int i;
	mask = disable();
	if(f->flag==FUTURE_EXCLUSIVE){
		if(f->state==FUTURE_WAITING || f->state==FUTURE_EMPTY){
			f->state=FUTURE_VALID;
			f->value=value;
			restore(mask);
			return OK;
		}
		else
		{
			restore(mask);
			return SYSERR;
		}

	}
	if(f->flag==FUTURE_SHARED){
		if (f->state==FUTURE_WAITING || f->state==FUTURE_EMPTY){
			f->state=FUTURE_VALID;
			f->value=value;		
			while(1)
			{
				i=d_queue(f->get_q);
				if(i==-1)
					break;
				process_id=get_q(f->get_q);
				resume(process_id);
			}
			
			restore(mask);
			return OK;
		}
		else
		{
			restore(mask);
			return SYSERR;
		}
	}
	if(f->flag==FUTURE_QUEUE)
	{
				if(f->state==FUTURE_EMPTY || f->state==FUTURE_VALID)
				{
					en_queue(f->set_q,currpid);
					restore(mask);
					suspend(currpid);

				}
				if(f->state==FUTURE_WAITING)
				{
					f->state=FUTURE_VALID;
					f->value=value;
					i=d_queue(f->get_q);
					if(i!=-1)
					{
						process_id=get_q(f->get_q);
						
					        restore(mask);
						resume(process_id);
						return OK;						
					}
					restore(mask);
					return OK;
				}
				else{
					restore(mask);
					return SYSERR;
				}
	}
	return OK;
}
