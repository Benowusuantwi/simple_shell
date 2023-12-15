#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

extern char **environ;
/*void process_command(char *command);*/
void executecommand(char **args, char *argv0, size_t arg_count);
char **tokenize(char *str, const char *delim);
void get_path(char **command);

#endif
