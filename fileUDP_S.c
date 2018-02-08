#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<dirent.h>


int main()
{

struct stat stat_buf;
struct sockaddr_in sock;
sock.sin_family=AF_INET;
sock.sin_port=htons(4444);
sock.sin_addr.s_addr=htonl(INADDR_ANY);

int sockid=socket(PF_INET,SOCK_DGRAM,0);
int sz=sizeof(sock);
bind(sockid,(struct sockaddr*)&sock,sizeof(sock));
char msg[450],tod[45];
recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&sock,&sz);
printf("received directory is :%s\n",msg);
sendto(sockid,"received succesfully",sizeof("received successfully"),0,(struct sockaddr*)&sock,sizeof(sock));

DIR *d;
struct dirent *dir;

d=opendir(msg);

while((dir=readdir(d))!=NULL){
//printf("%s",tod);
printf("%s\n",dir->d_name);
sendto(sockid,dir->d_name,sizeof(dir->d_name),0,(struct sockaddr*)&sock,sizeof(sock));
}
printf("r1\n");
sendto(sockid,"quit",strlen("quit")+1,0,(struct sockaddr*)&sock,sizeof(sock));

recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&sock,&sz);

printf("received :%s\n",msg);
int fd=open(msg,O_RDONLY,0755);
int r;
while((r=read(fd,msg,100))>0)
{
printf("%s\n",msg);
sendto(sockid,msg,100,0,(struct sockaddr*)&sock,sizeof(sock));
}
}
