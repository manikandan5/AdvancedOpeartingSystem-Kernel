/* new_getstk.c - new_getstk */

#include <xinu.h>

char *new_getstk(uint32 nbytes)
{
	intmask	mask;			
	struct	memblk	*p, *current;	
	struct	memblk	*bestFit, *bestFitp; 
	mask = disable();

	if (nbytes == 0) 
	{
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	

	p = &memlist;
	current = memlist.mnext;
	bestFit = p;
	bestFitp = NULL;  

	while (current != NULL) 
	{			
		if ((current->mlength >= nbytes)&&(current->mlength>bestFit->mlength)) 
		{	
			bestFit = current;		
			bestFitp = p;
		}
		p = current;
		current = current->mnext;
	}

	if (bestFit == NULL) 
	{	
		restore(mask);
		return (char *)SYSERR;
	}
	if (nbytes == bestFit->mlength)
	{		
		bestFitp->mnext = bestFit->mnext;
	} 
	else 
	{				
		bestFit->mlength -= nbytes;
		bestFit = (struct memblk *)((uint32)bestFit + bestFit->mlength);
	}
	memlist.mlength -= nbytes;
	restore(mask);
	char* rtn=(char *)((uint32) bestFit + nbytes - sizeof(uint32));
	int size=nbytes;
	while(size>0)
	{
		*rtn='#';
		*--rtn;
		--size;
	}
	return (char *)((uint32) bestFit + nbytes - sizeof(uint32));
}
