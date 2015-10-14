/* xsh_reset.c - xsh_reset */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_date - obtain and print the current month, day, year, and time
 *------------------------------------------------------------------------
 */
shellcmd xsh_reset(int nargs, char *args[]) {

	int32	retval;			/* return value			*/
	uint32	now;			/* current local time		*/
	char	datestr[64];		/* printable date in ascii	*/

	volatile uint32 *prm_rstctrl = (volatile uint32 *)0X44E00F00;
	*prm_rstctrl = 0x01;
	return 0;
}
