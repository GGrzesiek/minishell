/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:39:44 by sandrzej          #+#    #+#             */
/*   Updated: 2026/03/11 13:41:45 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export(t_shell *shell, t_cmd *cmd)
{
	t_env	*new_node;
	int		i;
	int		ret;

	if (!cmd->args[1])
		return (print_sorted_declare_env(shell, cmd), 0);
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (!valid_identifier(cmd->args[i]))
		{
			shperror("minishell: export", " not a valid identifier");
			ret = 1;
		}
		else
		{
			new_node = new_env_node(cmd->args[i]);
			if (!new_node)
				end(shell, "envp new node malloc error\n");
			env_add_back(&shell->env_list, new_node);
		}
		i++;
	}
	return (ret);
}

int	unset(t_shell *shell, t_cmd *cmd)
{
	char	*key;

	key = cmd->args[1];
	if (key)
	{
		return (env_del(&shell->env_list, key));
	}
	return (0);
}

static void	run_child(t_shell *shell, t_cmd *cmd)
{
	t_env	*curr;

	curr = shell->env_list;
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
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	end(shell, NULL);
}

int	print_env(t_shell *shell, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
	{
		run_child(shell, cmd);
	}
	return (0);
}
