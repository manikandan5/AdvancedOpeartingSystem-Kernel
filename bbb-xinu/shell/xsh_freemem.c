/* xsh_memcmp.c - xsh_memcmp */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*-------------------------------------------------------
 * xsh_freemem - Memory Allocation using Best Fit method
 *-------------------------------------------------------
 */
shellcmd xsh_freemem(int nargs, char *args[]) {

	traverse();
	printf("Assigned 100 bytes\n");
	int* i = new_getstk(100);
	traverse();
	int* j = new_getstk(200);
	printf("Assigned 200 bytes\n");
	traverse();
	int* k = new_getstk(500);
	printf("Assigned 500 bytes\n");
	traverse();
	freemem(k,sizeof(k));
	printf("Freed  500 bytes\n");
	traverse();
	return 0;
}
