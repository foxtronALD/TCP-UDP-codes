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

int main()
{
	int sockid;
	if((sockid=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		printf("Socket Error\n");

	struct sockaddr_in y;
	y.sin_family=PF_INET;
	y.sin_port=htons(5555);
	y.sin_addr.s_addr=INADDR_ANY;

	if(bind(sockid,(struct sockaddr *)&y,sizeof(y))<0)
		printf("Error in Binding\n");
	else
	{
		char buf[25];
		int send_msglen,recv_msglen;
		int addrsize=sizeof(y);
		if((recv_msglen=recvfrom(sockid,buf,25,0,(struct sockaddr *)&y,&addrsize))<0)
			printf("Receive Error\n");
		else
			printf("Message from Client is:%s\n",buf);
		
		time_t rawtime=time(NULL);
		struct tm* timeinfo=localtime(&rawtime);
		// printf("%d %d %d %d %d %d\n",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
		if((send_msglen=sendto(sockid,asctime(timeinfo),strlen(asctime(timeinfo))+1,0,(struct sockaddr*)&y,sizeof(y)))<0)
			printf("Time Date can't be send\n");
		else
			printf("%d bytes send to client\n",send_msglen);
	}
	close(sockid);
	return 0;
}