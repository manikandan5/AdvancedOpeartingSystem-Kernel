/* xsh_traversal.c - xsh_traversal */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_traversal - Displays all free memory blocks and their size from memlist
 *------------------------------------------------------------------------
 */
shellcmd xsh_traversal(int nargs, char *args[]) {

	traverse();
	printf("After Assigning memory to 1 variable....\n");
	int* j = new_getmem(400*sizeof(int));
	traverse();
	int* k = new_getmem(200*sizeof(int));
	printf("After Assigning memory to 1 variable....\n");
	traverse();
	int* d = new_getmem(300*sizeof(int));
	freemem(k,2000*sizeof(int));
	printf("After deallocating memory for the last variable....\n");
	traverse();
	return 0;
}
