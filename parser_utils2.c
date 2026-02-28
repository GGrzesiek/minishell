/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:09 by emilka            #+#    #+#             */
/*   Updated: 2026/02/28 15:00:27 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// Dokleja jeden znak do stringa i zwalnia stary string
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

// Dokleja drugi string do pierwszego i zwalnia pierwszy
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
char	*expand_token(t_shell *shell, char *str)
{
	char	*res = ft_strdup("");
	int		i = 0;
	int		in_sq = 0;
	int		in_dq = 0;

	while (str[i])
	{
		// 1. Obsługa cudzysłowów pojedynczych '
		if (str[i] == '\'' && !in_dq)
		{
			in_sq = !in_sq; // włącz/wyłącz
			i++;
		}
		// 2. Obsługa cudzysłowów podwójnych "
		else if (str[i] == '\"' && !in_sq)
		{
			in_dq = !in_dq; // włącz/wyłącz
			i++;
		}
		// 3. Obsługa znaku dolara $ (tylko poza pojedynczymi cudzysłowami)
		else if (str[i] == '$' && !in_sq)
		{
			i++;
			if (str[i] == '?') // Zmienna $?
			{
				char *num = ft_itoa(shell->exit_code);
				res = append_str(res, num);
				free(num);
				i++;
			}
			else if (ft_isalpha(str[i]) || str[i] == '_') // Zwykła zmienna np. $USER
			{
				int start = i;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
				char *var_name = ft_substr(str, start, i - start);
				char *var_val = env_get(&shell->env_list, var_name);
				if (var_val)
					res = append_str(res, var_val); // doklej wartość jeśli istnieje
				free(var_name);
			}
			else // Zwykły znak $, po którym nic nie ma
			{
				res = append_char(res, '$');
			}
		}
		// 4. Każdy inny, zwykły znak
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}