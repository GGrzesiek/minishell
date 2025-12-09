/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:19:19 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 14:36:59 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*v1;
	unsigned char	*v2;

	v1 = (unsigned char *)s1;
	v2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (v1[i] < v2[i])
			return (v1[i] - v2[i]);
		else if (v1[i] > v2[i])
			return (v1[i] - v2[i]);
		i++;
	}
	return (0);
}
