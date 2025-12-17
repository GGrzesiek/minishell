/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandrzej <sandrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:34:17 by sandrzej          #+#    #+#             */
/*   Updated: 2025/12/17 12:34:21 by sandrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_shlvl = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals(&shell);
	while (1)
	{
		line = readline("mini(s)hell> ");
		if (!line)
			end(&shell, NULL);
		if (*line)
		{
			add_history(line);
			tokens = tokenizer(line);
			cmds = parse_tokens(tokens);
			execute_cmd_chain(&shell, cmds);
			free_cmds(cmds);
			free_tokens(tokens);
			free(line);
		}
	}
}
