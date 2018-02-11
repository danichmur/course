#ifndef CLIENT_H
#define CLIENT_H

#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif

int start_client();
void send_command(const char *command, int len, char* answer);

#ifdef __cplusplus
}
#endif

#endif //CLIENT_H