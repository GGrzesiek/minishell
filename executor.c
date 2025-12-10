#include "minishell.h"

/*
Finds the command on the path, and initializes cmd->path for execution
*/
void validate_command(t_shell *shell, t_cmd *cmd)
{
  int j;
  char **paths = shell->paths;
  char *path;

  j = 0;
  while (paths[j])
  {
    printf("[%s]", paths[j]);
    path = ft_strjoin(paths[j], cmd->name);
    printf("[%s]", path);
    if(!path)
      end(data, "command path malloc error\n");
    if (access(path, X_OK) == 0)
      break;
    free(path);
    j++;
  }
  if (!paths[j])
    end(data, "command not found on path\n");
  cmd->path=path;
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
char *execute_command(t_shell *shell, t_cmd *cmd, char *stdinput)
{
  int pid;
  int out[2];
  int in[2];
  char *stdoutput;

  stdoutput = NULL;
  if (pipe(out) == -1)
    end(data, "out pipe fail\n");
  if (pipe(in) == -1)
    end(data, "in pipe fail\n");
  write_all(data, in[1], stdinput);
  pid = fork();
  if (pid < 0)
    end(data, "fork failed\n");
  else if (pid == 0)
  {
    close(in[1]);
    close(out[0]);
    if (dup2(in[0], STDIN_FILENO) == -1)
      end(data, "dup2 fail\n"); 
    close(in[0]);
    if (dup2(out[1], STDOUT_FILENO) == -1)
      end(data, "dup2 fail\n");
    close(out[1]);
    execve(data->cmd[i].path, data->cmd[i].params, envp);
  }
  else 
  {
    close(in[0]);
    close(in[1]);
    close(out[1]);
    wait(NULL);
    stdoutput = read_all(data, out[0]);
  }
  return (stdoutput);
}