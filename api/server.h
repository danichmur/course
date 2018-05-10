#ifndef SERVER_H
#define SERVER_H

#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif

int start_server(const char* (*f)(const char *), const char* adress, unsigned int port);

#ifdef __cplusplus
}
#endif

#endif //SERVER_H
