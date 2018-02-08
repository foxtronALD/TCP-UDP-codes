#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc,char *argv[]) //./client 127.0.0.1 5555
{
	int sockid;
	if((sockid=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		printf("Socket Error\n");

	struct sockaddr_in x;

	//int port=atoi(argv[2]);
	x.sin_family=AF_INET;
	x.sin_port=htons(3545);
	x.sin_addr.s_addr=inet_addr(argv[1]);

	int sizeaddr=sizeof(x);
	if((connect(sockid,(struct sockaddr *)&x,sizeof(x)))<0)
			printf("Connect Error\n");

	printf("Enter the messageto send to server\n");
	char str[255];
	fgets(str,254,stdin);
	int send_msglen,recv_msglen;
	if((send_msglen=sendto(sockid,str,strlen(str)+1,0,(struct sockaddr *)&x,sizeof(x)))<0)
		printf("Send Error\n");
	else
		printf("%d bytes send to server\n",send_msglen);

	if((recv_msglen=recvfrom(sockid,str,100,0,(struct sockaddr  *)&x,&sizeaddr))<0)
		printf("Recieve Error\n");
	else
		printf("Message from server is : %s\n",str);

	close(sockid);
	return 0;
}
