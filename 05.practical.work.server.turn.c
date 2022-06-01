#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>   
int main() {
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;	
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket.");
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
	printf("Error binding.");
    }
    if (listen(sockfd, 5) < 0) {
        printf("Error listening.");
    }
    clen=sizeof(caddr);
    if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error connection.");
    }
    else{  
        printf("Successfully connected.\n");
        char buf[1024];
        char data[1024];
        while(1){
            recv(clientfd,buf,sizeof(buf),0);
            printf("Messages from client: %s",buf);
            scanf("%s",buf);
            send(clientfd,data,sizeof(data),0);
        }
    }
    return 0;
 }
