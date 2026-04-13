/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 10:49:46 by emilka            #+#    #+#             */
/*   Updated: 2026/04/13 10:51:26 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	replace_env(t_env **head, t_env *new_n, size_t len)
{
	t_env	*curr;
	t_env	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, new_n->key, len + 1) == 0)
		{
			if (prev)
				prev->next = new_n;
			else
				*head = new_n;
			new_n->next = curr->next;
			return (free_env(curr), 1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (prev->next = new_n, 0);
}

int	env_add_back(t_env **head, t_env *new_node)
{
	if (!head || !new_node)
		return (1);
	if (!new_node->key || !*new_node->key)
		return (free_env(new_node), 1);
	if (!*head)
		return (*head = new_node, 0);
	replace_env(head, new_node, ft_strlen(new_node->key));
	return (0);
}

int	env_del(t_env **head, char *key)
{
	size_t	len;
	t_env	*curr;
	t_env	*prev;
	t_env	*tmp;

	if (!head || !*head || !key || !*key)
		return (1);
	curr = *head;
	prev = NULL;
	len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len + 1) == 0)
		{
			tmp = curr;
			if (!prev)
				*head = curr->next;
			else
				prev->next = curr->next;
			return (free_env(tmp), 0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

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
		if (ft_strncmp(curr->key, key, len + 1) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
