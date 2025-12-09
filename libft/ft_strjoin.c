/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:46:40 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/17 12:12:09 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*new;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		l1 = 0;
	else
		l1 = ft_strlen(s1);
	if (s2 == NULL)
		l2 = 0;
	else
		l2 = ft_strlen(s2);
	new = (char *)malloc((l1 + l2 + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[l1 + l2] = '\0';
	ft_memcpy(new, s1, l1);
	ft_memcpy(&new[l1], s2, l2);
	return (new);
}
