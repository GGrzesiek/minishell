/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emilka <emilka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:56:45 by emilka            #+#    #+#             */
/*   Updated: 2026/04/13 11:58:06 by emilka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
