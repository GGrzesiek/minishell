/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:50:17 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 15:50:19 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	process_in(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	cmd->fdin = fd;
	return (0);
}

static int	process_heredoc(t_shell *shell, t_cmd *cmd, char *file)
{
	int	p[2];

	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	if (pipe(p) == -1)
		end(shell, "pipe fail");
	write_all(shell, p[1], file);
	close(p[1]);
	cmd->fdin = p[0];
	return (0);
}

static int	process_out(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	cmd->fdout = fd;
	return (0);
}

static int	process_append(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
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
			code = process_in(cmd, redir->file);
		else if (redir->type == TOKEN_REDIR_HEREDOC)
			code = process_heredoc(shell, cmd, redir->file);
		else if (redir->type == TOKEN_REDIR_OUT)
			code = process_out(cmd, redir->file);
		else if (redir->type == TOKEN_REDIR_APPEND)
			code = process_append(cmd, redir->file);
		redir = redir->next;
		if (code)
			r_code = 1;
	}
	return (r_code);
}
