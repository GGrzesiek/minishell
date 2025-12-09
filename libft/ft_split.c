/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:11:21 by sandrzej          #+#    #+#             */
/*   Updated: 2025/10/10 15:47:58 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_occurence(char *s, char c);
static int			split(char *s, char c, char **spl, int flag);

char	**ft_split(char const *s, char c)
{
	char	**spl;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = count_occurence((char *)s, c);
	spl = (char **)malloc((len + 1) * sizeof(char *));
	if (spl == NULL)
		return (NULL);
	spl[len] = NULL;
	if (split((char *)s, c, spl, 0))
	{
		free(spl);
		return (NULL);
	}
	return (spl);
}

int	allocate(size_t i, char *start, char **spl, unsigned int *counter)
{
	char	*tmp;

	tmp = (char *)malloc((i + 1) * sizeof(char));
	if (tmp == NULL)
		return (1);
	ft_strlcpy(tmp, start, i + 1);
	spl[*counter] = tmp;
	*counter += 1;
	return (0);
}

int	free_prev(char **spl, unsigned int counter)
{
	while (counter--)
		free(spl[counter]);
	return (1);
}

int	split(char *s, char c, char **spl, int flag)
{
	unsigned int	counter;
	char			*start;

	counter = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (flag == 1)
				if (allocate(s - start, start, spl, &counter))
					return (free_prev(spl, counter));
			flag = 0;
		}
		else if (flag == 0)
		{
			start = s;
			flag = 1;
		}
		s++;
	}
	if (flag == 1)
		if (allocate(s - start, start, spl, &counter))
			return (free_prev(spl, counter));
	return (0);
}

unsigned int	count_occurence(char *s, char c)
{
	unsigned int	count;
	int				flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		else if (flag == 0)
		{
			count++;
			flag = 1;
		}
		s++;
	}
	return (count);
}
