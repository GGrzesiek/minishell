/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sorter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:58 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 15:52:00 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static t_env	*find_great(t_env *curr, char *last_key)
{
	t_env	*great_node;
	int		is_great;

	great_node = NULL;
	while (curr)
	{
		is_great = 0;
		if (last_key == NULL || ft_strncmp(curr->key, last_key, INT_MAX) > 0)
			is_great = 1;
		if (is_great && (great_node == NULL || ft_strncmp(curr->key,
					great_node->key, INT_MAX) < 0))
			great_node = curr;
		curr = curr->next;
	}
	return (great_node);
}

static void	run_child(t_shell *shell)
{
	t_env	*curr;
	char	*last_key;
	t_env	*great_node;

	last_key = NULL;
	while (1)
	{
		curr = shell->env_list;
		great_node = NULL;
		great_node = find_great(curr, last_key);
		if (great_node == NULL)
			break ;
		printf("declare -x %s=\"%s\"\n", great_node->key, great_node->value);
		last_key = great_node->key;
	}
	end(shell, NULL);
}

void	print_sorted_declare_env(t_shell *shell, t_cmd *cmd)
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
		run_child(shell);
	}
}
