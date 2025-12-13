#include "./../minishell.h"

extern int g_SHLVL;

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

void process_native_command(t_shell *shell, t_cmd *cmd)
{
  if (!shell->paths)
    init_path(shell);
  if (shell->paths)
  {
    validate_command(shell, cmd);
    if(cmd->path)
    {
      g_SHLVL++; 
      execute_native_command(shell, cmd);
      g_SHLVL--;
      free(cmd->path);
    }
    else
      write_all(shell, STDOUT_FILENO, "Command not found\n");
  }
  else
    write_all(shell, STDOUT_FILENO, "Command not found\n");
}