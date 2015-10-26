#include<future.h>

future* future_alloc(int future_flag){

	future *p=(future *)getmem(sizeof(future));
	if (p!=NULL){
		p->flag=future_flag;
		p->state=FUTURE_EMPTY;
		p->set_q=init_q();
		p->get_q=init_q();
	}
	return p;
}
