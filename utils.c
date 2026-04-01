/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:52:36 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 07:06:45 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_single_cmd(t_shell *shell, char *line)
{
	char	**args;
	t_cmd	*new;

	args = ft_split(line, ' ');
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!args || !new)
		end(shell, "single cmd init malloc error\n");
	new->args = args;
	return (new);
}
