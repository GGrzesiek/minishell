/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:40:48 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 15:50:33 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*new;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	while (len > 0)
	{
		new[len - 1] = (*f)(len - 1, s[len - 1]);
		len--;
	}
	return (new);
}
