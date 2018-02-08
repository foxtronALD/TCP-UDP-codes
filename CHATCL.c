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
#include <pthread.h>
struct threadS{
        int sck;
};
void *threadmain(void *p)
{
        int sock=((struct threadS *)p)->sck;
        char buff[1025];
        while(1){
        recv(sock,buff,1024,0);
        printf("%s\n",buff);
     }
        close(sock);
        pthread_exit(NULL);

}
int main()
{
        int sock;
        if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
        {
                perror("Socket");
                return 1;
        }
        struct sockaddr_in serv;
        memset(&serv,0,sizeof(serv));
        serv.sin_family=AF_INET;
        serv.sin_port=htons(4029);
        serv.sin_addr.s_addr=inet_addr("127.0.0.1");
        if(connect(sock,(struct sockaddr *)&serv,sizeof(serv))<0)
        {
                perror("connect");
                return 1;
        }
        pthread_t ptd;
        struct threadS *thd;

        thd=(struct threadS *)malloc(sizeof(struct threadS));
        thd->sck=sock;
   pthread_create(&ptd,NULL,threadmain,(void *)thd);
        char message[1024];
        while(1)
    {
        scanf(" %s",message);
        int len=strlen(message);
        if((send(sock,message,len+2,0))<0)
        {
                perror("send error");
                return 1;
        }
    }

        return 0;
}
