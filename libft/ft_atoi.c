/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:34:11 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/08 19:09:03 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		value;
	char	*i;
	int		c;

	i = (char *)nptr;
	value = 0;
	c = 0;
	while (*i == ' ' || (*i >= 9 && *i <= 13))
		i++;
	if (*i == '+' || i[c] == '-')
		c++;
	while (ft_isdigit(i[c]))
	{
		value *= 10;
		value += (i[c] - '0');
		c++;
	}
	if (i[0] == '-')
		value = -value;
	return (value);
}
