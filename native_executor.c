#include "minishell.h"

static void init_pipe(t_shell *shell, int *in, int *out, char *input)
{
  if (pipe(out) == -1)
    end(shell, "out pipe fail\n");
  if (pipe(in) == -1)
    end(shell, "in pipe fail\n");
  write_all(shell, in[1], input);
}

static void run_child(t_shell *shell, int *in, int *out, t_cmd *cmd)
{
  close(in[1]);
  close(out[0]);
  if (dup2(in[0], STDIN_FILENO) == -1)
    end(shell, "in dup2 fail\n"); 
  close(in[0]);
  if (dup2(out[1], STDOUT_FILENO) == -1)
    end(shell, "out dup2 fail\n");
  close(out[1]);
  execve(cmd->path, cmd->args, shell->envp);
  perror("");
  exit(1);
}

static char *run_parent(t_shell *shell, int *in, int *out)
{
  close(in[0]);
  close(in[1]);
  close(out[1]);
  wait(NULL);
  return (read_all(shell, out[0]));
}

/* 
Writes input to pipe(in)
Child ->
  Masks pipe(in) as STDIN_FILENO
  Masks pipe(out) as STDOUT_FILENO
  executes command
Parent ->
  reads from pipe(out)
*/
char *execute_native_command(t_shell *shell, t_cmd *cmd, char *input)
{
  int pid;
  int out[2];
  int in[2];
  char *output;

  output = NULL;
  init_pipe(shell, in, out, input);
  
  pid = fork();
  if (pid < 0)
    end(shell, "fork failed\n");
  else if (pid == 0)
    run_child(shell, in, out, cmd);
  else 
    output = run_parent(shell, in, out);
  return (output);
}