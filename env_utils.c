/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:53:19 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:53:20 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_env **head, char *key)
{
	size_t	len;
	t_env	*curr;

	if (!head || !key || !*key)
		return (NULL);
	if (!*head)
		return (NULL);
	curr = *head;
	len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void	print_env(t_shell *shell, t_env **head)
{
	int		pid;
	t_env	*curr;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
	{
		curr = *head;
		while (curr)
		{
			printf("%s=%s\n", curr->key, curr->value);
			curr = curr->next;
		}
		end(shell, NULL);
	}
	else
		wait(0);
}
