#ifndef SERVER_H
#define SERVER_H

#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif

int start_server(const char* (*f)(const char *));
int kill_server();

#ifdef __cplusplus
}
#endif

#endif //SERVER_H
