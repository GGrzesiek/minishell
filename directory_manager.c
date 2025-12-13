#include "minishell.h"

/* bufered wrapper for getcwd*/
char *getcwdir(t_shell *shell)
{
  static char buffer[PATH_MAX] = "";
  getcwd(buffer, sizeof(buffer));
  if (!*buffer)
    end(shell, "error getting cwd\n");
  return(buffer);
}

void change_directory(t_shell *shell, t_cmd *cmd)
{
  char *to;

  to = cmd->args[1];
  if (!to)
  {
    to = env_get(&shell->env_list, "HOME");
    if (!to)
      return ;
  }
  chdir(to);
}