#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

const SERV_PORT=1158;

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in servaddr;

    // socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    // connect
    connect(sockfd, (struct servaddr*)&servaddr, sizeof(servaddr));
    
    char buff[1024];
    while(scanf("%1023s", buff) != EOF) {
        // write 
        write(sockfd, buff, strlen(buff));
        // read
        read(sockfd, buff, strlen(buff));
        printf("return from server: \"%s\"\n", buff);
            
    }
    // close
    close(sockfd);
    
    return 0;
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
