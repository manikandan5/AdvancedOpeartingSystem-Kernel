#include "queue_fut.h"

int queue_init(struct FutureQ* queue, int capacity)
{
    queue->p = (pid32 * ) getmem(capacity * sizeof(pid32));
    queue->cap = capacity;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;
    return 1;
}
