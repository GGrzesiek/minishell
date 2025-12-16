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

/* bufered wrapper for getcwd */
static char	*getcwdir(t_shell *shell)
{
	static char	buffer[PATH_MAX] = "";
	getcwd(buffer, sizeof(buffer));
	if (!*buffer)
		end(shell, "error getting cwd\n");
	return (buffer);
}

static void run_child(t_shell *shell, t_cmd *cmd)
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
  printf("%s\n", getcwdir(shell));
  end(shell, NULL);
}

int pwd(t_shell *shell, t_cmd *cmd)
{
  int	pid;

	pid = fork();
	if (pid < 0)
		end(shell, "fork failed\n");
	else if (pid == 0)
		run_child(shell, cmd);
	else
  {
    if (cmd->fdout != STDOUT_FILENO)
      close(cmd->fdout);
  }
  return (0);
}