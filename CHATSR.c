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
        int idx;
};
struct clt{
        int sck;
        char name[100];
        int flag;
}user[1000];
int count=0;
void *threadmain(void *p)
{
        int sock=((struct threadS *)p)->sck;
        int c=((struct threadS *)p)->idx;
        free(p);
        user[c].sck=sock;

        char buff[1024],buff1[1024],buff2[1023],buff3[1024];
        int i,j;

        char mess[100];
        recv(sock,buff,1024,0);
        strcpy(user[c].name,buff);
        user[c].flag=1;
        char list[1023];
        strcpy(list,"list");
        printf("Username is %s\n",user[c].name);
        while(1)
        {
        recv(sock,buff1,100,0);
        printf("message is %s\n",buff1);
        if(strcmp(buff1,"list")==0)
        {
                int k=0;
                for(i=0;i<count;i++)
                {
                        if(user[i].flag==1)
     {
                                printf("User found %s\n",user[i].name);
                                for(j=0;user[i].name[j]!='\0'; ++j)
                                {
                                        mess[k++]=user[i].name[j];
                                }
                                mess[k++]=' ';
                        }
                }
                mess[k++]='\0';
                int l=strlen(mess);
                send(sock,mess,l+1,0);
        }
        else if(strcmp(buff1,"send")==0)
        {
                        printf("Send is here\n");
                        recv(sock,buff3,1024,0);
                        int ans=-1;
                        for (j = 0; j <count; ++j)
                        {
                                if(strcmp(buff3,user[j].name)==0 && user[j].flag==1)
                                {
                                        ans=j;
                                        break;
                                }
                        }
                        if(ans==-1)
                        {
                                printf("error\n");
                        }
                        else
                        {
                                recv(sock,buff2,1024,0);
                                send(user[ans].sck,buff2,1024,0);
                        }
                        printf("Message is %s\n", buff2);

        }
        else
                break;
}
        user[c].flag=0;
        close(sock);

}
int main()
{
        int sock;
        if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
        {
                perror("socket eroor");
                return 1;
        }
        struct sockaddr_in serv,client;
        serv.sin_family=AF_INET;
        serv.sin_port=htons(4029);
        serv.sin_addr.s_addr=inet_addr("127.0.0.1");
        if(bind(sock,(struct sockaddr *)&serv,sizeof(serv))<0)
        {
                perror("bind error");
                return 1;
        }
        if(listen(sock,10)==0)
        {
                printf("Listen\n");

        }
        struct threadS *thd;

        int newsock;
        int cl;
        while(1)
        {
                cl=sizeof(client);
                newsock=accept(sock,(struct sockaddr *)&client,&cl);
                thd=(struct threadS *)malloc(sizeof(struct threadS));
                thd->sck=newsock;
                thd->idx=count;
                        pthread_t ptd;
                pthread_create(&ptd,NULL,threadmain,(void *)thd);
                count++;
        }
        return 0;
}

