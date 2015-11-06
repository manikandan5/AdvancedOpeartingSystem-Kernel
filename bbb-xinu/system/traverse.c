/* traverse.c - traverse */

#include "xinu.h"

/*------------------------------------------------------------------------
 *  traverse - Used to traverse the free memory list and print the details
 *------------------------------------------------------------------------
 */

syscall traverse()
{
        intmask mask;
        mask=disable();
	struct memblk *head;
	head=&memlist;
	if(head->mnext==NULL)
	{
	printf("Memory is full...No free memory to print\n");
	return OK;
	}
	while(head->mnext!=NULL)
	{
	uint32 length=(uint32)head->mlength;
	printf("Memory Block : %d",head);
	printf("\tLength of Block : %d \n",length);
	head=head->mnext;
	}
        restore(mask);
	return OK;
}
