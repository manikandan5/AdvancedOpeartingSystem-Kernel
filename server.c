#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define BUFLEN 512  
#define PORT 1025   

void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in socket_msg, socket_other;
     
    int s, i, slen = sizeof(socket_other) , recv_len;
    char buf[BUFLEN];
     
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    memset((char *) &socket_msg, 0, sizeof(socket_msg));
     
    socket_msg.sin_family = AF_INET;
    socket_msg.sin_port = htons(PORT);
    socket_msg.sin_addr.s_addr = htonl(INADDR_ANY);
     
    if( bind(s , (struct sockaddr*)&socket_msg, sizeof(socket_msg) ) == -1)
    {
        die("bind");
    }
    
    while(1)
    {
        fflush(stdout);
         
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &socket_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        printf("XINU: %s\n" , buf);
        printf("VM:");
	scanf("%s",buf);
        
	if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &socket_other, slen) == -1)
        {
            die("sendto()");
        }
	break;
    }
 
    close(s);
    return 0;
}
