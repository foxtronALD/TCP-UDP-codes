#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() //./server 
{
	int sockid;
	if((sockid=socket(AF_INET,SOCK_STREAM,0))<0)
		printf("Socket error\n");
	
	struct sockaddr_in y,c;

	y.sin_family=AF_INET;
	y.sin_port=htons(3545);
	y.sin_addr.s_addr=INADDR_ANY;

	int sizeaddr=sizeof(y);
	if((bind(sockid,(struct sockaddr *)&y,sizeof(y)))<0)
			printf("Binding Error\n");

	if((listen(sockid,5))<0)
		printf("Listen error\n");
	int sockidc;
	for(;;)
	{
		
		int sizeaddr1=sizeof(c);
		int recvmsg_len,sendmsg_len;
		if((sockidc=accept(sockid,(struct sockaddr*)&c,&sizeaddr1))<0)
			printf("accept failed\n");

		char buf[100];

		if((recvmsg_len=recvfrom(sockidc,buf,100,0,(struct sockaddr*)&c,&sizeaddr1))<0)
			printf("Receive failed\n");

		char reverse[100];
		int i,j;
		for(i=recvmsg_len-1,j=0;i>=0;i--,j++)
		reverse[j]=buf[i];
		reverse[j]='\0';
		
		printf("Reversed Message is %s\n",reverse);
		if((sendmsg_len=sendto(sockidc,reverse,100,0,(struct sockaddr *)&c,sizeof(c)))<0)
			printf("Receive failed\n");
		printf("Reverse Messagee send to client\n");
	}
		close(sockid);
		close(sockidc);		
		return 0;
}


