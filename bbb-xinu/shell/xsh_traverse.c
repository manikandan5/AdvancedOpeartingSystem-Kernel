/* xsh_traversal.c - xsh_traversal */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*---------------------------------------------------------------------------
 * xsh_traverse - Displays all free memory blocks and their size from memlist
 *---------------------------------------------------------------------------
 */
shellcmd xsh_traverse(int nargs, char *args[]) {

	traverse();
	printf("Assigned memory to 1 variable\n");
	int* i = getmem(1000*sizeof(int));
	traverse();
	int* j = getmem(2000*sizeof(int));
	printf("Assigned memory to 1 variable\n");
	traverse();
	freemem(j,sizeof(j));
	printf("Assigned memory for the last variable\n");
	traverse();
	return 0;
}
