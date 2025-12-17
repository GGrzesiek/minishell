/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:39:44 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:39:46 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static void	runn_child(t_shell *shell)
{
	t_env	*curr;
	t_env	*next_node;
	char	*last_key;
	int		is_greater_than_last;
	int		is_smaller_than_candidate;

	last_key = NULL;
	while (1)
	{
		curr = shell->env_list;
		next_node = NULL;
		while (curr)
		{
			is_greater_than_last = 0;
			if (last_key == NULL)
				is_greater_than_last = 1;
			else
			{
				if (strncmp(curr->key, last_key, 100) > 0)
					is_greater_than_last = 1;
			}
			if (is_greater_than_last)
			{
				is_smaller_than_candidate = 0;
				if (next_node == NULL)
					is_smaller_than_candidate = 1;
				else
				{
					if (strncmp(curr->key, next_node->key, 100) < 0)
						is_smaller_than_candidate = 1;
				}
				if (is_smaller_than_candidate)
					next_node = curr;
			}
			curr = curr->next;
		}
		if (next_node == NULL)
			break ;
		printf("declare -x %s=\"%s\"\n", next_node->key, next_node->value);
		last_key = next_node->key;
	}
	end(shell, NULL);
}

static void	print_sorted_declare_env(t_shell *shell, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
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
		runn_child(shell);
	}
}

int	export(t_shell *shell, t_cmd *cmd)
{
	t_env	*new_node;
	char	*key;

	key = cmd->args[1];
	if (key)
	{
		new_node = new_env_node(key);
		if (!new_node)
			end(shell, "envp new node malloc error\n");
		env_add_back(&shell->env_list, new_node);
	}
	else
		print_sorted_declare_env(shell, cmd);
	return (0);
}

int	unset(t_shell *shell, t_cmd *cmd)
{
	char	*key;

	key = cmd->args[1];
	if (key)
	{
		env_del(&shell->env_list, key);
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
