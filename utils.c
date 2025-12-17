/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:35:07 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:35:08 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	if (!*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


void shperror(char *a, char *msg)
{
  if (a)
  {
    write(2, a, ft_strlen(a));
    write(2, ": ", 2);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
  }
}
