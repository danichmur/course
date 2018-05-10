#include <iostream>
#include "server.h"
#include "daemon_func.h"

using namespace std;

int main() {
    initialize_ini();

    int pid = fork();
    cout << "My pid: " << pid << endl;
    if (pid == -1) {
        printf("Error: Start Daemon failed (%s)\n", strerror(errno));
        return -1;
    }
    else if (!pid){
        umask(0);
        setsid();
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        start_server(parse_command);
    }
    else {
        return 0;
    }
}