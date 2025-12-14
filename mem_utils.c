#include "minishell.h"

void	free_env(t_env *node)
{
	free(node->value);
	free(node->key);
	free(node);
}

void	end(t_shell *shell, char *msg)
{
	t_env	*lst;
	t_env	*tmp;

	rl_clear_history();
	lst = shell->env_list;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_env(tmp);
	}
	free_split(shell->paths);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(shell->exit_code);
}

void	free_split(char **sp)
{
	int i;

	i = 0;
	if (sp)
	{
		while (sp[i])
		{
			free(sp[i]);
			i++;
		}
		free(sp);
	}
}

void close_pipe(t_cmd *cmd)
{
  if (cmd->fdin != STDIN_FILENO)
    close(cmd->fdin);
  if (cmd->fdout != STDOUT_FILENO)
    close(cmd->fdout);
  if (cmd->next && cmd->next->fdin != STDIN_FILENO)
    close(cmd->next->fdin);
}