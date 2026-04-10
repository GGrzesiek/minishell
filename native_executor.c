#include "minishell.h"

static void run_child(t_shell *shell, t_cmd *cmd)
{
  execve(cmd->path, cmd->args, shell->envp);
  perror("Comand Failed:");
  printf("Path: %s\n", cmd-> path);
  exit(1);
}

void execute_native_command(t_shell *shell, t_cmd *cmd)
{
  int pid;
  
  pid = fork();
  if (pid < 0)
    end(shell, "fork failed\n");
  else if (pid == 0)
    run_child(shell, cmd);
  else 
    wait(0);
}