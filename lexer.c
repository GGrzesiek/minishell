/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:16:51 by emilka            #+#    #+#             */
/*   Updated: 2026/03/11 13:19:21 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir_in(char *line, int *i, t_token **head)
{
	if (line[*i + 1] == '<')
	{
		token_add_back(head, new_token(ft_strdup("<<"), TOKEN_REDIR_HEREDOC));
		(*i) += 2;
	}
	else
	{
		token_add_back(head, new_token(ft_strdup("<"), TOKEN_REDIR_IN));
		(*i)++;
	}
}

static void	handle_redir_out(char *line, int *i, t_token **head)
{
	if (line[*i + 1] == '>')
	{
		token_add_back(head, new_token(ft_strdup(">>"), TOKEN_REDIR_APPEND));
		(*i) += 2;
	}
	else
	{
		token_add_back(head, new_token(ft_strdup(">"), TOKEN_REDIR_OUT));
		(*i)++;
	}
}

static void	handle_separator(char *line, int *i, t_token **head)
{
	if (line[*i] == '|')
	{
		token_add_back(head, new_token(ft_strdup("|"), TOKEN_PIPE));
		(*i)++;
	}
	else if (line[*i] == '<')
		handle_redir_in(line, i, head);
	else if (line[*i] == '>')
		handle_redir_out(line, i, head);
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
