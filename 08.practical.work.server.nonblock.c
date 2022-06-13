#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>   
#include <fcntl.h> 
#include <unistd.h>
#include <poll.h>
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
    setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &(int){ 1 },sizeof(int));
	int fl = fcntl(sockfd, F_GETFL, 0);
    fl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, fl);
    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
	printf("Error binding.");
    }
    if (listen(sockfd, 5) < 0) {
        printf("Error listening.");
    }
    clen=sizeof(caddr);
    /*
    if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error connection.");
    }
    */
    struct pollfd fds;
    fds.fd=fileno(stdin);
    fds.events=POLLIN;
    char buf[MAX];
    char data[MAX];
    int connected=1;
    while(connected){
    	clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen);
    	if (clientfd > 0){
    		printf("Successfully connected.\n");
    		int clientfl = fcntl(clientfd, F_GETFL, 0);
    		clientfl |= O_NONBLOCK;
    		fcntl(clientfd, F_SETFL, clientfl);
    		while(1){
    			if (recv(clientfd, buf, sizeof(buf),0)>0){
    				printf("Messages from client: %s \n",buf);
        		}
        		if (poll(&fds, 1, 0) > 0) {
            		if (fds.revents & POLLIN) {
        				fgets(data,MAX,stdin);
        				if (strcmp(data,"/dc\n")==0){
            				printf("Disconnected \n");
            				break;
        				}
        				for(int i = 0; i < MAX; i++) { 
            				if (data[i] == '\n') {
            					data[i] = '\0';
            					break;
            				}
    					} 
        				send(clientfd,data,sizeof(data),0);
					}
				}	    	
    		}
    	}	
    }
    close(sockfd);
	return 0;
}
   
