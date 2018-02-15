#include "client.h"

char* send_from_web(const char *command, int len){
  start_client();
  char* answer = (char*)malloc(1000);
  send_command(command, len, answer);
  return answer;
}