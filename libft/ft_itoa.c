/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:47:16 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/01 17:39:07 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_size(unsigned int n);
static char		*process(unsigned int n, size_t size, char *b);

size_t	int_size(unsigned int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*process(unsigned int n, size_t size, char *b)
{
	b[size] = '\0';
	size--;
	if (n == 0)
		b[size] = '0';
	while (n > 0)
	{
		b[size] = (char)((n % 10) + '0');
		n /= 10;
		size--;
	}
	return (b);
}

char	*ft_itoa(int n)
{
	char	*new;
	size_t	size;

	if (n < 0)
	{
		size = int_size(-n) + 1;
		new = (char *)malloc((size + 1) * sizeof(char));
		if (new == NULL)
			return (NULL);
		new[0] = '-';
		return (process(-n, size, new));
	}
	else
	{
		size = int_size(n);
		new = (char *)malloc((size + 1) * sizeof(char));
		if (new == NULL)
			return (NULL);
		return (process(n, size, new));
	}
}
