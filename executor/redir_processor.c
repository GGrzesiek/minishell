/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:17 by sandrzej          #+#    #+#             */
/*   Updated: 2026/02/28 13:35:02 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	process_in(t_shell *shell, t_cmd *cmd, char *file)
{
	int	fd;

  (void) shell;
	fd = open(file, O_RDONLY);
	if (fd == -1)
    return (perror(file), 1);
	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	cmd->fdin = fd;
	return (0);
}

static int	process_heredoc(t_shell *shell, t_cmd *cmd, char *delimiter)
{
	int		p[2];
	char	*line;

	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	if (pipe(p) == -1)
		end(shell, "pipe fail");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write_all(shell, p[1], line);
		write_all(shell, p[1], "\n");
		free(line);
	}
	close(p[1]);
	cmd->fdin = p[0];
	return (0);
}

static int	process_out(t_shell *shell, t_cmd *cmd, char *file)
{
	int	fd;

  (void) shell;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1)
    return (perror(file), 1);
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	cmd->fdout = fd;
	return (0);
}

static int	process_append(t_shell *shell, t_cmd *cmd, char *file)
{
	int	fd;

  (void) shell;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (fd == -1)
    return (perror(file), 1);
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	cmd->fdout = fd;
	return (0);
}

int	open_redir(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	int		r_code;
	int		code;

	r_code = 0;
	code = 0;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			code = process_in(shell, cmd, redir->file);
		else if (redir->type == TOKEN_REDIR_HEREDOC)
			code = process_heredoc(shell, cmd, redir->file);
		else if (redir->type == TOKEN_REDIR_OUT)
			code = process_out(shell, cmd, redir->file);
		else if (redir->type == TOKEN_REDIR_APPEND)
			code = process_append(shell, cmd, redir->file);
		redir = redir->next;
		if (code)
			r_code = 1;
	}
	return (r_code);
}
