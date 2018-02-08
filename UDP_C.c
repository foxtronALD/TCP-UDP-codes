#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc,char *argv[]) //./client 127.0.0.1 hey
{
	int sockid;
	if((sockid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		printf("connect error\n");

	struct sockaddr_in x;
	x.sin_family=AF_INET;
	x.sin_port=htons(4500);
	x.sin_addr.s_addr=inet_addr(argv[1]);

	int msg_len;
	if((msg_len=sendto(sockid,argv[2],strlen(argv[2])+1,0,(struct sockaddr *)&x,sizeof(x)))<0)
		printf("Send error\n");
	else
		printf("%d bytes send to server\n",msg_len);

	close(sockid);
	return 0;
}