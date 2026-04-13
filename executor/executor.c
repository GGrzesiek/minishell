/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:37:49 by sandrzej          #+#    #+#             */
/*   Updated: 2026/03/11 13:43:20 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shlvl;

/*
	cmd->fdout = p[1];      // write end
	cmd->next->fdin = p[0]; // read end
*/
void	open_pipe(t_shell *shell, t_cmd *cmd)
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

	free_split(shell->paths);
	init_path(shell);
	name = cmd->args[0];
	if (!name)
		return (close_pipe(cmd), 1);
	if (ft_strncmp("exit", name, 5) == 0)
		return (process_end(shell, cmd));
	else if (ft_strncmp("cd", name, 3) == 0)
		return (change_directory(shell, cmd));
	else if (ft_strncmp("pwd", name, 4) == 0)
		return (pwd(shell, cmd));
	else if (ft_strncmp("export", name, 7) == 0)
		return (cmd->next && cmd->args[1] ? 0 : export(shell, cmd));
	else if (ft_strncmp("unset", name, 6) == 0)
		return (unset(shell, cmd));
	else if (ft_strncmp("env", name, 4) == 0)
		return (print_env(shell, cmd));
	else if (ft_strncmp("echo", name, 5) == 0)
		return (recho(shell, cmd));
	else
		return (process_native_command(shell, cmd));
}

static int	execute_loop(t_shell *shell, t_cmd *cmd)
{
	int	last_redir_fail;

	last_redir_fail = 0;
	while (1)
	{
		cmd->fdout = STDOUT_FILENO;
		if (cmd->next)
			open_pipe(shell, cmd);
		if (run_cmd(shell, cmd))
		{
			shell->exit_code = 1;
			last_redir_fail = (!cmd->next);
		}
		else
			last_redir_fail = 0;
		if (cmd->fdin != STDIN_FILENO)
			close(cmd->fdin);
		if (cmd->fdout != STDOUT_FILENO)
			close(cmd->fdout);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	return (last_redir_fail);
}

static void	wait_children(t_shell *shell)
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		if (pid != shell->last_pid)
			continue ;
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_code = 128 + WTERMSIG(status);
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
