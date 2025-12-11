#include "minishell.h"

static void run_child(t_shell *shell, t_cmd *cmd, int in, int out)
{
  if (in != STDIN_FILENO)
  {
    if (dup2(in, STDIN_FILENO) == -1)
      end(shell, "in dup2 fail\n"); 
    close(in);
  }
  if (out != STDOUT_FILENO)
  {
    if (dup2(out, STDOUT_FILENO) == -1)
      end(shell, "out dup2 fail\n");
    close(out);
  }
  execve(cmd->path, cmd->args, shell->envp);
  perror("Comand Failed:");
  printf("Path: %s\n", cmd-> path);
  exit(1);
}


void execute_native_command(t_shell *shell, t_cmd *cmd, int in, int out)
{
  int pid;
  
  pid = fork();
  if (pid < 0)
    end(shell, "fork failed\n");
  else if (pid == 0)
    run_child(shell, cmd, in, out);
  else 
    wait(0);
}