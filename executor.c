#include "minishell.h"

/*
Finds the command in the current dir, or on the path, and initializes cmd->path for execution
*/

void validate_command(t_shell *shell, t_cmd *cmd)
{
  int j;
  char **paths = shell->paths;
  char *path;
  char *name = cmd->args[0];

  path = NULL;
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
      path = ft_strjoin(paths[j], name);
      if(!path)
        end(shell, "command path malloc error\n");
      if (access(path, X_OK) == 0)
        break;
      free(path);
      j++;
    }
    if (!paths[j])
      path = NULL;
  }
  cmd->path=path;
}

char *execute_command(t_shell *shell, t_cmd *cmd, char *input)
{
  char *output;
  output = NULL;

  if (ft_strlen(cmd->args[0]) == 2 && ft_strncmp("cd", cmd->args[0], 3) == 0)
  {
    return ft_strdup("Changing Directory\n");
  }
  else
  {
    validate_command(shell, cmd);
    if(cmd->path)
    {
      output = execute_native_command(shell, cmd, input);
      free(cmd->path);
    }
    else
      output = ft_strdup("Command not found\n");
  }
  return (output);
}