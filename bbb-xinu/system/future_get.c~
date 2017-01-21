#include<future.h>

syscall future_get(future *f, int *value){
	intmask mask; 
	pid32 p;
	int i;
	mask = disable();
	if(f->flag==FUTURE_SHARED){
		if(f->state==FUTURE_EMPTY||f->state==FUTURE_WAITING){
			f->state=FUTURE_WAITING;			
			en_queue(f->get_q,currpid);
			suspend(currpid);
			
		}
		if(f->state==FUTURE_VALID){
			*value=*(f->value);
			if(isempty_q(f->get_q))
				f->state=FUTURE_EMPTY;
			restore(mask);
			return OK;
			
		}
		if (isempty_q(f->get_q))
	        {
			f->state = FUTURE_EMPTY; 
		} 
		else 
		{
			f->state = FUTURE_WAITING;
		}
		
		

	}
	if(f->flag==FUTURE_QUEUE){
		if(f->state==FUTURE_EMPTY){
			f->state=FUTURE_WAITING;
			en_queue(f->get_q,currpid);
			i=d_queue(f->set_q);
			if(i!=-1){
				p=get_q(f->set_q);
				restore(mask);
				ready(p);
				suspend(currpid);
			} else {
			  suspend(currpid);
			}
		}
		if(f->state==FUTURE_WAITING){
			en_queue(f->get_q,currpid);
			i=d_queue(f->set_q);
			if(i!=-1){
				p=get_q(f->set_q);
				restore(mask);
				suspend(currpid);
			} else {
				suspend(currpid);
			}

		}
		if(f->state==FUTURE_VALID){		
			*value=*(f->value);
			
			i=d_queue(f->set_q);
			if(i!=-1){
			   if(isempty_q(f->get_q)) {
			      f->state = FUTURE_EMPTY;
			   } else {
				f->state=FUTURE_WAITING;
				p=get_q(f->set_q);
				ready(p);
			   }
			}
			else{
				if (isempty_q(f->get_q)) {
				   f->state = FUTURE_EMPTY; 
				} else {
				   f->state = FUTURE_WAITING;
				}
			}
			restore(mask);
			return OK;
		}
	}
	if(f->flag==FUTURE_EXCLUSIVE){
		if(f->state==FUTURE_VALID){
			f->state=FUTURE_EMPTY;
			*value=*(f->value);
			restore(mask);
			return OK;
			
		}
		else
		{
			restore(mask);
			return SYSERR;
		}
	}
	return SYSERR;
}
