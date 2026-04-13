/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:34:59 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:36:30 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_shlvl;

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_shlvl == 0)
	{
		write(1, "^C\n", 4);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_shlvl == 0)
	{
		rl_redisplay();
	}
}

void	disable_control(t_shell *shell)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	shell->t = t;
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	setup_signals(t_shell *shell)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	disable_control(shell);
	signal(SIGQUIT, handle_sigquit);
}
