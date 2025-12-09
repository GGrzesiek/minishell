/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:25:58 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/17 12:14:05 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*i;
	char	needle;

	needle = (char)c;
	i = (char *)s;
	while (*i)
	{
		if (*i == needle)
			return (i);
		i++;
	}
	if (needle == '\0' && *i == '\0')
		return (i);
	return (NULL);
}
