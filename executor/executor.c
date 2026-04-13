/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:37:49 by sandrzej          #+#    #+#             */
/*   Updated: 2026/04/13 12:06:25 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shlvl;

/*
	cmd->fdout = p[1];      // write end
	cmd->next->fdin = p[0]; // read end
*/
static void	open_pipe(t_shell *shell, t_cmd *cmd)
{
	int	p[2];

	if (pipe(p) == -1)
		end(shell, "pipe fail");
	cmd->fdout = p[1];
	cmd->next->fdin = p[0];
}

int	execute_command(t_shell *shell, t_cmd *cmd)
{
	char	*name;
	int		result;

	free_split(shell->paths);
	init_path(shell);
	name = cmd->args[0];
	if (!name)
		return (close_pipe(cmd), 1);
	result = execute_builtin(shell, cmd, name);
	if (result != -1)
		return (result);
	return (process_native_command(shell, cmd));
}

static int	execute_loop(t_shell *shell, t_cmd *cmd)
{
	int	last_redir_fail;

	last_redir_fail = 0;
	while (cmd)
	{
		cmd->fdout = STDOUT_FILENO;
		if (cmd->next)
			open_pipe(shell, cmd);
		if (run_cmd(shell, cmd))
		{
			if (shell->exit_code == 0)
				shell->exit_code = 1;
			last_redir_fail = (!cmd->next);
		}
		else
			last_redir_fail = 0;
		if (cmd->fdin != STDIN_FILENO)
			close(cmd->fdin);
		if (cmd->fdout != STDOUT_FILENO)
			close(cmd->fdout);
		cmd = cmd->next;
	}
	return (last_redir_fail);
}

static void	wait_children(t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid != shell->last_pid)
		{
			pid = wait(&status);
			continue ;
		}
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_code = 128 + WTERMSIG(status);
		pid = wait(&status);
	}
}

int	execute_cmd_chain(t_shell *shell, t_cmd *cmd)
{
	int	last_redir_fail;

	cmd->fdin = STDIN_FILENO;
	g_shlvl++;
	last_redir_fail = execute_loop(shell, cmd);
	wait_children(shell);
	if (last_redir_fail)
		shell->exit_code = 1;
	g_shlvl--;
	return (0);
}
