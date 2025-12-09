/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:16:35 by sandrzej          #+#    #+#             */
/*   Updated: 2025/09/24 18:27:11 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*i;
	char	needle;

	i = (char *)s;
	needle = (char)c;
	while (n > 0)
	{
		if (*i == needle)
			return ((void *)i);
		i++;
		n--;
	}
	return (NULL);
}
