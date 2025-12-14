
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
}					t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*path;
  int fdin;
  int fdout;
	t_redir		*redirs;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	int				argc;
	char			**argv;
	char			**envp;
	t_env			*env_list;
	char			**paths;
	int				exit_code;
	t_cmd			*cmds;
}					t_shell;

void				init_shell(t_shell *shell, char **envp);
void				init_path(t_shell *shell);
void				setup_signals(void);

/* Cmd processing */
int execute_cmd_chain(t_shell *shell, t_cmd *cmd);
void				validate_command(t_shell *shell, t_cmd *cmd);
int	process_native_command(t_shell *shell, t_cmd *cmd);

/* Piping */
void				write_all(t_shell *shell, int fd, char *content);
char				*read_all(t_shell *shell, int fd);

/* Built-ins */
int				change_directory(t_shell *shell, t_cmd *cmd);
int				export(t_shell *shell, t_cmd *cmd);
int				unset(t_shell *shell, t_cmd *cmd);
int	      print_env(t_shell *shell, t_cmd *cmd);

/* Utils */
char				*getcwdir(t_shell *shell);
void				end(t_shell *shell, char *msg);
void				free_split(char **sp);
void free_env(t_env *node);
void close_pipe(t_cmd *cmd);

/* Env variable manager */
t_env				*new_env_node(char *str);
int				env_add_back(t_env **head, t_env *new_node);
int				env_del(t_env **head, char *key);
char				*env_get(t_env **head, char *key);

/*TESTING*/
t_cmd				*init_single_cmd(t_shell *shell, char *line);

#endif
