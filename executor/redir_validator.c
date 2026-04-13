/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:21:33 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/10 23:33:03 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	run_cmd(t_shell *shell, t_cmd *cmd)
{
	if (open_redir(shell, cmd))
		return (1);
	if (cmd->args && execute_command(shell, cmd) && !shell->exit_code)
		shell->exit_code = 1;
	return (0);
}
