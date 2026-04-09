/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:53:16 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 07:06:45 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_shlvl;

int	is_builtin(char *name)
{
	return (ft_strncmp("exit", name, 5) == 0 || ft_strncmp("cd", name, 3) == 0
		|| ft_strncmp("export", name, 7) == 0 || ft_strncmp("unset", name,
			6) == 0 || ft_strncmp("env", name, 4) == 0 || ft_strncmp("echo",
			name, 5) == 0 || ft_strncmp("pwd", name, 4) == 0);
}

static void	scan_heredocs(t_shell *shell, t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == TOKEN_REDIR_HEREDOC)
		{
			if (cmd->heredoc_fd >= 0)
				close(cmd->heredoc_fd);
			cmd->heredoc_fd = handle_heredoc(shell, r->file);
		}
		r = r->next;
	}
}

static void	run_single_builtin(t_shell *shell, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;

	scan_heredocs(shell, cmd);
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(shell, cmd) == 0)
		dispatch_builtin(shell, cmd);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	if (cmd->heredoc_fd >= 0)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}

void	execute_command(t_shell *shell, t_cmd *cmds)
{
	if (!cmds || !cmds->args || !cmds->args[0])
		return ;
	if (!cmds->next && is_builtin(cmds->args[0]))
	{
		run_single_builtin(shell, cmds);
		return ;
	}
	g_shlvl++;
	execute_pipeline(shell, cmds);
	g_shlvl--;
}
