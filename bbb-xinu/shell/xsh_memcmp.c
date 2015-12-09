/* xsh_memcmp.c - xsh_memcmp */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_memcmp - Assign Memory using Best Fit method
 *------------------------------------------------------------------------
 */
shellcmd xsh_memcmp(int nargs, char *args[]) {

	traverse();
	printf("After Assigning memory....\n");
	int* k = new_getmem(sizeof(int));
	traverse();
	int* d = new_getmem(10*sizeof(long));
	printf("After Assigning memory....\n");
	traverse();
	int* f = new_getmem(sizeof(int));
	printf("After Assigning memory....\n");
	traverse();
	freestk(d,10*sizeof(long));
	printf("After freeing up memory....\n");
	traverse();
	return 0;
}
