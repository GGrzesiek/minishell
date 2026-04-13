/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:13:13 by emilka            #+#    #+#             */
/*   Updated: 2026/03/11 13:13:24 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

static void	expand_all_tokens(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;
	char	*expanded;
	char	*orig;
	int		is_var;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
		{
			orig = tmp->value;
			is_var = (orig[0] == '$' && !ft_strchr(orig, '\'')
				&& !ft_strchr(orig, '"'));
			expanded = expand_token(shell, orig);
			free(orig);
			if (is_var && !expanded[0])
			{
				free(expanded);
				tmp->value = NULL;
			}
			else
				tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}

static void	handle_redir(t_cmd *curr, t_token **tmp)
{
	t_redir	*new_node;

	if ((*tmp)->next && (*tmp)->next->type == TOKEN_WORD)
	{
		new_node = new_redir((*tmp)->type, (*tmp)->next->value);
		redir_add_back(&curr->redirs, new_node);
		*tmp = (*tmp)->next;
	}
	else
		printf("syntax error");
}

static int	handle_pipe(t_cmd **head, t_cmd **curr)
{
	*curr = init_cmd();
	if (!*curr)
		return (0);
	cmd_add_back(head, *curr);
	return (1);
}

t_cmd	*parse_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*tmp;

	expand_all_tokens(shell, tokens);
	head = NULL;
	if (!handle_pipe(&head, &curr))
		return (NULL);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			if (!handle_pipe(&head, &curr))
				return (NULL);
		}
		else if (is_redir_token(tmp->type))
			handle_redir(curr, &tmp);
		else if (tmp->type == TOKEN_WORD && tmp->value)
			add_arg(curr, tmp->value);
		tmp = tmp->next;
	}
	return (head);
}
