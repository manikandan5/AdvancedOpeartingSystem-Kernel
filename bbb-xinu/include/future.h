#include <prodcons.h>

typedef unsigned int            uint;

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


struct QueueFuture
{
    int size; //Current size of the Queue.
    pid32 *p; //pointer to the pid queue..
    int capacity; //maximum size of the Queue..
    int left; //left index of the queue.
    int right; // right index of the queue..
};


int initializeQueue(struct QueueFuture*, int);
void deallocateQueue(struct QueueFuture*);

//returns 1 on success, and -1 on failure..
int enqueueFuture(struct QueueFuture*, pid32);
pid32 dequeueFuture(struct QueueFuture*);

typedef struct futent
{
   int value;		
   int flag;		
   int state;         	
   pid32 pid;
   struct QueueFuture set_queue;
   struct QueueFuture get_queue;
} future;

/* Interface for system call */
future* future_alloc(int future_flags);
syscall future_free(future*);
syscall future_get(future*, int*);
syscall future_set(future*, int*);

uint future_prod(future*);
uint future_cons(future*);
 

#endif /* _FUTURE_H_ */
