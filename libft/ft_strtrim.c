/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:47:01 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 15:49:49 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len;
	char			*new;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	while (is_in_set(s1[i], set) && s1[i])
		i++;
	if (i == len)
		return (ft_calloc(1, sizeof(char)));
	j = 0;
	while (is_in_set(s1[len - 1 - j], set) && s1[len - 1 - j])
		j++;
	len = len - i - j;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	return (ft_memcpy(new, &s1[i], len));
}

int	is_in_set(char c, char const *set)
{
	int	i;

	if (set == NULL)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
