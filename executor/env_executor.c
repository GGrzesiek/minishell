#include "./../minishell.h"

int	export(t_shell *shell, t_cmd *cmd)
{
	t_env	*new_node;

	new_node = new_env_node(cmd->args[1]);
	if (!new_node)
		end(shell, "envp new node malloc error\n");
	env_add_back(&shell->env_list, new_node);
  if (cmd->fdin != STDIN_FILENO)
    close(cmd->fdin);
  return (0);
}

int	unset(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp("PATH", cmd->args[1], 5) == 0)
	{
		free_split(shell->paths);
		shell->paths = NULL;
	}
	env_del(&shell->env_list, cmd->args[1]);
  if (cmd->fdin != STDIN_FILENO)
    close(cmd->fdin);
  return (0);
}

static void run_child(t_shell *shell, t_cmd *cmd)
{
  t_env	*curr;
  curr = shell->env_list;
  if (cmd->fdin != STDIN_FILENO)
  {
    if (dup2(cmd->fdin, STDIN_FILENO) == -1)
      end(shell, "dup2 input fail");
    close(cmd->fdin);
  }
  if (cmd->fdout != STDOUT_FILENO)
  {
    if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
      end(shell, "dup2 output fail");
    close(cmd->fdout);
  }
  while (curr)
  {
    printf("%s=%s\n", curr->key, curr->value);
    curr = curr->next;
  }
  end(shell, NULL);
}

int	print_env(t_shell *shell, t_cmd *cmd)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
	{
    run_child(shell, cmd);
	}
	else
  {
    wait(0);
    if (cmd->fdin != STDIN_FILENO)
      close(cmd->fdin);
  }
  return (0);
}
