/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:48:18 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 15:48:19 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_redirs(t_redir *head)
{
	t_redir	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->args)
			free_split(tmp->args);
		if (tmp->redirs)
			free_redirs(tmp->redirs);
		free(tmp);
	}
}
