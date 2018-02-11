#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include <cstring>
#include "client.h"

using namespace std;


pair<int, char**> split(string str, string delim){
    std::vector<std::string> result;
    result.push_back("test");
    size_t pos = 0;
    while (1) {
        size_t end = str.find(delim, pos);
        if (end == str.npos) {
            result.push_back(str.substr(pos));
            break;
        } else {
            result.push_back(str.substr(pos, end - pos));
            pos = end + 1;
        }
    }
    unsigned long argc = result.size();
    char **argv = (char **) malloc(argc * sizeof(char*));
    for(int i = 0; i < argc; i++){
        argv[i] = (char *) malloc(result[i].size());
        strcpy(argv[i], result[i].c_str());
    }
    return make_pair(argc, argv);
}

int main()
{
    start_client();
    while (true)
    {
        char answer[BUFSIZ];
        string input;
        cout << ">>";

        getline(cin, input);
        if(input == "exit"){
            break;
        }
        send_command(input.c_str(), input.length(), answer);
//        auto args = split(input, " ");
        cout << answer << endl;
    }
}