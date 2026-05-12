/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrzesiek <ggrzesiek@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:21:43 by emilka            #+#    #+#             */
/*   Updated: 2026/05/12 16:26:27 by ggrzesiek        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_shlvl = 0;

static void	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(line);
	tokens = tokenizer(line);
	cmds = parse_tokens(shell, tokens);
	execute_cmd_chain(shell, cmds);
	free_cmds(cmds);
	free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals(&shell);
	errno = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			end(&shell, NULL);
		if (*line)
			process_line(&shell, line);
		free(line);
	}
	return (0);
}
