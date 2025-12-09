/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:12:32 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 14:38:34 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_abs(char c);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (i < n)
	{
		c1 = ft_abs(s1[i]);
		c2 = ft_abs(s2[i]);
		if (c1 == '\0' && c2 == '\0')
			return (0);
		else if (c1 > c2)
			return (c1 - c2);
		else if (c1 < c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}

char	ft_abs(char c)
{
	if (c < 0)
		return (-c);
	return (c);
}
