#include <future.h>

syscall future_free(future *f)
{
	deallocateQueue(&(f->set_queue));
	deallocateQueue(&(f->get_queue));
	return freemem((char*)f, sizeof(f));
	//freemem(f , sizeof(future));
	//return OK;
}
