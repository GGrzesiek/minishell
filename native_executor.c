/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:52:53 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:52:54 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cmd_path(t_shell *shell, char *name)
{
	char	*path;
	int		j;

	if (name[0] == '/' || (name[0] == '.' && name[1] == '/'))
	{
		if (access(name, X_OK) == 0)
			return (ft_strdup(name));
		return (NULL);
	}
	if (!shell->paths)
		return (NULL);
	j = 0;
	while (shell->paths[j])
	{
		path = ft_strjoin(shell->paths[j], name);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		j++;
	}
	return (NULL);
}

static int	apply_file_redir(t_redir *r)
{
	int	fd;

	if (r->type == TOKEN_REDIR_IN)
		fd = open(r->file, O_RDONLY);
	else if (r->type == TOKEN_REDIR_OUT)
		fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(r->file), -1);
	if (r->type == TOKEN_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_shell *shell, t_cmd *cmd)
{
	t_redir	*r;

	(void)shell;
	r = cmd->redirs;
	while (r)
	{
		if (r->type == TOKEN_REDIR_HEREDOC)
		{
			if (cmd->heredoc_fd >= 0)
				dup2(cmd->heredoc_fd, STDIN_FILENO);
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
		}
		else if (apply_file_redir(r) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}

void	exec_external(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = find_cmd_path(shell, cmd->args[0]);
	if (!path)
	{
		write(STDERR_FILENO, cmd->args[0], ft_strlen(cmd->args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(127);
	}
	execve(path, cmd->args, shell->envp);
	perror(cmd->args[0]);
	free(path);
	exit(126);
}
