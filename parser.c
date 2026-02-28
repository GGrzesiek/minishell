/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:34:40 by sandrzej          #+#    #+#             */
/*   Updated: 2026/02/28 16:15:33 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

t_cmd	*parse_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*tmp;

	// zmiana: najpierw przechodzimy przez tokeny i podmieniamy ich tekst
	// na wersję rozwiniętą (bez cudzysłowów, z podmienionym $USER itd.)
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
		{
			char *expanded = expand_token(shell, tmp->value);
			free(tmp->value); 
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}

	head = NULL;
	curr = init_cmd();
	if (!curr)
		return (NULL);
	cmd_add_back(&head, curr);
	tmp = tokens;
	
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			curr = init_cmd();
			if (!curr)
				return (NULL);
			cmd_add_back(&head, curr);
		}
		else if (is_redir_token(tmp->type))
		{
			if (tmp->next && tmp->next->type == TOKEN_WORD)
			{
				redir_add_back(&curr->redirs, new_redir(tmp->type,
						tmp->next->value));
				tmp = tmp->next;
			}
			else
				printf("syntax error");
		}
		else if (tmp->type == TOKEN_WORD)
		{
			add_arg(curr, tmp->value);
		}
		tmp = tmp->next;
	}
	return (head);
}
