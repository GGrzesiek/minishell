/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:34:24 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 07:06:45 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef int			t_pipe[2];

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
	t_redir			*redirs;
	int				heredoc_fd;
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

typedef struct s_pipe_ctx
{
	t_pipe			*pipes;
	int				n;
	int				idx;
}					t_pipe_ctx;

void				init_shell(t_shell *shell, char **envp);
void				setup_signals(void);

/* main funciton to free everything and end the program at any time */
void				end(t_shell *shell, char *msg);
void				free_split(char **sp);
void				free_redirs(t_redir *head);
void				free_cmds(t_cmd *head);
void				free_tokens(t_token *head);

int					is_builtin(char *name);
void				dispatch_builtin(t_shell *shell, t_cmd *cmd);
void				execute_command(t_shell *shell, t_cmd *cmds);
void				execute_pipeline(t_shell *shell, t_cmd *cmds);
int					apply_redirections(t_shell *shell, t_cmd *cmd);
void				exec_external(t_shell *shell, t_cmd *cmd);
int					handle_heredoc(t_shell *shell, char *delim);
void				close_pipes(t_pipe *pipes, int n_pipes);
void				setup_heredocs(t_shell *shell, t_cmd *cmds);
t_pipe				*init_pipes(t_shell *shell, int n);
void				cleanup_pipeline(t_cmd *cmds, t_pipe *pipes, int n_pipes);

void				write_all(t_shell *shell, int fd, char *content);
char				*read_all(t_shell *shell, int fd);

char				*getcwdir(t_shell *shell);
void				change_directory(t_shell *shell, char *to);

/* lexer and parser functions */
t_token				*new_token(char *value, t_token_type type);
void				token_add_back(t_token **head, t_token *new_tok);
int					is_separator(char c);
t_token				*tokenizer(char *line);
t_cmd				*init_cmd(void);
void				cmd_add_back(t_cmd **head, t_cmd *new_cmd);
t_cmd				*parse_tokens(t_token *tokens);
void				redir_add_back(t_redir **head, t_redir *new);
t_redir				*new_redir(t_token_type type, char *filename);
int					add_arg(t_cmd *cmd, char *arg);
extern int			g_shlvl;

/*TESTING*/
t_cmd				*init_single_cmd(t_shell *shell, char *line);

t_env				*new_env_node(char *str);
void				env_add_back(t_env **head, t_env *new_node);
void				env_del(t_env **head, char *key);
void				init_path(t_shell *shell);
char				*env_get(t_env **head, char *key);
void				print_env(t_shell *shell, t_env **head);

#endif
