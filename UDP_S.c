#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() //./a.out
{
	int sockid;
	if((sockid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		printf("Socket error\n");

	struct sockaddr_in y;
	y.sin_family=PF_INET;
	y.sin_port=htons(4500);
	y.sin_addr.s_addr=INADDR_ANY;

	
	if((bind(sockid,(struct sockaddr *)&y,sizeof(y)))<0)
		printf("Bind Error\n");
	else
	{
		char buffer[100];
		int msg_len;
		int addrsize=sizeof(y);
		if(msg_len=recvfrom(sockid,buffer,100,0,(struct sockaddr *)&y,&addrsize)<0)
			printf("Receive Error\n");
		else
			printf("Message received from client is %s\n",buffer);
	}
	
	close(sockid);
	return 0;

}