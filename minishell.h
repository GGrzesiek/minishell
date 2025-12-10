
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
#include "libft/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
}	t_token_type;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;	
}	t_env;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args; // first arg is the name
  char			*path;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
  int argc;
  char **argv;
  char **envp;
	t_env	*env_list;
  char **paths;
	int		exit_code;
	t_cmd	*cmds;
}	t_shell;

void	init_shell(t_shell *shell, char **envp);
void	setup_signals(void);

/* main funciton to free everything and end the program at any time */
void end(t_shell *shell, char *msg);

/* Finds the command on the path, and initializes cmd->path for execution */
void validate_command(t_shell *shell, t_cmd *cmd);

/* execute a command, with given arguments and STDIN_FILENO content. Returns the STDOUT_FILENO output of the command. */
char *execute_command(t_shell *shell, t_cmd *cmd, char *input);

void write_all(t_shell *shell, int fd, char *content);
char *read_all(t_shell *shell, int fd);

/*TESTING*/
t_cmd *init_single_cmd(t_shell *shell, char *line);

#endif
