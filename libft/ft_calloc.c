/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:50:14 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/07 18:15:22 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*i;
	size_t	b;

	b = size * nmemb;
	if (b == 0)
		return (malloc(0));
	if (b / nmemb != size)
		return (NULL);
	i = (char *)malloc(b);
	if (i == NULL)
		return (NULL);
	ft_bzero(i, b);
	return ((void *)i);
}
