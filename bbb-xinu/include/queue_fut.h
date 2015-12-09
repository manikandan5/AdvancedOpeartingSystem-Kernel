#include <xinu.h>

struct FutureQ
{
    int size;
    pid32 *p;
    int cap;
    int head;
    int tail;
};

/* Interface for Future Queue functions */
int queue_init(struct FutureQ* queue, int capacity);
int enqueueFut(struct FutureQ* queue, pid32 pid);
pid32 dequeueFut(struct FutureQ* queue);
