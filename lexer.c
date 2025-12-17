/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:34:09 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:34:12 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*curr;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_token;
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

void	handle_word(char *line, int *i, t_token **head)
{
	int		start;
	char	quote;
	char	*word;

	start = *i;
	quote = 0;
	while (line[*i])
	{
		if (!quote && (line[*i] == '\'' || line[*i] == '\"'))
			quote = line[*i];
		else if (quote && line[*i] == quote)
			quote = 0;
		if (!quote && is_separator(line[*i]))
			break ;
		(*i)++;
	}
	word = ft_substr(line, start, *i - start);
	token_add_back(head, new_token(word, TOKEN_WORD));
}

void	handle_separator(char *line, int *i, t_token **head)
{
	if (line[*i] == '|')
	{
		token_add_back(head, new_token(ft_strdup("|"), TOKEN_PIPE));
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			token_add_back(head, new_token(ft_strdup("<<"),
					TOKEN_REDIR_HEREDOC));
			(*i) += 2;
		}
		else
		{
			token_add_back(head, new_token(ft_strdup("<"), TOKEN_REDIR_IN));
			(*i)++;
		}
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			token_add_back(head, new_token(ft_strdup(">>"),
					TOKEN_REDIR_APPEND));
			(*i) += 2;
		}
		else
		{
			token_add_back(head, new_token(ft_strdup(">"), TOKEN_REDIR_OUT));
			(*i)++;
		}
	}
}

t_token	*tokenizer(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			handle_separator(line, &i, &head);
		else
			handle_word(line, &i, &head);
	}
	return (head);
}
