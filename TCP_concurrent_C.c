#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <fcntl.h>

int main()
{
 	int new_socket,sfd,val;
	char buffer[100];
 	//memset(&buffer,'0',sizeof(buffer));
 
 	if((sfd=socket(AF_INET,SOCK_STREAM,0))==0)
 	{
	   printf("socket connection failed\n");
	   exit(0);
	}
	
	struct sockaddr_in serveraddr;
	//memset(&serveraddr,'0',sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(5554);
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	
	if(connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
	{
		printf("error in connection\n");
		exit(0);
	}
	
	printf("enter message for server\n");
	scanf(" %[^\n]s",buffer);
	send(sfd,buffer,strlen(buffer),0);
	printf("%s message sent to server\n",buffer);
	//memset(&buffer,0,sizeof(buffer));
	val=read(sfd,buffer,100);
	printf("message from server : %s\n",buffer);
	return 0;
}