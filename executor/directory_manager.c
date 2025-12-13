#include "./../minishell.h"

void	change_directory(t_shell *shell, t_cmd *cmd)
{
	char *to;

	to = cmd->args[1];
	if (!to)
	{
		to = env_get(&shell->env_list, "HOME");
		if (!to)
			return ;
	}
	chdir(to);
}