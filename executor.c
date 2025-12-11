#include "minishell.h"

extern int g_SHLVL;

static char *validate_as_is(t_shell *shell, char *name)
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

/*
Finds the command in the current dir, or on the path, and initializes cmd->path for execution
*/
static void validate_command(t_shell *shell, t_cmd *cmd)
{
  char *path;
  char *name;

  path = NULL;
  name = cmd->args[0];
  if (ft_strlen(cmd->args[0]) >= 2 && 
    ft_strncmp("./", cmd->args[0], 2) == 0)
  {
    path = validate_as_is(shell, name);
  }
  else if(ft_strlen(cmd->args[0]) >= 1 && 
    ft_strncmp("/", cmd->args[0], 1) == 0)
  {
    path = validate_as_is(shell, name);
  }
  else
  {
    path = validate_in_paths(shell, name);
  }
  cmd->path=path;
}

void execute_command(t_shell *shell, t_cmd *cmd, int in, int out)
{
  char *name;
  t_env *new_node;

  name = cmd->args[0];
  if(ft_strncmp("exit", name, 5) == 0)
  {
    end(shell, NULL);
  }
  else if (ft_strncmp("cd", name, 3) == 0)
  {
    change_directory(shell, cmd->args[1]);
  }
  else if (ft_strncmp("export", name, 7) == 0)
  {
    new_node = new_env_node(cmd->args[1]);
    if (!new_node)
      end(shell, "envp new node malloc error\n");
		env_add_back(&shell->env_list, new_node);
    print_env(&shell->env_list);
  }
  else if (ft_strncmp("unset", name, 6) == 0)
  {
    if (ft_strncmp("PATH", cmd->args[1], 5) == 0)
    {
      free_split(shell->paths);
      shell->paths = NULL;
    }
    env_del(&shell->env_list, cmd->args[1]);
  }
  else if (ft_strncmp("env", name, 4) == 0)
  {
    print_env(&shell->env_list);
  }
  else
  {
    if (!shell->paths)
      init_path(shell);
    if (shell->paths)
    {
      validate_command(shell, cmd);
      if(cmd->path)
      {
        g_SHLVL++; 
        execute_native_command(shell, cmd, in, out);
        g_SHLVL--;
        free(cmd->path);
      }
      else
        write_all(shell, STDOUT_FILENO, "Command not found\n");
    }
    else
      write_all(shell, STDOUT_FILENO, "Command not found\n");
  }
}