/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:28:05 by sandrzej          #+#    #+#             */
/*   Updated: 2025/09/25 12:35:02 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*i;
	unsigned char	fill;

	fill = (unsigned char)c;
	i = (unsigned char *)s;
	while (n > 0)
	{
		*i = fill;
		i++;
		n--;
	}
	return (s);
}
