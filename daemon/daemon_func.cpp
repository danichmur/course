//
// Created by parallels on 2/11/18.
//
#include "daemon_func.h"
#include <vector>
#include <cstring>
#include <functional>
#include <map>
#include <utility>

#define DAEMON_ERR_NUM 15

char const *daemon_text[DAEMON_ERR_NUM] = {
        "the database was successfully renamed",    // 0
        "the database can not be renamed",          // 1
        "error parsing args. Must be 3",            // 2
        "the database was successfully removed",    // 3
        "the database can not be removed",          // 4
        "error parsing args. Must be 2",            // 5
        "the database was successfully created",    // 6
        "the database can not be created",          // 7
        "new path was successfully setted",         // 8
        "new path can not be setted",               // 9
        "error parsing args.",                      // 10
        "the database was successfully updated",    // 11
        "the database can not be updated",          // 12
        "the database can not be fetched",          // 13
        "the database was successfully fetched"     // 14
};

std::pair<int, char**> split(std::string str, std::string delim){
    std::vector<std::string> result;
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
    return std::make_pair(argc, argv);
}

const char* daemon_rename(const char* name1, const char* name2){
    if(rrdtools_rename(name1, name2) == 0){
        return daemon_text[0];
    }
    return daemon_text[1];
}

const char* daemon_remove(const char *name){
    if(rrdtools_remove(name) == 0){
        return daemon_text[3];
    }
    return daemon_text[4];
}

const char* daemon_info(const char *name){
    char *db_info = (char *) calloc(COUNT*LEN, sizeof(char));
    rrdtools_info(name, db_info);
    return db_info;
}

const char* daemon_insert(int argc, char** argv){
    for(int i = 1; i < argc; i++){
        argv[i - 1] = argv[i];
    }
    if(rrdtools_update(argc - 1, argv) == -1){
        return rrd_get_error();
    }
    return daemon_text[11];
}

const char* daemon_create(int argc, char **argv){
    for(int i = 1; i < argc; i++){
        argv[i - 1] = argv[i];
    }
    if(rrdtools_create(argc - 1, argv) == 0){
        return daemon_text[6];
    }
    return daemon_text[7];
}

const char* daemon_fetch(int argc, char **argv){
    char *name, *cf, *filename = nullptr, *pEnd;
    FETCH_TYPE fetch_type;
    time_t start, end;
    unsigned long step;
    bool in_file;

    int opt = 0;
    while ((opt = getopt(argc, argv, "n:c:s:e:p:f:t:")) != -1) {
        switch(opt) {
            case 'n':
                name = optarg;
                break;
            case 'c':
                cf = optarg;
                break;
            case 's':
                start = strtol(optarg, &pEnd, 10);
                break;
            case 'e':
                end = strtol(optarg, &pEnd, 10);
                break;
            case 'p':
                step = strtoul(optarg, &pEnd, 10);
                break;
            case 'f':
                filename = optarg;
                break;
            case 't':{
                if(strcmp(optarg, "JSON") == 0){
                    fetch_type = JSON;
                } else if(strcmp(optarg, "CSV") == 0){
                    fetch_type = CSV;
                } else return daemon_text[10];
                break;
            }
            default:
                return daemon_text[10];
        }
    }

    if(filename == nullptr){
        char *result = (char *) calloc(COUNT*LEN, sizeof(char));
        if(rrdtools_fetch(name, cf, &start, &end, &step, result, fetch_type) == 1){
            return daemon_text[13];
        }
        return result;
    }
    if(rrdtools_fetch_in_file(name, cf, &start, &end, &step, filename, fetch_type) == 1){
        return daemon_text[13];
    }
    return daemon_text[14];
}

const char* daemon_set_path(char **argv){
    if(strcmp(argv[1], "r") == 0){
        if(set_res_path(argv[2]) == 0){
            return daemon_text[8];
        }
        return daemon_text[9];
    }
    if(strcmp(argv[1], "d") == 0){
        if(set_db_path(argv[2]) == 0){
            return daemon_text[8];
        }
        return daemon_text[9];
    }
    return daemon_text[10];
}

const char* daemon_get_path(char **argv){
    if(strcmp(argv[1], "r") == 0){
        return get_res_path();
    }
    if(strcmp(argv[1], "d") == 0){
        return get_db_path();
    }
    return daemon_text[10];
}

const char* parse_command(const char *command){
    auto split_result = split(command, " ");
    char** argv = split_result.second;
    int argc = split_result.first;
    char c = argv[0][0];
    switch(c){
        case 'n': {
            if (argc != 3) {
                return daemon_text[2];
            }
            return daemon_rename(argv[1], argv[2]);
        }
        case 'r': {
            return parse_rrdtool_command(argc, argv);
        }
        case 'a': {
            char *dbs = (char *) calloc(COUNT*LEN, sizeof(char));
            daemon_all_dbs(dbs);
            return dbs;
        }
        case 'd':{
            if(argc != 2){
                return daemon_text[5];
            }
            return daemon_remove(argv[1]);
        }
        case 's':{
            if(argc != 3){
                return daemon_text[2];
            }
            return daemon_set_path(argv);
        }
        case 'g':{
            if(argc != 2){
                return daemon_text[5];
            }
            return daemon_get_path(argv);
        }
        case 'u':{
            if(argc != 2){
                return daemon_text[5];
            }
            return daemon_insert(argc, argv);
        }
        default:
            perror("error parsing args.");
            break;
    }
    return daemon_text[10];
}

const char* parse_rrdtool_command(int argc, char **argv){
    if(strcmp(argv[1], "create") == 0){
        return daemon_create(argc, argv);
    }

    if(strcmp(argv[1], "info") == 0){
        if(argc != 3){
            return daemon_text[2];
        }
        return daemon_info(argv[3]);
    }

    if(strcmp(argv[1], "update") == 0){
        if(argc != 4){
            return daemon_text[2];
        }
        return daemon_info(argv[10]);
    }

    if(strcmp(argv[1], "fetch") == 0){
        if(argc <= 7){
            return daemon_text[10];
        }
        return daemon_fetch(argc, argv);
    }
    return daemon_text[10];
}

void daemon_all_dbs(char *dbs) {
    char **list = (char **) calloc(COUNT, sizeof(char *));
    for (int i = 0; i < COUNT; i++) {
        list[i] = (char *) calloc(LEN, sizeof(char));
    }

    get_db_list(list);
    int i = 0;
    strcpy(dbs, list[i]);
    free(list[i]);
    while (strcmp(list[++i], "") != 0) {
        strcat(dbs,  list[i]);
        free(list[i]);
    }
    if (i == 0) {
        strcpy(dbs,"Databases not found!");
    }
    free(list);
}