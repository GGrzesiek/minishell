/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:27:24 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 17:37:29 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inner_find(char *start, char *ndl, size_t len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*hay;
	char	*ndl;

	hay = (char *)big;
	ndl = (char *)little;
	if (*little == '\0' || little == NULL)
		return (hay);
	while (len > 0 && *hay != '\0')
	{
		if (*hay == *ndl)
		{
			if (inner_find(hay, ndl, len))
				return (hay);
		}
		len--;
		hay++;
	}
	return (NULL);
}

int	inner_find(char *start, char *ndl, size_t len)
{
	int	i;

	i = 0;
	while (start[i] && len > 0)
	{
		if (ndl[i] == start[i] && ndl[i + 1] == '\0')
			return (1);
		else if (ndl[i] != start[i])
		{
			return (0);
		}
		i++;
		len--;
	}
	return (0);
}
