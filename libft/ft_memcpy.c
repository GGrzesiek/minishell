/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:51:40 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/17 12:12:20 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*srci;
	unsigned char	*dsti;

	dsti = (unsigned char *)dest;
	srci = (unsigned char *)src;
	while (n > 0)
	{
		*dsti = *srci;
		dsti++;
		srci++;
		n--;
	}
	return (dest);
}
