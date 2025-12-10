#include "minishell.h"

/*
Finds the command on the path, and initializes cmd->path for execution
*/
void validate_command(t_shell *shell, t_cmd *cmd)
{
  int j;
  char **paths = shell->paths;
  char *path;
  char *name = cmd->args[0];

  if (access(name, X_OK) == 0)
  {
    path = ft_strjoin("./", name);
    if(!path)
      end(shell, "command path malloc error\n");
  } 
  else
  {
    j = 0;
    while (paths[j])
    {
      printf("[%s]", paths[j]);
      path = ft_strjoin(paths[j], name);
      printf("[%s]", path);
      if(!path)
        end(shell, "command path malloc error\n");
      if (access(path, X_OK) == 0)
        break;
      free(path);
      j++;
    }
    if (!paths[j])
      end(shell, "command not found on path\n");
  }
  cmd->path=path;
}

t_cmd *init_single_cmd(t_shell *shell, char *line)
{
    char **args;
    t_cmd *new;

    args = ft_split(line, ' ');
    new = (t_cmd *) malloc(sizeof(t_cmd));
    if(!args || !new)
      end(shell, "single cmd init malloc error\n");
    new->args=args;
    validate_command(shell, new);
    return (new);
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
char *execute_command(t_shell *shell, t_cmd *cmd, char *input)
{
  int pid;
  int out[2];
  int in[2];
  char *output;

  output = NULL;
  if (pipe(out) == -1)
    end(shell, "out pipe fail\n");
  if (pipe(in) == -1)
    end(shell, "in pipe fail\n");
  write_all(shell, in[1], input);
  
  pid = fork();
  if (pid < 0)
    end(shell, "fork failed\n");
  else if (pid == 0)
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
  }
  else 
  {
    close(in[0]);
    close(in[1]);
    close(out[1]);
    wait(NULL);
    output = read_all(shell, out[0]);
  }
  return (output);
}