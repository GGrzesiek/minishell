/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:09 by emilka            #+#    #+#             */
/*   Updated: 2026/02/28 16:20:19 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	char	*new_str;
	int		len;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
	{
		ft_strlcpy(new_str, str, len + 1);
		free(str);
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*append_str(char *str, char *append)
{
	char	*new_str;

	if (!str && !append)
		return (NULL);
	if (!str)
		return (ft_strdup(append));
	if (!append)
		return (str);
	new_str = ft_strjoin(str, append);
	free(str);
	return (new_str);
}
static char	*handle_dollar(t_shell *shell, char *str, int *i, char *res)
{
	int		start;
	char	*tmp;

	(*i)++;
	if (str[*i] == '?')
	{
		tmp = ft_itoa(shell->exit_code);
		res = append_str(res, tmp);
		(*i)++;
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		start = *i;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
		tmp = ft_substr(str, start, *i - start);
		res = append_str(res, env_get(&shell->env_list, tmp));
	}
	else
		return (append_char(res, '$'));
	free(tmp);
	return (res);
}

char	*expand_token(t_shell *shell, char *str)
{
	char	*res = ft_strdup("");
	int		i = 0;
	int		in_sq = 0;
	int		in_dq = 0;

	while (str[i])
	{
		if (str[i] == '\'' && !in_dq)
		{
			in_sq = !in_sq;
			i++;
		}
		else if (str[i] == '\"' && !in_sq)
		{
			in_dq = !in_dq;
			i++;
		}
		else if (str[i] == '$' && !in_sq)
			res = handle_dollar(shell, str, &i, res);
		else
			res = append_char(res, str[i++]);
	}
	return (res);
}
