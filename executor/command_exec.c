/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:51:53 by emilka            #+#    #+#             */
/*   Updated: 2026/04/13 11:51:40 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shlvl;

void	execute_native_path(t_shell *shell, t_cmd *cmd)
{
	if (!shell->paths)
		init_path(shell);
	if (!shell->paths)
		return ;
	validate_command(shell, cmd);
	if (cmd->path)
	{
		g_shlvl++;
		execute_native_command(shell, cmd);
		g_shlvl--;
		free(cmd->path);
	}
	else
		write_all(shell, STDOUT_FILENO, "Command not found\n");
}

void	unset_env(t_shell *shell, char *arg)
{
	if (ft_strncmp("PATH", arg, 5) == 0)
	{
		free_split(shell->paths);
		shell->paths = NULL;
	}
	env_del(&shell->env_list, arg);
}
