/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:34:33 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:34:35 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
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

// for heredoc store the content of the file in char *file.
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
	int				fdin;
	int				fdout;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char			**envp;
	struct termios	t;
	t_env			*env_list;
	char			**paths;
	int				exit_code;
	t_cmd			*cmds;
}					t_shell;

void				init_shell(t_shell *shell, char **envp);
void				init_path(t_shell *shell);
void				setup_signals(t_shell *shell);

/* main funciton to free everything and end the program at any time */
void				end(t_shell *shell, char *msg);
void				free_split(char **sp);
void				free_redirs(t_redir *head);
void				free_cmds(t_cmd *head);
void				free_tokens(t_token *head);
/* Cmd processing */
int					execute_cmd_chain(t_shell *shell, t_cmd *cmd);
int	validate_command(t_shell *shell, t_cmd *cmd);
int					process_native_command(t_shell *shell, t_cmd *cmd);

/* Piping */
int					open_redir(t_shell *shell, t_cmd *cmd);
void				write_all(t_shell *shell, int fd, char *content);
char				*read_all(t_shell *shell, int fd);

/* Built-ins */
int					change_directory(t_shell *shell, t_cmd *cmd);
int					export(t_shell *shell, t_cmd *cmd);
int					process_end(t_shell *shell, t_cmd *cmd);
int					unset(t_shell *shell, t_cmd *cmd);
int					print_env(t_shell *shell, t_cmd *cmd);
int					pwd(t_shell *shell, t_cmd *cmd);
int					recho(t_shell *shell, t_cmd *cmd);

/* Utils */
void shperror(char *a, char *msg);
int					ft_isnumber(char *str);
void				end(t_shell *shell, char *msg);
void				free_split(char **sp);
void				free_env(t_env *node);
void				close_pipe(t_cmd *cmd);
t_cmd				*init_single_cmd(t_shell *shell, char *line);

/* lexer and parser functions */
t_token				*tokenizer(char *line);
t_cmd				*init_cmd(void);
void				cmd_add_back(t_cmd **head, t_cmd *new_cmd);
t_cmd				*parse_tokens(t_token *tokens);
void				redir_add_back(t_redir **head, t_redir *new);
t_redir				*new_redir(t_token_type type, char *filename);
int					add_arg(t_cmd *cmd, char *arg);

/* Env variable manager */
void				print_sorted_declare_env(t_shell *shell, t_cmd *cmd);
t_env				*new_env_node(char *str);
int					env_add_back(t_env **head, t_env *new_node);
int					env_del(t_env **head, char *key);
char				*env_get(t_env **head, char *key);

#endif
