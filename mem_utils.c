/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:34:26 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:37:07 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *node)
{
	free(node->value);
	free(node->key);
	free(node);
}

void	free_env_lst(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_env(tmp);
	}
}

void	end(t_shell *shell, char *msg)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->t);
	rl_clear_history();
	free_cmds(shell->cmds);
	free_env_lst(shell->env_list);
	free_split(shell->paths);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(shell->exit_code);
}

void	free_split(char **sp)
{
	int	i;

	i = 0;
	if (sp)
	{
		while (sp[i])
		{
			free(sp[i]);
			i++;
		}
		free(sp);
	}
}

void	close_pipe(t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	if (cmd->next && cmd->next->fdin != STDIN_FILENO)
		close(cmd->next->fdin);
}
