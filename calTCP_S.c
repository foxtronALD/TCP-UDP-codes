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
#define qlen 10

int solve(char* expr)
{
	int i=1,ans = expr[0] - '0';
	while(expr[i]!='\0')
	{
		switch(expr[i])
		{
			case '+':
				ans = ans + (expr[i+1]-'0');
				break;
			case '-':
				ans = ans - (expr[i+1]-'0');
				break;
			case '*':
				ans = ans * (expr[i+1]-'0');
				break;
			case '/':
				ans = ans / (expr[i+1]-'0');
				break;
		}
		i = i+2;
	}
	return ans;
}

int main(int argc, char* argv[])
{
	int status, servSock, clientSock,clntlen,msglen;
	struct sockaddr_in servAddr,clientaddr;
    	int opt = 1;
    	int addrlen = sizeof(servAddr);
	char msg[1024];
	int n;

    	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	printf("socket() failed");
        
	int port  =  atoi(argv[1]);
  	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);
	
	if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		printf("bind() failed");
	
	time_t timer;
	char tim[50];
	struct tm* tm_info;
        time(&timer);
	tm_info = localtime(&timer);

	if (listen(servSock, qlen) < 0)
		printf("listen() failed");

	clntlen = sizeof(clientaddr);
	if ((clientSock=accept(servSock,(struct sockaddr *)&clientaddr,&clntlen))<0)
			printf("accept() failed");

        strftime(tim, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        printf("client connected at :%s\n",tim);

	for(;;)
        {
		if ((msglen = recv(clientSock,msg, MAXLINE, 0)) < 0)
			printf("recv() failed");
	 	if(msg[0] == 'q')
	         {
			printf("Connection closed from client\n");
			close(clientSock);
			break;
		  }
		printf("Received message from client is  %s\n",msg);
	        int ans = solve(msg);
		char smsg[1024];
		int i;
		smsg[0] = ans + '0';
		printf("Sending message to client is %s\n",smsg);
		if (msglen > 0) 
		{
			if (send(clientSock, smsg,2, 0) != 2)
				printf("send() failed");
		}
	}
	close(servSock);
	return 0;
}
     	
    	
    	
    