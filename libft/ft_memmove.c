/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:54:07 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 15:52:14 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dsti;
	unsigned char	*srci;

	dsti = (unsigned char *)dest;
	srci = (unsigned char *)src;
	if (dest > src)
	{
		srci = (unsigned char *)src;
		while (n > 0)
		{
			dsti[n - 1] = srci[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
