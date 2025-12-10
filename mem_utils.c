#include "minishell.h"

void end(t_shell *shell, char *msg)
{
  t_env *lst;
  t_env *tmp;

  // FREE ENV LIST
  lst = shell->env_list;
  while (lst)
  {
    tmp = lst;
    lst = lst->next;
    free(tmp->key);
    free(tmp->value);
    free(tmp);
  }
  // FREE PATH SPLIT
  char **paths = shell->paths;
  if(paths)
  {
    int i = 0;
    while(paths[i])
    {
      free(paths[i]);
      i++;
    }
    free(paths);
  }
  if (msg)
    write(STDERR_FILENO, msg, ft_strlen(msg));
  exit(shell->exit_code);
}