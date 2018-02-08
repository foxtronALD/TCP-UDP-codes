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

char buffer[100];
void swap(char *a,char *b)
{
  char t=*a;
  *a=*b;
  *b=t;
}

int main()
{
	int i,new_socket,sfd,val;
	
	if((sfd=socket(AF_INET,SOCK_STREAM,0))==0)
	{
	   printf("socket connection failed\n");
	   exit(0);
  	}
 
 	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serveraddr.sin_port=htons(5554);
	
	if(bind(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
 	{
		printf("error in binding\n");
		exit(0);
	}
	
	if(listen(sfd,10)<0)
 	{
		printf("listening failed\n");
		exit(0);
 	}
 
 	int pid;
 	int addrlen=sizeof(serveraddr);
 	int c=0;
 	while(1)
	{
		if((new_socket=accept(sfd,(struct sockaddr*)&serveraddr,(socklen_t*)&addrlen))<0)
	 	{
		  printf("error in accept\n");
		  exit(0);
		}
		
		if((pid=fork())<0)
		  printf("error in forking\n");
		
		else if(pid>0) 
		{
		   close(new_socket);
		   continue;
		}
		
		else
		{
			 printf("connection established with client\n");
			 val=read(new_socket,buffer,100);
			 printf("message from client : %s\n",buffer);
			 int l=strlen(buffer);
			 for(i=0;i<strlen(buffer)/2;i++)
			 {
				  swap(&buffer[i],&buffer[l-i-1]);
			 }
			 send(new_socket,buffer,strlen(buffer),0);
			 printf("%s message sent to client\n",buffer);
			 close(new_socket);
	 	}
	}
 return 0;
}