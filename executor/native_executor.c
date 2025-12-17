/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:39:55 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:39:58 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static void	run_child(t_shell *shell, t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			end(shell, "dup2 input fail");
		close(cmd->fdin);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
			end(shell, "dup2 output fail");
		close(cmd->fdout);
	}
	if (cmd->next)
		close(cmd->next->fdin);
	execve(cmd->path, cmd->args, shell->envp);
	perror(cmd->args[0]);
	free(cmd->path);
	end(shell, NULL);
}

void	execute_native_command(t_shell *shell, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
		run_child(shell, cmd);
}

int is_directory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int	process_native_command(t_shell *shell, t_cmd *cmd)
{
	if (validate_command(shell, cmd))
    return (1);
	if (cmd->path)
	{
		execute_native_command(shell, cmd);
		free(cmd->path);
	}
	return (0);
}
