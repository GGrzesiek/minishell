#include "./../minishell.h"

void	export(t_shell *shell, t_cmd *cmd)
{
	t_env	*new_node;

	new_node = new_env_node(cmd->args[1]);
	if (!new_node)
		end(shell, "envp new node malloc error\n");
	env_add_back(&shell->env_list, new_node);
}

void	unset(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp("PATH", cmd->args[1], 5) == 0)
	{
		free_split(shell->paths);
		shell->paths = NULL;
	}
	env_del(&shell->env_list, cmd->args[1]);
}

void	print_env(t_shell *shell, t_env **head)
{
	int		pid;
	t_env	*curr;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
	{
		curr = *head;
		while (curr)
		{
			printf("%s=%s\n", curr->key, curr->value);
			curr = curr->next;
		}
		end(shell, NULL);
	}
	else
		wait(0);
}
