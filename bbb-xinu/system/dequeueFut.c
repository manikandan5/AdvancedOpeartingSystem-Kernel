#include "queue_fut.h"

pid32 dequeueFut(struct FutureQ* queue)
{
    if(queue->size == 0)
    {
        return -1;
    }
    pid32 val = queue->p[queue->head];
    //printf("\nDequeued : %d",val);
    queue->head = (queue->head + 1) % (queue->cap);
    (queue->size)--;
    //printf("\nQueue : %d",queue->size);
    return val;
}
