//
// Created by parallels on 2/11/18.
//

#ifndef DAEMON_FUNC_H
#define DAEMON_FUNC_H

#include "rrdtools.h"
#include "config_manager.h"

#define LEN 100
#define COUNT 30

const char* daemon_rename(const char*, const char*);
const char* parse_rrdtool_command(int, char**);
const char* parse_command(const char*);
const char* daemon_remove(const char *);
void daemon_all_dbs(char *);

#endif //DAEMON_DAEMON_FUNC_H
