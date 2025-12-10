
#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_command
{
  char *command; // full command
  char **args;
  char *path; // detected path of the command
  char *name;
} t_command;

typedef struct s_data
{
  int argc;
  char **argv;
  char **envp;
  char **env_path; // processed paths from envp
} t_data;


// execute a command, with given arguments and STDIN_FILENO content. Returns the STDOUT_FILENO output of the command.
char *execute_command(char *command, char **args, char *ioinput);

void write_all(int fd, char *content);
char *read_all(int fd);

#endif
