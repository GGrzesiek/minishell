#include "./../minishell.h"

extern int g_SHLVL;

static void	run_child(t_shell *shell, t_cmd *cmd)
{
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
	execve(cmd->path, cmd->args, shell->envp);
	perror(cmd->args[0]);
  free(cmd->path);
  end(shell, NULL);
}

void	execute_native_command(t_shell *shell, t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
		run_child(shell, cmd);
	else
  {
    wait(0);
    if (cmd->fdin != STDIN_FILENO)
      close(cmd->fdin);
  }
}

int	process_native_command(t_shell *shell, t_cmd *cmd)
{
  validate_command(shell, cmd);
	if (cmd->path)
	{
		g_SHLVL++;
		execute_native_command(shell, cmd);
		g_SHLVL--;
		free(cmd->path);
	}
	else
    return (perror(cmd->args[0]), 1);
  return (0);
}