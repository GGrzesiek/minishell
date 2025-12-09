/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:37:33 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 14:38:48 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copies the string from src to dst
// as long as size > 0
// return 'total length of the string they tried to create' - initial len of src
// copy up to size - 1, guarantee termination.
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t			l2;
	unsigned int	i;

	l2 = ft_strlen(src);
	if (size == 0)
		return (l2);
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l2);
}
