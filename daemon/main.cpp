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

//    while (true)
//    {
//        //r fetch -n speed.rrd -c AVERAGE -s 920804400 -e 920809200 -f file.json
//
//        //r create speed.rrd --start 920804400 DS:speed:COUNTER:600:U:U RRA:AVERAGE:0.5:1:24 RRA:AVERAGE:0.5:6:10
//        char answer[BUFSIZ];
//        string input ="";
//        cout << ">>";
//
//        getline(cin, input);
//        if(input == "exit"){
//            break;
//        }
//        cout << parse_command(input.c_str()) << endl;
//    }
    return 0;
}