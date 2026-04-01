/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:52:45 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:55:12 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

static t_cmd	*handle_pipe(t_cmd **head)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	cmd_add_back(head, cmd);
	return (cmd);
}

static t_token	*handle_redir(t_cmd *curr, t_token *tmp)
{
	if (tmp->next && tmp->next->type == TOKEN_WORD)
	{
		redir_add_back(&curr->redirs, new_redir(tmp->type,
				tmp->next->value));
		return (tmp->next);
	}
	printf("syntax error");
	return (tmp);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*tmp;

	head = NULL;
	curr = init_cmd();
	if (!curr)
		return (NULL);
	cmd_add_back(&head, curr);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			curr = handle_pipe(&head);
		else if (is_redir_token(tmp->type))
			tmp = handle_redir(curr, tmp);
		else if (tmp->type == TOKEN_WORD)
			add_arg(curr, tmp->value);
		if (!curr)
			return (NULL);
		tmp = tmp->next;
	}
	return (head);
}
