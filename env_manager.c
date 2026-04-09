/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:53:19 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:53:20 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static int	env_has_key(t_env *head, char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (head)
	{
		if (ft_strncmp(head->key, key, len) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

t_env	*new_env_node(char *str)
{
	t_env	*node;
	char	*sub;
	int		i;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	sub = ft_substr(str, 0, i);
	if (sub != NULL)
		node->key = sub;
	if (str[i] == '=')
		node->value = ft_strdup(str + i + 1);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*curr;

	if (!head || !new_node)
		return ;
	if (!new_node->key || !new_node->value)
	{
		free_env_node(new_node);
		return ;
	}
	if (env_has_key(*head, new_node->key))
	{
		free_env_node(new_node);
		return ;
	}
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}

void	env_del(t_env **head, char *key)
{
	size_t	len;
	t_env	*curr;
	t_env	*prev;

	if (!head || !key || !*key || !*head)
		return ;
	curr = *head;
	prev = NULL;
	len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len) == 0)
		{
			if (!prev)
				*head = curr->next;
			else
				prev->next = curr->next;
			free_env_node(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
