#include "minishell.h"

static char *validate_in_cd(t_shell *shell, char *name)
{
  char *path;

  path = NULL;
  if (access(name, X_OK) == 0)
  {
    path = ft_strdup(name);
    if(!path)
      end(shell, "command path malloc error\n");
  }
  return(path);
}

/*
Finds the command in the current dir, or on the path, and initializes cmd->path for execution
*/
static char *validate_in_paths(t_shell *shell, char *name)
{
  char *path;
  char **paths;
  int j;

  j = 0;
  paths = shell->paths;
  while (paths[j])
  {
    path = ft_strjoin(paths[j], name);
    if(!path)
      end(shell, "command full path malloc error\n");
    if (access(path, X_OK) == 0)
      break;
    free(path);
    path = NULL;
    j++;
  }
  return(path);
}

static void validate_command(t_shell *shell, t_cmd *cmd)
{
  char *path;
  char *name;

  path = NULL;
  name = cmd->args[0];
  if (ft_strlen(cmd->args[0]) >= 2 && 
    ft_strncmp("./", cmd->args[0], 2) == 0)
  {
    path = validate_in_cd(shell, name);
  }
  else if(ft_strlen(cmd->args[0]) >= 1 && 
    ft_strncmp("/", cmd->args[0], 1) == 0)
  {
    path = validate_in_cd(shell, name);
  }
  else
  {
    path = validate_in_paths(shell, name);
  }
  cmd->path=path;
}

void execute_command(t_shell *shell, t_cmd *cmd, int in, int out)
{
  if (ft_strlen(cmd->args[0]) == 2 && 
      ft_strncmp("cd", cmd->args[0], 3) == 0)
  {
    change_directory(shell, cmd->args[1]);
  }
  else
  {
    validate_command(shell, cmd);
    if(cmd->path)
    {
      execute_native_command(shell, cmd, in, out);
      free(cmd->path);
    }
    else
      write_all(shell, STDOUT_FILENO, "Command not found\n");
  }
}