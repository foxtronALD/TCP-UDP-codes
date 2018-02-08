#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

int main(int argc,char *argv[]) //./client 127.0.0.1 5555
{
	//if port has to be taken as argument
	int sockid;
	if((sockid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		printf("Socket error\n");

	int portno=atoi(argv[2]);
	struct sockaddr_in x;

	x.sin_family=PF_INET;
	x.sin_port=htons(portno);
	x.sin_addr.s_addr=inet_addr(argv[1]);

	int send_msglen,recv_msglen;
	char buf[25]="Please send the Date";
	int addrsize=sizeof(x);
	if((send_msglen=sendto(sockid,buf,strlen(buf)+1,0,(struct sockaddr *)&x,sizeof(x)))<0)
		printf("Send error\n");
	else
		printf("%d bytes send to server\n",send_msglen);

	if((recv_msglen=recvfrom(sockid,buf,25,0,(struct sockaddr *)&x,&addrsize))<0)		
		printf("Receive failed\n");
	else
		printf("Message received from server : %s",buf);

	close(sockid);
	return 0;
}
