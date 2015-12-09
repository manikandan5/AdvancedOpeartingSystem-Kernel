#include "queue_fut.h"

#ifndef _FUTURE_H_
#define _FUTURE_H_
 
/* define states */
#define FUTURE_EMPTY	  0
#define FUTURE_WAITING 	  1
#define FUTURE_VALID 	  2

/* modes of operation for future*/

#define FUTURE_EXCLUSIVE  1
#define FUTURE_SHARED     2
#define FUTURE_QUEUE      3

typedef struct futent
{
   int *value;
   int flag;
   int state;
   pid32 pid;
   struct FutureQ set_queue;
   struct FutureQ get_queue;
} future;

/* Interface for system call */
future* future_alloc(int future_flags);
syscall future_free(future*);
syscall future_get(future*, int*);
syscall future_set(future*, int*);

/* Function Prototypes */
uint32 future_prod(future*);
uint32 future_cons(future*);

/* Declaring Semaphore */
extern sid32 fut_sem,f_qsem1,f_qsem2,f_qsem3; 
#endif /* _FUTURE_H_ */
