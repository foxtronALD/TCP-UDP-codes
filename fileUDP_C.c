#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
int main()
{

//printf("%d\n",strcmp("a","b"));
struct sockaddr_in sock;
sock.sin_family=AF_INET;
sock.sin_port=htons(4444);
sock.sin_addr.s_addr=htonl(INADDR_ANY);

int sockid=socket(PF_INET,SOCK_DGRAM,0);

char msg[450];
int sz=sizeof(sock);
printf("enter directory name\n");
scanf("%s",msg);
sendto(sockid,msg,sizeof(msg),0,(struct sockaddr*)&sock,sizeof(sock));
recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&sock,&sz);
printf("received :%s\n",msg);

while(recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&sock,&sz)>0){
if(!strcmp(msg,"quit")){
printf("quit detected!\n");
break;
}
printf("%s\n",msg);
}
scanf("%s",msg);
sendto(sockid,msg,sizeof(msg),0,(struct sockaddr*)&sock,sizeof(sock));
int r;
while((r=recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&sock,&sz))>0)
{
 printf("%s\n",msg);
// memset(msg,0,sizeof(msg));
}

close(sockid);
}
