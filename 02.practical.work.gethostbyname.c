#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
int main(int argc, char *argv[]){
    struct hostent *hostname;
    struct in_addr *ip;
    char input[20];
    strcpy(input, argv[1]);
    printf("Hostname : %s \n",input);
    hostname = gethostbyname(input);
    if (hostname == NULL){
        printf("Failed to get host by name.\n");
        return 0;
    }
    for(int i=0; hostname->h_addr_list[i] != NULL; i++){
            printf("Hostname %s was resolved to IP address: %s\n",input, inet_ntoa(*(struct in_addr *) (hostname->h_addr_list[i])));   
    }
    return 0;
}
