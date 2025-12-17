/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:39:37 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:39:39 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	write_all(t_shell *shell, int fd, char *content)
{
	if (fd < 0)
		end(shell, "invalid fd\n");
	if (content)
		write(fd, content, ft_strlen(content));
}

char	*read_all(t_shell *shell, int fd)
{
	int		bread;
	char	buffer[101];
	char	*content;
	char	*tmp;

	if (fd < 0)
		end(shell, "invalid fd\n");
	bread = 1;
	content = NULL;
	while (bread > 0)
	{
		bread = read(fd, buffer, 100);
		buffer[bread] = '\0';
		tmp = content;
		content = ft_strjoin(content, buffer);
		if (!content)
			end(shell, "file read_all malloc error\n");
		free(tmp);
	}
	return (content);
}
