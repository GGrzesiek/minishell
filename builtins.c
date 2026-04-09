/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:53:27 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:53:28 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dispatch_export(t_shell *shell, t_cmd *cmd)
{
	t_env	*node;

	if (!cmd->args[1])
		return ;
	node = new_env_node(cmd->args[1]);
	if (!node)
		end(shell, "envp malloc error\n");
	env_add_back(&shell->env_list, node);
}

static void	dispatch_unset(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->args[1])
		return ;
	if (ft_strncmp("PATH", cmd->args[1], 5) == 0)
	{
		free_split(shell->paths);
		shell->paths = NULL;
	}
	env_del(&shell->env_list, cmd->args[1]);
}

static void	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
	{
		nl = 0;
		i = 2;
	}
	while (cmd->args[i])
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
}

static void	builtin_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwdir(shell);
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
}

void	dispatch_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strncmp("exit", name, 5) == 0)
		end(shell, NULL);
	else if (ft_strncmp("cd", name, 3) == 0)
		change_directory(shell, cmd->args[1]);
	else if (ft_strncmp("export", name, 7) == 0)
		dispatch_export(shell, cmd);
	else if (ft_strncmp("unset", name, 6) == 0)
		dispatch_unset(shell, cmd);
	else if (ft_strncmp("env", name, 4) == 0)
		print_env(shell, &shell->env_list);
	else if (ft_strncmp("echo", name, 5) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp("pwd", name, 4) == 0)
		builtin_pwd(shell);
}
