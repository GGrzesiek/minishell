/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:53:23 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 07:06:45 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* bufered wrapper for getcwd*/
char	*getcwdir(t_shell *shell)
{
	static char	buffer[PATH_MAX] = "";

	getcwd(buffer, sizeof(buffer));
	if (!*buffer)
		end(shell, "error getting cwd\n");
	return (buffer);
}

void	change_directory(t_shell *shell, char *to)
{
	if (!to)
	{
		to = env_get(&shell->env_list, "HOME");
		if (!to)
			return ;
	}
	chdir(to);
}
