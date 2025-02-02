#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>

int main(){
    char input[200];
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd;
    unsigned short port = 8784;

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket \n");
        return 1;
    }
    printf("Enter host domain name: ");
    fgets(input,200,stdin);
    input[strlen(input)-1]='\0';
    if ((h=gethostbyname(input)) == NULL) {
        printf("Unknown host \n");
        return 1;
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        return 1;
    }
    printf("Successfully connected to server.\n ");
    char buf[1024];
    char data[1024];
    while(1){
        printf("Enter the messages: ");
        scanf("%s",buf);
        send(sockfd,buf,sizeof(buf),0);
        recv(sockfd,data,sizeof(data),0);
        printf("Messages from server: %s \n",data);
    }
    return 0;
}
