#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h> 
int main(int argc, char *argv[]){
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd;
    unsigned short port = 8784;
    char input[100];
    strcpy(input,argv[1]);
    if ((h=gethostbyname(input)) == NULL) {
        printf("Unknown host\n");
    }
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect \n");
    } 
    else{
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
    }
    return 0;
}
