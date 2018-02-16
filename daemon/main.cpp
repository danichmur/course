#include <iostream>
#include "server.h"
#include "daemon_func.h"

using namespace std;

int main() {
    initialize_ini();
    start_server(parse_command);

//    int pid = fork();
//    if (pid == -1) {
//        printf("Error: Start Daemon failed (%s)\n", strerror(errno));
//
//        return -1;
//    }
//    else if (!pid){
//        umask(0);
//        setsid();
//        close(STDIN_FILENO);
//        close(STDOUT_FILENO);
//        close(STDERR_FILENO);
//        start_server(parse_command);
//    }
//    else {
//        return 0;
//    }
   // while (true)
    {
        char answer[BUFSIZ];
        string input ="";
        //cout << ">>";

       // getline(cin, input);
       // if(input == "exit"){
        //    break;
        //}
        cout << parse_command(input.c_str()) << endl;
    }
    return 0;
}