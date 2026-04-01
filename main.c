/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 06:53:03 by ggrzesiek         #+#    #+#             */
/*   Updated: 2026/04/01 06:54:38 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_shlvl = 0;

static void	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(line);
	tokens = tokenizer(line);
	cmds = parse_tokens(tokens);
	execute_command(shell, cmds);
	free_cmds(cmds);
	free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	shell.argc = argc;
	shell.argv = argv;
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		line = readline("mini(s)hell> ");
		if (!line)
			end(&shell, NULL);
		if (*line)
			process_line(&shell, line);
		free(line);
	}
}
