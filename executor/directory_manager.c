#include "./../minishell.h"

int	change_directory(t_shell *shell, t_cmd *cmd)
{
	char *to;

	to = cmd->args[1];
	if (!to)
	{
		to = env_get(&shell->env_list, "HOME");
		if (!to)
			return (1);
	}
	chdir(to);
  return (0);
}