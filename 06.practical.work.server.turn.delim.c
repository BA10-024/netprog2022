#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>   
#define MAX 1024
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
    printf("Successfully connected.\n");
    char buf[MAX];
    char data[MAX];
    while(1){
        recv(clientfd,buf,sizeof(buf),0);
        printf("Messages from client: %s",buf);
        for(int i = 0; i < MAX; i++) { 
            if (buf[i] == '\n') {
            	buf[i] = '\0';
            	break;
            }
    	}	
        printf("Mesages to client: ");
        fgets(data, 1024, stdin);
        send(clientfd,data,sizeof(data),0);
        for(int i = 0; i < MAX; i++) { 
            if (data[i] == '\n') {
                data[i] = '\0';
            	break;
            }
    	}
    }
    return 0;
}
