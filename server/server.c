#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
    char *table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int port = 10000;
    int lsock, asock, pid;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clint_addr;
    socklen_t clnt_addr_size;

    lsock = socket(AF_INET, SOCK_STREAM, 0);
    if(lsock == -1){
        puts("socker error");
        exit(-1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    printf("port : %d\n", port);

    if(bind(lsock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        puts("bind error");
        exit(-1);
    }
    if (listen(lsock, 100) < 0) {
        puts("listen error");
        exit(-1);
    }
    signal(SIGCHLD, SIG_IGN);

    asock = accept(lsock, (struct sockaddr *)&clint_addr, &clnt_addr_size);
    if (asock < 0) {
        puts("accept error.");
        return 0;
    }
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned char key[16] = {0, };
    char realkey[16] = { 0, };
    read(fd, key, 16);
    close(fd);
    for(int i = 0; i < 16; i++)
        realkey[i] = table[key[i]%62];
    write(1, "Key : ", 6);
    write(1, realkey, 16);
    write(asock, realkey, 16);
    close(asock);
    close(lsock);

    return 0;
}