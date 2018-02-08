#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define MAXLINE 1024

int main(int argc , char* argv[])
{
    int clientSock, new_socket,len;
    struct sockaddr_in clientaddress,servAddr;
    int opt = 1;
    int addrlen = sizeof(clientaddress);
    char recv_msg[1024] ;
    char str[1024];
    int n;
    
	if((clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("socket() failed");
    
	char *ip = argv[1];
        char *port = argv[2];
        int p = atoi(port);
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip);
	servAddr.sin_port = htons(p);

	if (connect(clientSock, (struct sockaddr *) &servAddr,sizeof(servAddr)) < 0)
		printf("connect() failed");
	else
	{
	       while(1)
		{
			 printf("Enter your expression to send to server and 'q' to quit\n");
			 scanf("%s",str);	
			 len = strlen(str);
	                 if (send(clientSock,str,len, 0) != len)
				printf("send() sent a different number of bytes than expected");
			 if(str[0] == 'q')
			  {
				close(clientSock);
				break;
			  }
	               	 printf("Expression sent to server is %s", str);
			 n=recvfrom(clientSock,recv_msg,MAXLINE,0,NULL,NULL);
			 recv_msg[n]='\0';
		         printf("\n Server's ans for expression : %s\n\n",recv_msg);
		}
	}	
}