#include "client.h"

int sock;

int start_client(){
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return 1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        return 2;
    }
    return 0;
}

void send_command(const char *command, int len, char* answer){
    write(sock, command, len);
    ssize_t answ_len = read(sock, answer, BUFSIZ);
    if(answ_len == 0){
        perror("can't read any data");
        return;
    }
    answer[answ_len] = '\0';
}