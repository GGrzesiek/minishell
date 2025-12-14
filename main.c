
#include "minishell.h"

volatile int	g_SHLVL = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char *line;

	shell.argc = argc;
	shell.argv = argv;

	init_shell(&shell, envp);
	setup_signals();

	while (1)
	{
		line = readline("mini(s)hell> ");

		if (!line) // Ctrl+D
			end(&shell, NULL);

		if (*line)
		{
			add_history(line);
			t_cmd *cmd = init_single_cmd(&shell, line);
			execute_cmd_chain(&shell, cmd);
			free_split(cmd->args);
			free(cmd);
		}
	}
}