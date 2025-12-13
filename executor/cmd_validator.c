#include "./../minishell.h"

static char *validate_as_is(t_shell *shell, char *name)
{
  char *path;

  path = NULL;
  if (access(name, X_OK) == 0)
  {
    path = ft_strdup(name);
    if (!path)
      end(shell, "command path malloc error\n");
  }
  return(path);
}

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
    if (!path)
      end(shell, "command full path malloc error\n");
    if (access(path, X_OK) == 0)
      break;
    free(path);
    path = NULL;
    j++;
  }
  return(path);
}

void validate_command(t_shell *shell, t_cmd *cmd)
{
  char *path;
  char *name;

  path = NULL;
  name = cmd->args[0];
  if (ft_strlen(cmd->args[0]) >= 2 && 
    ft_strncmp("./", cmd->args[0], 2) == 0)
    path = validate_as_is(shell, name);
  else if(ft_strlen(cmd->args[0]) >= 1 && 
    ft_strncmp("/", cmd->args[0], 1) == 0)
    path = validate_as_is(shell, name);
  else
    path = validate_in_paths(shell, name);
  cmd->path=path;
}