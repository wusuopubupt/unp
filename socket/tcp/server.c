#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

const int SERV_PORT=1158;
const int BACKLOG_NUM = 10;

/**
 * print error messge
 * @param err
 * @return null
 */
void err_die(const char *err) {
    printf("ERROR %s\n", err);
    perror(err);
    exit(1);
}


/**
 * reverse string
 * @param char s[]
 * @param int i
 * @param int j
 * @return null
 */
void str_rev(char s[], int i, int j) {
    while(i < j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in servaddr;
    int servaddr_len = sizeof(servaddr);

    int port = SERV_PORT;
    if(argc == 2) {
        port = atoi(argv[1]);
    }

    // socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        err_die("socket");
    }
    bzero(&servaddr, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind
    if(bind(sockfd, (struct sockaddr *)&servaddr, servaddr_len) < 0) {
        err_die("bind");
    }
    // listen
    if(listen(sockfd, BACKLOG_NUM) < 0) {
        err_die("listen");
    }
    printf("server running on port [%d]\n", SERV_PORT);
    int acceptfd;
    // 阻塞等待accept
    while(1) {
        // accept, 第三个参数是指针！(坑！)
        acceptfd = accept(sockfd, (struct sockaddr*)&servaddr, &servaddr_len);
        if(-1 == acceptfd) {
            perror("accept");
        } else {
            printf("accept from client, acceptfd is %d\n!", acceptfd);
        }

        // read
        char buff[1024];
        memset(buff, '\0', sizeof(buff));
        ssize_t n;
        // 不用要strlen(buff), 编译时就要确定，用sizeof! 
        while( (n = read(acceptfd, buff, sizeof(buff)) )  > 0) {
            printf("read from client:\"%s\"\n", buff);
            // reverse string
            str_rev(buff, 0, strlen(buff)-1);
            printf("write to client: \"%s\"\n", buff);
            // write
            write(acceptfd, buff, strlen(buff));
            // 每次read前把buff清洗下
            memset(buff, '\0', sizeof(buff));
        }
        printf("read from client, body len is 0, closing acceptfd!\n");
        
        // close acceptfd
        close(acceptfd);
    }
    // close sockfd
    close(sockfd);
    
    return 0;
}


