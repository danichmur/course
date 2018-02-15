#include "client.h"

void send_from_web(const char *command, int len, char* answer){
	send_command(command, len, answer);
}