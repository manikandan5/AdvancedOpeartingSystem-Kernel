#include <future.h>
#include <string.h>
#include <stdio.h>
typedef unsigned int uint;

uint future_prod(future *fut) 
{
    int i, j;
    j = (int)fut;
    j = echo_client();
    future_set(fut, &j);
    return OK;
}

int echo_client()
{
	int	i;			
	int	retval;			
	char	msg[] = "Hello"; 	
	char	inbuf[1500];		
	int32	slot;			
	int32	msglen;			
	uint32	remoteip;		
	uint16	echoport= 1025;		
	uint16	locport	= 1026;	
	int32	retries	= 3;		
	int32	delay	= 5000;		
	char args[] = "192.168.1.100";
	char prog[] = "udpclient";

	udp_init();

	if (dot2ip(args, &remoteip) == SYSERR) 
	{
		fprintf(stderr, "%s: invalid IP address argument\r\n",
			prog);
		return 1;
	}

	slot = udp_register(remoteip, echoport, locport);
	if (slot == SYSERR) 
	{
		fprintf(stderr, "%s: could not reserve UDP port %d\n",
				prog, locport);
		return 1;
	}

	
	msglen = strnlen(msg, 1200);
	for (i=0; i<retries; i++) 
	{
		retval = udp_send(slot, msg, msglen);
		if (retval == SYSERR) 
		{
			fprintf(stderr, "%s: error sending UDP \n",prog);
			return 1;
		}

		retval = udp_recv(slot, inbuf, sizeof(inbuf), delay);
		if (retval == TIMEOUT) 
		{
			fprintf(stderr, "%s: timeout...\n", prog);
			continue;
		} 
		else if (retval == SYSERR) 
		{
			fprintf(stderr, "%s: error from udp_recv \n",prog);
			udp_release(slot);
			return 1;
		}
		break;
	}

	udp_release(slot);
	if (retval == TIMEOUT) 
	{
		fprintf(stderr, "%s: retry limit exceeded\n",prog);
		return 1;
	}

	if (retval != msglen) 
	{
		fprintf(stderr, "%s: sent %d bytes and received %d\n",prog, msglen, retval);
		return 1;
	}
	for (i = 0; i < msglen; i++) 
	{
		if (msg[i] != inbuf[i]) 
		{
			fprintf(stderr, "%s: reply differs at byte %d\n",prog, i);
			return 1;
		}
	}
	int msgnum = (int)msg;
	kprintf("\n %s \n",inbuf);
	return msgnum;
}
