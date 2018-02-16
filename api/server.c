#include "server.h"

int fork_pid;
const char* (*func)(const char *);

int work_with_client(int sock){
    char com_buff[BUFSIZ];
    char* buffer = NULL;
    size_t com_len = (size_t) read(sock, com_buff, sizeof(com_buff));

    if(com_len == -1){
        perror("reading error");
        return 1;
    }
    if(com_len <= 0){
        const char * empty_command =  "empty command\n";
        write(sock, empty_command, strlen(empty_command));
        return 0;
    }
    com_buff[com_len] = '\0';
    const char* answer = func(com_buff);
    size_t len = strlen(answer);
    printf("\nSERVER: %s %s %zu %zu\n", com_buff, answer, com_len, len);
    write(sock, answer, len);
    free(buffer);
    return 0;
}

void proc_func(int sock) {
    while(work_with_client(sock) == 0);
    close(sock);
    exit(0);
}

void process_for_client(int listen_socket){
    int accepted_socket;

    for(;;) {
        accepted_socket = accept(listen_socket, 0, 0);
        if(-1 == accepted_socket) {
            perror("accept");
            return;
        }
        int fork_pid = fork();
        if(-1 == fork_pid) {
            perror("fork");
            return;
        } else if(0 == fork_pid) {
            close(listen_socket);
            proc_func(accepted_socket);
        } else {
            close(accepted_socket);
        }
    }
}

int start_server(const char* (*f)(const char *)){
    func = f;
    struct sockaddr_in addr;
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(-1 == listen_socket) {
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(-1 == bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr))){
        perror("bind");
        return -1;
    }

    if(-1 == listen(listen_socket, 100)) {
        perror("listen");
        return -1;
    }
    process_for_client(listen_socket);
}

int kill_server(){
    kill(fork_pid, SIGTERM);
}
