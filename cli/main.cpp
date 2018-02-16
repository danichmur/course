#include <cstdio>
#include <iostream>
#include "client.h"

using namespace std;

int main()
{
    start_client();
    while (true)
    {
        char answer[1000];
        string input;
        cout << ">>";


        getline(cin, input);
        if(input == "exit"){
            break;
        }
        send_command(input.c_str(), input.length(), answer);
        cout << answer << endl;
    }
}

