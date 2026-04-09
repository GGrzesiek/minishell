/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:52:42 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:52:43 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_shell *shell, char *delim)
{
	int		pipefd[2];
	char	*line;

	(void)shell;
	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

void	close_pipes(t_pipe *pipes, int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	setup_heredocs(t_shell *shell, t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == TOKEN_REDIR_HEREDOC)
			{
				if (cmd->heredoc_fd >= 0)
					close(cmd->heredoc_fd);
				cmd->heredoc_fd = handle_heredoc(shell, r->file);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

t_pipe	*init_pipes(t_shell *shell, int n)
{
	t_pipe	*pipes;
	int		i;
	int		count;

	count = n - 1;
	if (count < 1)
		count = 1;
	pipes = malloc(sizeof(t_pipe) * count);
	if (!pipes)
		end(shell, "malloc error\n");
	i = 0;
	while (i < n - 1)
	{
		if (pipe(pipes[i]) < 0)
			end(shell, "pipe error\n");
		i++;
	}
	return (pipes);
}

void	cleanup_pipeline(t_cmd *cmds, t_pipe *pipes, int n_pipes)
{
	t_cmd	*cmd;

	close_pipes(pipes, n_pipes);
	cmd = cmds;
	while (cmd)
	{
		if (cmd->heredoc_fd >= 0)
		{
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
		}
		cmd = cmd->next;
	}
}
