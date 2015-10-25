#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

// 注：以上头文件的添加查阅linux man page得到(http://linux.die.net/man/3/htons)

const char * SERV_ADDR = "127.0.0.1";
const int SERV_PORT = 1158;

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in servaddr;

    int port = SERV_PORT;
    if(argc == 2) {
        port = atoi(argv[1]);
    }

    // socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERV_ADDR);

    // connect
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    char buff[1024];
    memset(buff, '\0', sizeof(buff));
    // 一般情况下，使用 %s 的scanf()函数只会把一个单词而不是整个句子作为字符串读入!
    // 所以， hello world会被分两次处理
    // while(scanf("%1023s", buff) != EOF) {
    // fgets()函数会把换行符也读入
    while(fgets(buff, sizeof(buff), stdin) != NULL) {
        // write 
        printf("in buff: \"%s\"\n", buff);
        write(sockfd, buff, strlen(buff));
        memset(buff, '\0', sizeof(buff));
        // read
        read(sockfd, buff, sizeof(buff));
        printf("return from server: \"%s\"\n", buff);
        memset(buff, '\0', sizeof(buff));
    }
    // close
    close(sockfd);
    
    return 0;
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
