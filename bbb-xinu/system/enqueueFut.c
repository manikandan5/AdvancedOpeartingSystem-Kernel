#include "queue_fut.h"

int enqueueFut(struct FutureQ* queue, pid32 pid)
{
    if(queue->size == queue->cap - 1)
    {
        printf("Queue is already full!!");
        return -1;
    }
    else
    {
        queue->p[queue->tail] = pid;
        queue->tail = ((queue->tail) + 1)%(queue->cap);
        (queue->size)++;
	//printf("\nEnqueued : %d",queue->p[(queue->tail)-1]);
	//printf("\nQueue Size : %d",queue->size);
    }
    return 1;
}
