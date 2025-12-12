
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
	char			**args;
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
void  end(t_shell *shell, char *msg);
void  free_split(char **sp);

void execute_command(t_shell *shell, t_cmd *cmd);
/* executes the command with already parsed path */
void execute_native_command(t_shell *shell, t_cmd *cmd);

void write_all(t_shell *shell, int fd, char *content);
char *read_all(t_shell *shell, int fd);

char *getcwdir(t_shell *shell);
void change_directory(t_shell *shell, char *to);

/*TESTING*/
t_cmd *init_single_cmd(t_shell *shell, char *line);

t_env	*new_env_node(char *str);
void	env_add_back(t_env **head, t_env *new_node);
void env_del(t_env **head, char *key);
void init_path(t_shell *shell);
char *env_get(t_env **head, char *key);
void print_env(t_shell *shell, t_env **head);

#endif
