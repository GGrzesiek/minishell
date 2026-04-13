/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:05:00 by emilka            #+#    #+#             */
/*   Updated: 2026/04/13 12:05:07 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	handle_exit(t_shell *shell, t_cmd *cmd)
{
	return (process_end(shell, cmd));
}

static int	handle_cd(t_shell *shell, t_cmd *cmd)
{
	return (change_directory(shell, cmd));
}

static int	handle_pwd(t_shell *shell, t_cmd *cmd)
{
	return (pwd(shell, cmd));
}

static int	handle_export(t_shell *shell, t_cmd *cmd)
{
	if (cmd->next && cmd->args[1])
		return (0);
	return (export(shell, cmd));
}

int	execute_builtin(t_shell *shell, t_cmd *cmd, char *name)
{
	if (ft_strncmp("exit", name, 5) == 0)
		return (handle_exit(shell, cmd));
	else if (ft_strncmp("cd", name, 3) == 0)
		return (handle_cd(shell, cmd));
	else if (ft_strncmp("pwd", name, 4) == 0)
		return (handle_pwd(shell, cmd));
	else if (ft_strncmp("export", name, 7) == 0)
		return (handle_export(shell, cmd));
	else if (ft_strncmp("unset", name, 6) == 0)
		return (unset(shell, cmd));
	else if (ft_strncmp("env", name, 4) == 0)
		return (print_env(shell, cmd));
	else if (ft_strncmp("echo", name, 5) == 0)
		return (recho(shell, cmd));
	return (-1);
}
